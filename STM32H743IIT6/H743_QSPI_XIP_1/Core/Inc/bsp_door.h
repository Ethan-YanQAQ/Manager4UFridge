/**
 * bsp_door.h - 门磁传感器驱动
 *
 * 引脚: PG9 (GPIO_EXTI9, 下降沿触发)
 * 逻辑: 开门=高→低, 关门=低→高
 */

#ifndef __BSP_DOOR_H
#define __BSP_DOOR_H

#include "main.h"
#include <stdint.h>

/* 门状态 */
#define DOOR_CLOSED  0
#define DOOR_OPEN    1

/* 初始化 */
void bsp_door_init(void);

/* 获取当前门状态 (0=关门, 1=开门) */
uint8_t bsp_door_get_state(void);

/* 设置门状态变化回调 (ISR 中调用) */
void bsp_door_set_callback(void (*cb)(uint8_t state));

#endif /* __BSP_DOOR_H */