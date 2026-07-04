/**
 * Phase 2b: OV2640 快照 → 串口上传到电脑
 *
 * 协议：
 *   STM32 发送: [0xAA 0xBB][4字节长度 big-endian][JPEG 数据]
 *   PC 端运行: python recv_jpeg.py COM3
 *
 * 使用方式：
 *   main.c 中 #define TEST_PHASE_OV2640_SNAPSHOT
 *   小板复位后自动拍一张照片，发到 PC
 */

#include "test_ov2640.h"
#include "test_config.h"
#include "i2c.h"
#include "dcmi.h"
#include "dma.h"
#include "gpio.h"
#include "usart.h"
#include <stdio.h>

#define OV2640_ADDR      0x60
#define SNAP_BUF          ((uint8_t *)0xC0100000)  /* SDRAM */
#define SNAP_BUF_SIZE     (128 * 1024)              /* 128KB */

static volatile int g_snap_done = 0;
static volatile uint32_t g_snap_len = 0;


static uint8_t ov2640_read(uint8_t reg)
{
    uint8_t val = 0;
    HAL_I2C_Mem_Read(&hi2c1, OV2640_ADDR, reg,
                     I2C_MEMADD_SIZE_8BIT, &val, 1, 100);
    return val;
}

/* ── DCMI 帧完成 (仅测试阶段编译) ── */
#if defined(TEST_PHASE_OV2640) || defined(TEST_PHASE_OV2640_SNAPSHOT)
void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi)
{
    g_snap_len = __HAL_DCMI_GET_COUNTER(hdcmi) * 4;  /* word→byte */
    SCB_InvalidateDCache_by_Addr((uint32_t *)SNAP_BUF, SNAP_BUF_SIZE);
    g_snap_done = 1;
    HAL_DCMI_Stop(hdcmi);
}
#endif

/* ── 发 JPEG 到 PC ── */
static void send_jpeg_over_uart(uint8_t *data, uint32_t len)
{
    uint8_t header[6];

    header[0] = 0xAA;   /* sync word */
    header[1] = 0xBB;
    header[2] = (len >> 24) & 0xFF;
    header[3] = (len >> 16) & 0xFF;
    header[4] = (len >>  8) & 0xFF;
    header[5] = (len >>  0) & 0xFF;

    /* 发送帧头 */
    HAL_UART_Transmit(&huart1, header, 6, 100);

    /* 发送 JPEG 数据（分块发送，避免阻塞过久） */
    uint32_t sent = 0;
    while (sent < len)
    {
        uint32_t chunk = (len - sent) > 4096 ? 4096 : (len - sent);
        HAL_UART_Transmit(&huart1, data + sent, chunk, 500);
        sent += chunk;

        /* 进度指示 */
        if ((sent & 0x3FFF) == 0 || sent == len)
        {
            printf("  sent %lu/%lu (%.0f%%)\r",
                   sent, len, 100.0f * sent / len);
        }
    }
    printf("\r\n[DONE] %lu bytes sent\r\n", len);
}

/* ── 主测试 ── */
void test_ov2640_run(void)
{
    printf("\r\nPhase 2b: OV2640 Snapshot → PC\r\n");

    /* 1. I2C 探测 */
    uint8_t pid = ov2640_read(0x0A);
    uint8_t ver = ov2640_read(0x0B);
    printf("[I2C] OV2640 PID=0x%02X VER=0x%02X\r\n", pid, ver);
    if (pid != 0x26)
    {
        printf("[FAIL] Camera not found!\r\n");
        while (1) { HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0); HAL_Delay(200); }
    }

    printf("[WAIT] Focusing camera (2s)...\r\n");
    HAL_Delay(2000);

    /* 2. 单次快照 */
    g_snap_done = 0;
    HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_SNAPSHOT,
                       (uint32_t)SNAP_BUF, SNAP_BUF_SIZE / 4);

    uint32_t timeout = HAL_GetTick() + 5000;
    while (!g_snap_done && HAL_GetTick() < timeout) {}
    if (!g_snap_done)
    {
        printf("[FAIL] Snapshot timeout!\r\n");
        while (1) {}
    }

    printf("[OK] Snapshot: %lu bytes\r\n", g_snap_len);

    /* 3. JPEG 头检测 */
    if (SNAP_BUF[0] == 0xFF && SNAP_BUF[1] == 0xD8)
    {
        printf("[OK] Valid JPEG header (0xFFD8)\r\n");
    }
    else
    {
        printf("[WARN] Expected JPEG (0xFFD8), got 0x%02X%02X\r\n",
               SNAP_BUF[0], SNAP_BUF[1]);
    }

    /* 4. 发送到 PC */
    printf("[SEND] Transmitting to PC...\r\n");
    send_jpeg_over_uart((uint8_t *)SNAP_BUF, g_snap_len);

    /* 5. 完成，LED 快闪确认 */
    printf("[OK] Done! LED fast blink\r\n");
    while (1)
    {
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
        HAL_Delay(100);
    }
}