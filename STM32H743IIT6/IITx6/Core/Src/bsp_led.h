/**
 * bsp_led.h — 适配 IITx6 核心板 PB0 LED
 */

#ifndef __LED_H
#define __LED_H

#include "stm32h7xx.h"

#define LED_PIN                  GPIO_PIN_0
#define LED_PORT                 GPIOB
#define LED_CLK_ENABLE()         __HAL_RCC_GPIOB_CLK_ENABLE()

#define ON                       GPIO_PIN_RESET
#define OFF                      GPIO_PIN_SET

#define LED(a)                   HAL_GPIO_WritePin(LED_PORT, LED_PIN, a)
#define LED_TOGGLE               HAL_GPIO_TogglePin(LED_PORT, LED_PIN)

/* 单色 LED 别名 */
#define LED_RED                  LED(ON)
#define LED_GREEN                LED(ON)
#define LED_BLUE                 LED(ON)
#define LED_RGBOFF               LED(OFF)

void LED_GPIO_Config(void);
#endif