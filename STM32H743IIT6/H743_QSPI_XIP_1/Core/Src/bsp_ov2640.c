/**
 * bsp_ov2640.c - OV2640 摄像头驱动实现
 *
 * 双缓冲帧采集(DMA1_Stream2, 循环模式) → SDRAM
 * SCCB 通过 I2C1 (PB6=SCL, PB7=SDA) 写寄存器
 */

#include "bsp_ov2640.h"
#include "dma.h"
#include "dcmi.h"
#include "i2c.h"
#include "gpio.h"

/* --- 双缓冲帧 (放 SDRAM) --- */
static uint8_t *fb[2] = {
    (uint8_t *)0xC0100000,          /* SDRAM 1MB+ offset */
    (uint8_t *)0xC0140000           /* +256KB */
};
static volatile uint8_t fb_idx = 0;         /* 当前写缓冲索引 */
static void (*frame_callback)(void) = NULL;

/* --- SCCB/I2C 操作 --- */
static int sccb_write(uint8_t reg, uint8_t val)
{
    uint8_t buf[2] = { reg, val };
    if (HAL_I2C_Master_Transmit(&hi2c1, 0x60, buf, 2, 100) == HAL_OK)
        return 0;
    return -1;
}

static int sccb_read(uint8_t reg, uint8_t *val)
{
    if (HAL_I2C_Master_Transmit(&hi2c1, 0x60, &reg, 1, 100) != HAL_OK)
        return -1;
    if (HAL_I2C_Master_Receive(&hi2c1, 0x61, val, 1, 100) != HAL_OK)
        return -1;
    return 0;
}

/* --- OV2640 初始化寄存器序列 (320x240, RGB565) --- */
/* 简化版 — 正点原子 + 野火验证通过 */
typedef struct { uint8_t reg; uint8_t val; } ov2640_reg_t;

static const ov2640_reg_t ov2640_init_table[] = {
    /* 软复位 */
    {0xFF, 0x01}, {0x12, 0x80},
    /* Sensor 页: 格式/时钟 */
    {0xFF, 0x01},
    {0x12, 0x06},   /* COM7: RGB */
    {0x11, 0x01},   /* CLKRC */
    {0x03, 0x04},   /* VREF */
    {0x17, 0x14}, {0x18, 0x02}, {0x19, 0x03}, {0x1A, 0x7B}, /* window */
    {0x32, 0x00},   /* HREF */
    /* DSP 页: 分辨率/格式 */
    {0xFF, 0x00},
    {0x2C, 0x10},   /* 使能缩放 */
    {0x5A, 79}, {0x5B, 59}, {0x5C, 79}, {0x5D, 59}, /* 320x240 */
    {0xDA, 0x08},   /* RGB565 */
    {0xFF, 0x00},   /* back to DSP */
};

#define OV2640_REG_NUM  (sizeof(ov2640_init_table)/sizeof(ov2640_reg_t))

/* --- 初始化 --- */
void bsp_ov2640_init(void)
{
    uint8_t midh = 0, midl = 0;

    /* 硬件复位 */
    HAL_GPIO_WritePin(GPIOH, GPIO_PIN_6, GPIO_PIN_RESET);  /* PWDN=0 使能 */
    HAL_Delay(10);
    HAL_GPIO_WritePin(GPIOH, GPIO_PIN_7, GPIO_PIN_RESET);  /* RST=0 */
    HAL_Delay(1);
    HAL_GPIO_WritePin(GPIOH, GPIO_PIN_7, GPIO_PIN_SET);    /* RST=1 */
    HAL_Delay(10);

    /* 读 ID 验证 */
    sccb_write(0xFF, 0x01);
    sccb_read(0x1C, &midh);
    sccb_read(0x1D, &midl);
    if (midh != 0x7F || midl != 0xA2) {
        /* ID 不匹配 — 检查 I2C 接线 */
        while (1) { __NOP(); }
    }

    /* 批量写寄存器 */
    for (uint32_t i = 0; i < OV2640_REG_NUM; i++) {
        sccb_write(ov2640_init_table[i].reg, ov2640_init_table[i].val);
        HAL_Delay(1);
    }
}

/* --- 启动采集 --- */
void bsp_ov2640_start(void)
{
    fb_idx = 0;
    HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_CONTINUOUS,
                       (uint32_t)fb[0],
                       OV2640_FRAME_SIZE / 4);  /* Word 为单位 */
}

/* --- 停止 --- */
void bsp_ov2640_stop(void)
{
    HAL_DCMI_Stop(&hdcmi);
}

/* --- 获取当帧缓冲区 --- */
uint8_t* bsp_ov2640_get_fb(void)
{
    return fb[1 - fb_idx];  /* 返回刚写完的那帧 */
}

/* --- 帧回调 --- */
void bsp_ov2640_set_frame_cb(void (*cb)(void))
{
    frame_callback = cb;
}

/* DCMI 帧完成中断 */
void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi)
{
    /* invalidate D-Cache for the just-completed buffer */
    SCB_InvalidateDCache_by_Addr((uint32_t *)fb[fb_idx], OV2640_FRAME_SIZE);
    fb_idx = 1 - fb_idx;
    if (frame_callback) frame_callback();
}