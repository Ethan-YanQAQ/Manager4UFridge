/**
 * main.c - OV5640 摄像头测试 (基于野火 H743 源码)
 * 适配: IITx6 核心板, SDRAM 帧缓冲, 软 SCCB, 串口输出
 */

#include "stm32h7xx.h"
#include "main.h"
#include "bsp_led.h"
#include "bsp_ov5640.h"
#include "usart.h"  /* CubeMX USART1 */
#include <stdio.h>
#include "fmc.h"   /* CubeMX FMC/SDRAM */

/* printf 重定向 (使用 CubeMX 的 huart1) */
int fputc(int ch, FILE *f)
{
    while (!(USART1->ISR & USART_ISR_TXE_TXFNF)) {}
    USART1->TDR = ch;
    return ch;
}

/* SDRAM 模式寄存器位 */
#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)

/* ── SDRAM 帧缓冲 (QVGA 320×240 RGB565 = 153600 bytes) ── */
#define FB_START_ADDRESS  0xC0000000

uint8_t fps = 0;

/* ── SDRAM 初始化序列 (CubeMX FMC GPIO 已完成, 只需发命令) ── */
static void SDRAM_Init(void)
{
    FMC_SDRAM_CommandTypeDef cmd = {0};
    cmd.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;

    cmd.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
    cmd.AutoRefreshNumber = 1;
    HAL_SDRAM_SendCommand(&hsdram1, &cmd, 0xFFFF);
    HAL_Delay(1);

    cmd.CommandMode = FMC_SDRAM_CMD_PALL;
    HAL_SDRAM_SendCommand(&hsdram1, &cmd, 0xFFFF);

    cmd.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
    cmd.AutoRefreshNumber = 8;
    HAL_SDRAM_SendCommand(&hsdram1, &cmd, 0xFFFF);

    cmd.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
    cmd.ModeRegisterDefinition =
        SDRAM_MODEREG_BURST_LENGTH_1 |
        SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL |
        SDRAM_MODEREG_CAS_LATENCY_2 |
        SDRAM_MODEREG_OPERATING_MODE_STANDARD |
        SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;
    HAL_SDRAM_SendCommand(&hsdram1, &cmd, 0xFFFF);

    HAL_SDRAM_ProgramRefreshRate(&hsdram1, 937);
}

/* VSYNC 回调 ── 统计帧率 */
void HAL_DCMI_VsyncEventCallback(DCMI_HandleTypeDef *hdcmi)
{
    fps++;
    /* 每次帧同步重新设 DMA (野火方案) */
    OV5640_DMA_Config(FB_START_ADDRESS, OV5640_WIDTH * OV5640_HEIGHT / 2);
}

int main(void)
{
    OV5640_IDTypeDef OV5640_Camera_ID;

    /* ── HAL + 时钟 + 外设 ── */
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_FMC_Init();
    MX_USART1_UART_Init();
    SCB_EnableICache();
    SCB_EnableDCache();

    LED_GPIO_Config();

    printf("\r\n=== OV5640 Camera Test ===\r\n");
    printf("Board: STM32H743IIT6 + OV5640\r\n");

    /* SDRAM 初始化 */
    LED_BLUE;
    SDRAM_Init();
    printf("[OK] SDRAM init done\r\n");

    /* ── OV5640 初始化 ── */
    OV5640_HW_Init();

    OV5640_ReadID(&OV5640_Camera_ID);
    if (OV5640_Camera_ID.PIDH == 0x56) {
        printf("[OK] OV5640 ID: 0x%02X%02X\r\n",
               OV5640_Camera_ID.PIDH, OV5640_Camera_ID.PIDL);
    } else {
        printf("[FAIL] OV5640 not found! ID=0x%02X%02X\r\n",
               OV5640_Camera_ID.PIDH, OV5640_Camera_ID.PIDL);
        while (1) { LED_RED; HAL_Delay(500); LED_BLUE; HAL_Delay(500); }
    }

    OV5640_RGB565Config();
    printf("[OK] OV5640 RGB565 QVGA config done\r\n");

    OV5640_Init();
    printf("[OK] DCMI+DMA started\r\n");

    /* ── 主循环: 每秒打印帧率 ── */
    fps = 0;
    uint32_t last_tick = 0;
    while (1) {
        if (HAL_GetTick() - last_tick >= 1000) {
            printf("FPS: %d\r\n", (int)fps);
            fps = 0;
            last_tick = HAL_GetTick();
            LED_RED;
            HAL_Delay(50);
            LED_BLUE;
        }
    }
}

/* ═══════════════════════════════════════════════
 * System Clock 400MHz (野火原版)
 * ═══════════════════════════════════════════════ */
static void SystemClock_Config(void)
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;
    HAL_StatusTypeDef ret = HAL_OK;

    MODIFY_REG(PWR->CR3, PWR_CR3_SCUEN, 0);
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
    while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
    RCC_OscInitStruct.CSIState = RCC_CSI_OFF;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 5;
    RCC_OscInitStruct.PLL.PLLN = 160;
    RCC_OscInitStruct.PLL.PLLP = 2;
    RCC_OscInitStruct.PLL.PLLR = 2;
    RCC_OscInitStruct.PLL.PLLQ = 2;
    RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
    RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
    ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
    if (ret != HAL_OK) while (1) {}

    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
                                   RCC_CLOCKTYPE_D1PCLK1 | RCC_CLOCKTYPE_PCLK1 |
                                   RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_D3PCLK1);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
    RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;
    ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4);
    if (ret != HAL_OK) while (1) {}
}