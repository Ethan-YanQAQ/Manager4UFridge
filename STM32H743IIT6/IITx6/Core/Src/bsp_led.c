/**
 * bsp_led.c — IITx6 核心板 PB0 LED
 */
#include "bsp_led.h"

void LED_GPIO_Config(void)
{
    GPIO_InitTypeDef g = {0};
    LED_CLK_ENABLE();
    g.Pin = LED_PIN;
    g.Mode = GPIO_MODE_OUTPUT_PP;
    g.Pull = GPIO_PULLUP;
    g.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LED_PORT, &g);
    LED_RGBOFF;
}
