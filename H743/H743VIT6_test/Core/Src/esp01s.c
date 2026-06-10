#include "esp01s.h"
#include <string.h>
#include <stdio.h>

/**
  * @brief  初始化ESP01S驱动
  */
void ESP01S_Init(ESP01S_HandleTypeDef *hesp, UART_HandleTypeDef *huart) {
    hesp->huart = huart;
    hesp->rx_flag = 0;
    hesp->rx_len = 0;
    memset(hesp->rx_buf, 0, ESP_RX_BUF_SIZE);

    // 1. 清除可能已经存在的初始空闲中断标志（H7特有寄存器操作）
    __HAL_UART_CLEAR_FLAG(hesp->huart, UART_CLEAR_IDLEF);

    // 2. 开启UART空闲中断
    __HAL_UART_ENABLE_IT(hesp->huart, UART_IT_IDLE);

    // 3. 开启DMA接收
    HAL_UART_Receive_DMA(hesp->huart, hesp->rx_buf, ESP_RX_BUF_SIZE);
}

/**
  * @brief  清空接收缓存
  */
void ESP01S_ClearBuffer(ESP01S_HandleTypeDef *hesp) {
    hesp->rx_flag = 0;
    hesp->rx_len = 0;
    memset(hesp->rx_buf, 0, ESP_RX_BUF_SIZE);
}

/**
  * @brief  发送AT指令并等待预期的应答
  */
HAL_StatusTypeDef ESP01S_SendAT(ESP01S_HandleTypeDef *hesp, char *cmd, char *ack, uint32_t timeout) {
    ESP01S_ClearBuffer(hesp);

    // 发送数据
    HAL_UART_Transmit(hesp->huart, (uint8_t *)cmd, strlen(cmd), 100);

    uint32_t tickstart = HAL_GetTick();

    // 等待应答
    while ((HAL_GetTick() - tickstart) < timeout) {
        if (hesp->rx_flag) {
            // H7 刷新Cache
            //SCB_InvalidateDCache_by_Addr((uint32_t *)hesp->rx_buf, ESP_RX_BUF_SIZE);

            if (strstr((char *)hesp->rx_buf, ack) != NULL) {
                return HAL_OK;
            }
            hesp->rx_flag = 0; // 不是期望的应答，清除标志继续等待
        }
    }
    return HAL_TIMEOUT;
}

/**
  * @brief  精简版空闲中断处理：杜绝死锁风险
  */
void ESP01S_UART_IRQHandler(ESP01S_HandleTypeDef *hesp) {
    // 判断是否为空闲中断
    if (__HAL_UART_GET_FLAG(hesp->huart, UART_FLAG_IDLE) != RESET) {

        // 【关键修复】：针对 H7 架构安全清除空闲中断标志
        __HAL_UART_CLEAR_FLAG(hesp->huart, UART_CLEAR_IDLEF);

        // 不再 Stop DMA。直接通过计数器计算当前接收到的字节数
        uint16_t temp = ESP_RX_BUF_SIZE - __HAL_DMA_GET_COUNTER(hesp->huart->hdmarx);
        if (temp > 0) {
            hesp->rx_len = temp;
            hesp->rx_flag = 1;
        }
    }
}
