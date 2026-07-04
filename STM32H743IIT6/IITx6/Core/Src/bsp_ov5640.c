/**
 * bsp_ov5640.c - OV5640 摄像头驱动实现
 *
 * 双缓冲帧采集(DMA1_StreamX, 循环模式) → SDRAM
 * SCCB 通过软 I2C (PB3=SDA, PB4=SCL) 写寄存器
 *
 * 寄存器初始化表来源: STMicroelectronics/stm32-ov5640 (GitHub)
 * 共 150+ 寄存器, 覆盖 PLL/AEC/AWB/Gamma/ColorMatrix/LensCorrection
 */

#include "bsp_ov5640.h"
#include "dcmi.h"
#include "gpio.h"

/* --- 双缓冲帧 (放 SDRAM) --- */
static uint8_t *fb[2] = {
    (uint8_t *)0xC0100000,
    (uint8_t *)0xC0140000
};
static volatile uint8_t fb_idx = 0;
static void (*frame_callback)(void) = NULL;

/* ═══════════════════════════════════════════════════════════════
 * 软 I2C (SCCB) 驱动 — PB3=SDA, PB4=SCL, 开源+上拉
 * ═══════════════════════════════════════════════════════════════ */

#define SCCB_SCL_PIN   GPIO_PIN_4
#define SCCB_SDA_PIN   GPIO_PIN_3
#define SCCB_PORT      GPIOB

#define SDA_H()  HAL_GPIO_WritePin(SCCB_PORT, SCCB_SDA_PIN, GPIO_PIN_SET)
#define SDA_L()  HAL_GPIO_WritePin(SCCB_PORT, SCCB_SDA_PIN, GPIO_PIN_RESET)
#define SCL_H()  HAL_GPIO_WritePin(SCCB_PORT, SCCB_SCL_PIN, GPIO_PIN_SET)
#define SCL_L()  HAL_GPIO_WritePin(SCCB_PORT, SCCB_SCL_PIN, GPIO_PIN_RESET)
#define SDA_RD() HAL_GPIO_ReadPin(SCCB_PORT, SCCB_SDA_PIN)

/* ~5us 延时 (100kHz I2C 半周期), 480MHz 下约 200 NOP */
static void sccb_delay(void)
{
    for (volatile uint32_t i = 0; i < 120; i++) { __NOP(); }
}

static void sccb_start(void)
{
    SDA_H(); SCL_H(); sccb_delay();
    SDA_L(); sccb_delay();
    SCL_L();
}

static void sccb_stop(void)
{
    SDA_L(); sccb_delay();
    SCL_H(); sccb_delay();
    SDA_H(); sccb_delay();
}

/* 发 1 字节, 返回 ACK (1=ACK, 0=NACK) */
static uint8_t sccb_write_byte(uint8_t data)
{
    for (int i = 0; i < 8; i++) {
        if (data & 0x80) SDA_H(); else SDA_L();
        sccb_delay();
        SCL_H(); sccb_delay();
        SCL_L();
        data <<= 1;
    }
    /* 第9个时钟: 释放SDA, 读ACK */
    SDA_H(); sccb_delay();
    SCL_H(); sccb_delay();
    uint8_t ack = (SDA_RD() == GPIO_PIN_RESET) ? 1 : 0;
    SCL_L();
    return ack;
}

/* 读 1 字节 + 回复 ACK/NACK */
static uint8_t sccb_read_byte(uint8_t send_ack)
{
    uint8_t data = 0;
    SDA_H();
    for (int i = 0; i < 8; i++) {
        data <<= 1;
        SCL_H(); sccb_delay();
        if (SDA_RD() != GPIO_PIN_RESET) data |= 1;
        SCL_L(); sccb_delay();
    }
    if (send_ack) SDA_L(); else SDA_H();
    sccb_delay();
    SCL_H(); sccb_delay();
    SCL_L();
    SDA_H();
    return data;
}

/* OV5640 SCCB 写: [0x78] [regH] [regL] [val] */
static int sccb_write(uint16_t reg, uint8_t val)
{
    sccb_start();
    if (!sccb_write_byte(0x78)) goto fail;
    if (!sccb_write_byte((reg >> 8) & 0xFF)) goto fail;
    if (!sccb_write_byte(reg & 0xFF)) goto fail;
    if (!sccb_write_byte(val)) goto fail;
    sccb_stop();
    return 0;
fail:
    sccb_stop();
    return -1;
}

/* OV5640 SCCB 读: [0x78][regH][regL]+Stop+[0x79][val(NAK)]+Stop */
static int sccb_read(uint16_t reg, uint8_t *val)
{
    /* Phase 1: 写寄存器地址 */
    sccb_start();
    if (!sccb_write_byte(0x78)) goto fail;
    if (!sccb_write_byte((reg >> 8) & 0xFF)) goto fail;
    if (!sccb_write_byte(reg & 0xFF)) goto fail;
    sccb_stop();

    /* Phase 2: 读数据 */
    sccb_start();
    if (!sccb_write_byte(0x79)) goto fail;
    *val = sccb_read_byte(0);   /* 最后一个字节回 NACK */
    sccb_stop();
    return 0;
fail:
    sccb_stop();
    return -1;
}

/* 初始化软 I2C 引脚 (在 bsp_ov5640_init 中调用) */
static void sccb_gpio_init(void)
{
    GPIO_InitTypeDef g = {0};
    g.Pin = SCCB_SCL_PIN | SCCB_SDA_PIN;
    g.Mode = GPIO_MODE_OUTPUT_OD;    /* 开漏 + 内部上拉 = 无需外部电阻 */
    g.Pull = GPIO_PULLUP;
    g.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(SCCB_PORT, &g);
    SDA_H(); SCL_H();  /* 初始释放总线 */
}

/* ── 寄存器表批量写入 ── */
static int sccb_write_table(const ov5640_reg_t *tbl, uint32_t n)
{
    for (uint32_t i = 0; i < n; i++) {
        if (sccb_write(tbl[i].reg, tbl[i].val) != 0)
            return -1;
    }
    return 0;
}

/* ═══════════════════════════════════════════════════════════════
 * OV5640 初始化寄存器序列 (ST官方 Common 表 + QVGA + RGB565)
 * 来源: github.com/STMicroelectronics/stm32-ov5640
 * ═══════════════════════════════════════════════════════════════ */

typedef struct { uint16_t reg; uint8_t val; } ov5640_reg_t;

static const ov5640_reg_t ov5640_init_table[] = {
    /* ═══ OV5640_Common[] — ST 官方 141 寄存器 (基础配置, 默认 WVGA) ═══ */
    {0x3103, 0x11}, {0x3008, 0x82}, {0x3103, 0x03},
    {0x3630, 0x36}, {0x3631, 0x0E}, {0x3632, 0xE2}, {0x3633, 0x12},
    {0x3621, 0xE0}, {0x3704, 0xA0}, {0x3703, 0x5A}, {0x3715, 0x78},
    {0x3717, 0x01}, {0x370B, 0x60}, {0x3705, 0x1A}, {0x3905, 0x02},
    {0x3906, 0x10}, {0x3901, 0x0A}, {0x3731, 0x12}, {0x3600, 0x08},
    {0x3601, 0x33}, {0x302D, 0x60}, {0x3620, 0x52}, {0x371B, 0x20},
    {0x471C, 0x50},
    {0x3A13, 0x43}, {0x3A18, 0x00}, {0x3A19, 0xF8},
    {0x3635, 0x13}, {0x3636, 0x03}, {0x3634, 0x40}, {0x3622, 0x01},
    {0x3C01, 0x34}, {0x3C04, 0x28}, {0x3C05, 0x98},
    {0x3C06, 0x00}, {0x3C07, 0x00}, {0x3C08, 0x01}, {0x3C09, 0x2C},
    {0x3C0A, 0x9C}, {0x3C0B, 0x40},
    {0x3820, 0x06}, {0x3821, 0x00}, {0x3814, 0x31}, {0x3815, 0x31},
    {0x3800, 0x00}, {0x3801, 0x00}, {0x3802, 0x00}, {0x3803, 0x04},
    {0x3804, 0x0A}, {0x3805, 0x3F}, {0x3806, 0x07}, {0x3807, 0x9B},
    {0x3808, 0x03}, {0x3809, 0x20}, {0x380A, 0x02}, {0x380B, 0x58},
    {0x380C, 0x07}, {0x380D, 0x90}, {0x380E, 0x04}, {0x380F, 0x40},
    {0x3810, 0x00}, {0x3811, 0x10}, {0x3812, 0x00}, {0x3813, 0x06},
    {0x3618, 0x00}, {0x3612, 0x29}, {0x3708, 0x64}, {0x3709, 0x52},
    {0x370C, 0x03},
    {0x3A02, 0x03}, {0x3A03, 0xD8},
    {0x3A08, 0x01}, {0x3A09, 0x27}, {0x3A0A, 0x00}, {0x3A0B, 0xF6},
    {0x3A0E, 0x03}, {0x3A0D, 0x04},
    {0x3A14, 0x03}, {0x3A15, 0xD8},
    {0x4001, 0x02}, {0x4004, 0x02},
    {0x3000, 0x00}, {0x3002, 0x1C},
    {0x3004, 0xFF}, {0x3006, 0xC3},
    {0x300E, 0x58},
    {0x302E, 0x00},
    {0x4740, 0x22},
    {0x4300, 0x6F},
    {0x501F, 0x01},
    {0x4711, 0x03}, {0x4712, 0x04},
    {0x440E, 0x00},
    {0x460B, 0x35}, {0x460C, 0x23},
    {0x3824, 0x02},
    {0x5000, 0xA7}, {0x5001, 0xA3},
    {0x5180, 0xFF}, {0x5181, 0xF2}, {0x5182, 0x00}, {0x5183, 0x14},
    {0x5184, 0x25}, {0x5185, 0x24}, {0x5186, 0x09}, {0x5187, 0x09},
    {0x5188, 0x09}, {0x5189, 0x75}, {0x518A, 0x54}, {0x518B, 0xE0},
    {0x518C, 0xB2}, {0x518D, 0x42}, {0x518E, 0x3D}, {0x518F, 0x56},
    {0x5190, 0x46}, {0x5191, 0xF8}, {0x5192, 0x04}, {0x5193, 0x70},
    {0x5194, 0xF0}, {0x5195, 0xF0}, {0x5196, 0x03}, {0x5197, 0x01},
    {0x5198, 0x04}, {0x5199, 0x12}, {0x519A, 0x04}, {0x519B, 0x00},
    {0x519C, 0x06}, {0x519D, 0x82}, {0x519E, 0x38},
    {0x5381, 0x1E}, {0x5382, 0x5B}, {0x5383, 0x08}, {0x5384, 0x0A},
    {0x5385, 0x7E}, {0x5386, 0x88}, {0x5387, 0x7C}, {0x5388, 0x6C},
    {0x5389, 0x10}, {0x538A, 0x01}, {0x538B, 0x98},
    {0x5300, 0x08}, {0x5301, 0x30}, {0x5302, 0x10}, {0x5303, 0x00},
    {0x5304, 0x08}, {0x5305, 0x30}, {0x5306, 0x08}, {0x5307, 0x16},
    {0x5309, 0x08}, {0x530A, 0x30}, {0x530B, 0x04}, {0x530C, 0x06},
    {0x5480, 0x01},
    {0x5481, 0x08}, {0x5482, 0x14}, {0x5483, 0x28}, {0x5484, 0x51},
    {0x5485, 0x65}, {0x5486, 0x71}, {0x5487, 0x7D}, {0x5488, 0x87},
    {0x5489, 0x91}, {0x548A, 0x9A}, {0x548B, 0xAA}, {0x548C, 0xB8},
    {0x548D, 0xCD}, {0x548E, 0xDD}, {0x548F, 0xEA}, {0x5490, 0x1D},
    {0x5580, 0x02}, {0x5583, 0x40}, {0x5584, 0x10},
    {0x5589, 0x10}, {0x558A, 0x00}, {0x558B, 0xF8},
    {0x5800, 0x23}, {0x5801, 0x14}, {0x5802, 0x0F}, {0x5803, 0x0F},
    {0x5804, 0x12}, {0x5805, 0x26}, {0x5806, 0x0C}, {0x5807, 0x08},
    {0x5808, 0x05}, {0x5809, 0x05}, {0x580A, 0x08}, {0x580B, 0x0D},
    {0x580C, 0x08}, {0x580D, 0x03}, {0x580E, 0x00}, {0x580F, 0x00},
    {0x5810, 0x03}, {0x5811, 0x09}, {0x5812, 0x07}, {0x5813, 0x03},
    {0x5814, 0x00}, {0x5815, 0x01}, {0x5816, 0x03}, {0x5817, 0x08},
    {0x5818, 0x0D}, {0x5819, 0x08}, {0x581A, 0x05}, {0x581B, 0x06},
    {0x581C, 0x08}, {0x581D, 0x0F}, {0x581E, 0x26}, {0x581F, 0x12},
    {0x5820, 0x0F}, {0x5821, 0x0F}, {0x5822, 0x14}, {0x5823, 0x23},
    {0x5824, 0x0A},
    {0x5025, 0x00},
    {0x3A0F, 0x30}, {0x3A10, 0x28}, {0x3A1B, 0x30}, {0x3A1E, 0x26},
    {0x3A11, 0x60}, {0x3A1F, 0x14},
    {0x3008, 0x02},

    /* ═══ QVGA 分辨率 (ST 官方: OV5640_QVGA[]) ═══ */
    {0x3808, 0x01}, {0x3809, 0x40},
    {0x380A, 0x00}, {0x380B, 0xF0},

    /* ═══ DVP + 极性 + 使能 ═══ */
    {0x3017, 0x7F}, {0x3018, 0xFC},
    {0x4740, 0x23},
    {0x300E, 0x18},
    {0x503D, 0x00},
};

#define OV5640_REG_NUM  (sizeof(ov5640_init_table)/sizeof(ov5640_reg_t))

/* ═══════════════════════════════════════════════════════════════
 * 公开 API
 * ═══════════════════════════════════════════════════════════════ */

void bsp_ov5640_init(void)
{
    uint8_t midh = 0, midl = 0;

    /* 软 I2C 引脚初始化 */
    sccb_gpio_init();

    /* 硬件上电时序 */
    HAL_GPIO_WritePin(GPIOH, GPIO_PIN_6, GPIO_PIN_RESET);  /* PWDN=0 */
    HAL_Delay(10);
    HAL_GPIO_WritePin(GPIOH, GPIO_PIN_7, GPIO_PIN_RESET);  /* RST=0 */
    HAL_Delay(20);
    HAL_GPIO_WritePin(GPIOH, GPIO_PIN_7, GPIO_PIN_SET);    /* RST=1 */
    HAL_Delay(20);

    /* 软件复位 */
    sccb_write(0x3008, 0x80);
    HAL_Delay(300);

    /* ID 验证 */
    sccb_read(0x300A, &midh);
    sccb_read(0x300B, &midl);
    if (midh != 0x56 || midl != 0x40) {
        while (1) {
            HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
            HAL_Delay(100);
        }
    }

    /* 批量写寄存器 (150+ 个) */
    sccb_write_table(ov5640_init_table, OV5640_REG_NUM);
    HAL_Delay(100);
}

void bsp_ov5640_start(void)
{
    fb_idx = 0;
    HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_CONTINUOUS,
                       (uint32_t)fb[0],
                       OV5640_FRAME_SIZE / 4);
}

void bsp_ov5640_stop(void)
{
    HAL_DCMI_Stop(&hdcmi);
}

uint8_t* bsp_ov5640_get_fb(void)
{
    return fb[1 - fb_idx];
}

void bsp_ov5640_set_frame_cb(void (*cb)(void))
{
    frame_callback = cb;
}

#if !defined(TEST_PHASE_OV2640) && !defined(TEST_PHASE_OV2640_SNAPSHOT)
void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi)
{
    SCB_InvalidateDCache_by_Addr((uint32_t *)fb[fb_idx], OV5640_FRAME_SIZE);
    uint8_t *ready = fb[fb_idx];
    fb_idx = 1 - fb_idx;
    HAL_DCMI_Stop(hdcmi);
    HAL_DCMI_Start_DMA(hdcmi, DCMI_MODE_CONTINUOUS,
                       (uint32_t)fb[fb_idx],
                       OV5640_FRAME_SIZE / 4);
    if (frame_callback) frame_callback();
    (void)ready;
}
#endif