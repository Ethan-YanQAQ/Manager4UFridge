/**
  * Phase 1: USART1 串口通信验证（裸机，不依赖 FreeRTOS）
  *
  * 烧录后打开串口助手（115200/8/N/1），应看到：
  *   ╔══════════════════════════╗
  *   ║  Manager4UFridge  UART  ║
  *   ╚══════════════════════════╝
  *   MCU: STM32H743, UID: XXXXXX
  *   SYSCLK: 480 MHz
  *   USART1: 115200 bps, PB14(TX) PB15(RX)
  *   [ECHO] 敲键盘看回显...
  *
  * 每 500ms 板载 LED(PB0) 翻转一次，确认 MCU 在跑。
  */

#include "test_uart.h"
#include "usart.h"
#include "gpio.h"
#include <stdio.h>
#include <string.h>


/* ── 读芯片 UID（96bit = 3×32bit）── */
static void read_uid(uint32_t uid[3])
{
    uid[0] = *((uint32_t *)0x1FF1E800);
    uid[1] = *((uint32_t *)0x1FF1E804);
    uid[2] = *((uint32_t *)0x1FF1E808);
}

void test_uart_run(void)
{
    uint32_t uid[3];
    uint32_t last_tick = 0;
    uint8_t  rx_byte;

    read_uid(uid);

    /* ── 打印系统信息 ── */
    printf("\r\n\r\n");
    printf("╔══════════════════════════╗\r\n");
    printf("║  Manager4UFridge  UART  ║\r\n");
    printf("╚══════════════════════════╝\r\n");
    printf("MCU:   STM32H743IIT6\r\n");
    printf("UID:   %08lX-%08lX-%08lX\r\n", uid[0], uid[1], uid[2]);
    printf("SYSCLK: 480 MHz\r\n");
    printf("USART1: 115200 bps, PB14(TX) PB15(RX)\r\n");
    printf("──────────────────────────\r\n");
    printf("[ECHO] 敲键盘看回显...\r\n\r\n");

    /* ── 主循环：LED 心跳 + 串口回环 ── */
    while (1)
    {
        /* LED PB0 每 500ms 翻转 */
        if (HAL_GetTick() - last_tick >= 500)
        {
            HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
            last_tick = HAL_GetTick();
        }

        /* 串口收到 1 字节 → 立即发回 */
        if (HAL_UART_Receive(&huart1, &rx_byte, 1, 1) == HAL_OK)
        {
            HAL_UART_Transmit(&huart1, &rx_byte, 1, 10);
        }
    }
}