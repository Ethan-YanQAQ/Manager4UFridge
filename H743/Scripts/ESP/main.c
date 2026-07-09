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
#include "dcmi.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ov2640_jpeg.h"
#include "wifi_esp01s.h"
#include <stdio.h>
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
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#include <stdio.h>

/* printf 重定向到 USART2 (Debug Console) */
int _write(int file, char *ptr, int len)
{
    HAL_UART_Transmit(&huart2, (uint8_t *)ptr, len, HAL_MAX_DELAY);
    return len;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
  /* Platform already initialized by startup code.
     SystemInit() configures FPU, MPU, and cache via CMSIS.
     We'll let HAL take over from here. */
  /* USER CODE END 1 */

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

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
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_DCMI_Init();
  /* USER CODE BEGIN 2 */

  printf("\r\n==================================================\r\n");
  printf("     STM32H7 + OV2640 + ESP-01S  \r\n");
  printf("==================================================\r\n");

  /* ---- Camera Init ---- */
  printf("[INFO] [CAM] Probing OV2640 sensor registers...\r\n");
  if (OV2640_JPEG_Init() == HAL_OK) {
      printf("[SUCCESS] [CAM] OV2640 JPEG initialized (320x240)!\r\n");
  } else {
      printf("[ERROR] [CAM] Camera probe failed! Check wiring.\r\n");
      while (1) {
          HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
          HAL_Delay(200);
      }
  }

  /* ---- WiFi Module Init ---- */
  DEBUG_LOG("[INIT] ESP-01S WiFi module...");
  if (WIFI_Init() != WIFI_OK) {
      DEBUG_LOG("[ERROR] ESP-01S AT communication failed");
      while (1) {
          HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
          HAL_Delay(500);
      }
  }
  DEBUG_LOG("[OK] ESP-01S AT communication OK");

  /* ---- Connect to Wi-Fi AP ---- */
  DEBUG_LOG("[WIFI] Connecting to AP: %s ...", WIFI_SSID);
  if (WIFI_ConnectAP(WIFI_SSID, WIFI_PASSWORD) != WIFI_OK) {
      DEBUG_LOG("[ERROR] WiFi AP connection failed");
      while (1) {
          HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
          HAL_Delay(1000);
      }
  }
  DEBUG_LOG("[OK] WiFi connected to AP");

  /* ---- Get local IP ---- */
  char local_ip[16];
  if (WIFI_GetLocalIP(local_ip) == WIFI_OK) {
      DEBUG_LOG("[INFO] ESP-01S local IP: %s", local_ip);
  }

  /* ---- Connect to PC TCP server (with retry) ---- */
  DEBUG_LOG("[TCP] Connecting to PC server %s:%d ...", PC_SERVER_IP, PC_SERVER_PORT);
  {
    int tcp_ok = 0;
    for (int retry = 0; retry < 10; retry++) {
      if (WIFI_ConnectTCPServer(PC_SERVER_IP, PC_SERVER_PORT) == WIFI_OK) {
        tcp_ok = 1;
        break;
      }
      DEBUG_LOG("[TCP] Retry %d/10 — is PC server running?", retry + 1);
      HAL_Delay(2000);
    }
    if (!tcp_ok) {
      DEBUG_LOG("[ERROR] TCP connection failed after 10 retries");
      while (1) {
        HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
        HAL_Delay(200);
      }
    }
  }
  DEBUG_LOG("[OK] TCP connected to server");

  DEBUG_LOG("========================================");
  DEBUG_LOG("[READY] System initialized — starting capture loop");
  DEBUG_LOG("========================================");

  /* Trigger first snapshot capture */
  OV2640_JPEG_Start_Capture();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    /*
     * Snapshot Image Transfer Loop
     *
     * DCMI_MODE_SNAPSHOT: hardware auto-stops after one frame.
     * DMA NORMAL mode: stream stops after NDTR reaches 0.
     * Single CIPSEND with 4-byte LE length header per frame.
     */
    if (g_jpeg_frame_ready)
    {
        printf("[SNAP] %lu bytes\r\n", (unsigned long)g_jpeg_frame_len);

        /* Send frame with 4-byte length header */
        if (WIFI_SendFrame(jpeg_frame_buf, g_jpeg_frame_len) == WIFI_OK)
        {
            /* Short LED blink on success */
            HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
            HAL_Delay(25);
            HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
        }
        else
        {
            printf("[SNAP] Send failed, reconnecting TCP...\r\n");
            WIFI_CloseTCP();
            HAL_Delay(1000);
            if (WIFI_ConnectTCPServer(PC_SERVER_IP, PC_SERVER_PORT) == WIFI_OK) {
                printf("[SNAP] TCP reconnected\r\n");
            }
        }

        /* Frame rate control: 50–100 ms between captures */
        HAL_Delay(50);
        OV2640_JPEG_Start_Capture();
    }
    /* USER CODE END 3 */
  }
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

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
