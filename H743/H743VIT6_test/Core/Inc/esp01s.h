#ifndef __ESP01S_H
#define __ESP01S_H

#include "main.h"

#define ESP_RX_BUF_SIZE 512

typedef struct {
    UART_HandleTypeDef *huart;    // 绑定的串口句柄
    uint8_t rx_buf[ESP_RX_BUF_SIZE]; // DMA接收缓存
    volatile uint8_t rx_flag;     // 接收完成标志
    volatile uint16_t rx_len;    // 接收数据长度
} ESP01S_HandleTypeDef;

// 函数声明
void ESP01S_Init(ESP01S_HandleTypeDef *hesp, UART_HandleTypeDef *huart);
void ESP01S_ClearBuffer(ESP01S_HandleTypeDef *hesp);
HAL_StatusTypeDef ESP01S_SendAT(ESP01S_HandleTypeDef *hesp, char *cmd, char *ack, uint32_t timeout);
void ESP01S_UART_IRQHandler(ESP01S_HandleTypeDef *hesp);

#endif /* __ESP01S_H */
