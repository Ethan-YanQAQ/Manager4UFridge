/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "dcmi.h"
#include "dma.h"
#include "quadspi.h"
#include "usart.h"
#include "gpio.h"
#include "fmc.h"
#include "app_x-cube-ai.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "test_config.h"
#ifdef TEST_PHASE_UART
#include "test_uart.h"
#endif
#if defined(TEST_PHASE_OV2640) || defined(TEST_PHASE_OV2640_SNAPSHOT)
#include "test_ov2640.h"
#endif
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_FMC_Init();
  MX_QUADSPI_Init();
  MX_DCMI_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  /* ── 修正初始化顺序 ── */
  MPU_Config();                       /* MPU 在 HAL + Clock 之后 */
  SCB_EnableICache();                 /* Cache 在外设初始化之后 */
  SCB_EnableDCache();
  SDRAM_InitSequence();               /* SDRAM 硬件初始化序列 */
  //CSP_QUADSPI_Init();                 /* STEP 6 启用 */ + 开 Quad 模式 */
  //CSP_QSPI_EnableMemoryMappedMode();  /* STEP 6 启用 */ @ 0x90000000 */
  //MX_X_CUBE_AI_Init();                /* STEP 7 启用 */+SDRAM+QSPI 之后 */
  /* USER CODE END 2 */

#ifdef TEST_PHASE_UART
  /* STEP 1: 裸机串口测试 */
  test_uart_run();
#elif defined(TEST_PHASE_OV2640) || defined(TEST_PHASE_OV2640_SNAPSHOT)
  /* STEP 2: 裸机 OV5640 测试 */
  test_ov2640_run();
#else
  /* STEP 3+: FreeRTOS 多任务 */
  osKernelInitialize();
  MX_FREERTOS_Init();
  osKernelStart();
#endif

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
static void MPU_Config(void)
{
    MPU_Region_InitTypeDef M = {0};
    HAL_MPU_Disable();

    /* Region 0: QSPI Flash @ 0x90000000, 32MB, cacheable, executable */
    M.Enable           = MPU_REGION_ENABLE;
    M.BaseAddress      = 0x90000000;
    M.Size             = MPU_REGION_SIZE_32MB;
    M.AccessPermission = MPU_REGION_FULL_ACCESS;
    M.IsBufferable     = MPU_ACCESS_BUFFERABLE;
    M.IsCacheable      = MPU_ACCESS_CACHEABLE;
    M.IsShareable      = MPU_ACCESS_NOT_SHAREABLE;
    M.Number           = MPU_REGION_NUMBER0;
    M.TypeExtField     = MPU_TEX_LEVEL1;
    M.SubRegionDisable = 0x00;
    M.DisableExec      = MPU_INSTRUCTION_ACCESS_ENABLE;
    HAL_MPU_ConfigRegion(&M);

    /* Region 1: SDRAM @ 0xC0000000, 32MB, cacheable, no-exec */
    M.BaseAddress      = 0xC0000000;
    M.Size             = MPU_REGION_SIZE_32MB;
    M.DisableExec      = MPU_INSTRUCTION_ACCESS_DISABLE;
    M.Number           = MPU_REGION_NUMBER1;
    HAL_MPU_ConfigRegion(&M);

    HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

/* ── SDRAM 初始化序列 ── */
#define SDRAM_MODEREG_BURST_LENGTH_1            ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL     ((uint16_t)0x0000)
#define SDRAM_MODEREG_CAS_LATENCY_2             ((uint16_t)0x0020)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD   ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE    ((uint16_t)0x0200)

static void SDRAM_InitSequence(void)
{
    FMC_SDRAM_CommandTypeDef cmd = {0};
    uint32_t temp = 0;
    cmd.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;

    cmd.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
    cmd.AutoRefreshNumber = 1;
    HAL_SDRAM_SendCommand(&hsdram1, &cmd, 0xFFFF);
    HAL_Delay(1);

    cmd.CommandMode = FMC_SDRAM_CMD_PALL;
    HAL_SDRAM_SendCommand(&hsdram1, &cmd, 0xFFFF);

    cmd.CommandMode       = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
    cmd.AutoRefreshNumber = 8;
    HAL_SDRAM_SendCommand(&hsdram1, &cmd, 0xFFFF);

    temp = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1
         | SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL
         | SDRAM_MODEREG_CAS_LATENCY_2
         | SDRAM_MODEREG_OPERATING_MODE_STANDARD
         | SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;
    cmd.CommandMode            = FMC_SDRAM_CMD_LOAD_MODE;
    cmd.ModeRegisterDefinition = temp;
    HAL_SDRAM_SendCommand(&hsdram1, &cmd, 0xFFFF);

    HAL_SDRAM_ProgramRefreshRate(&hsdram1, 937);
}

/* ── printf 重定向到 USART1 ── */
int _write(int fd, char *ptr, int len)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)ptr, len, 100);
    return len;
}
/* USER CODE END 4 */

/* USER CODE BEGIN 0 */  /* 把下面的 CubeMX 默认 MPU 注释掉 */
#if 0
 /* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}
#endif  /* #if 0 — 用 USER CODE 4 中的自定义 MPU_Config 代替 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
