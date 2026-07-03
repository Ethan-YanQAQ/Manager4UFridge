#include "bsp_door.h"

static void (*door_callback)(uint8_t state) = NULL;
static volatile uint8_t door_state = DOOR_CLOSED;

/* EXTI 中断回调 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_9) {  /* PG9 */
        if (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_9) == GPIO_PIN_RESET) {
            door_state = DOOR_OPEN;
        } else {
            door_state = DOOR_CLOSED;
        }
        if (door_callback) {
            door_callback(door_state);
        }
    }
}

void bsp_door_init(void)
{
    door_state = (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_9) == GPIO_PIN_RESET)
                 ? DOOR_OPEN : DOOR_CLOSED;
}

uint8_t bsp_door_get_state(void)
{
    return door_state;
}

void bsp_door_set_callback(void (*cb)(uint8_t state))
{
    door_callback = cb;
}