/* This file contain low level adapters (STM32 HAL -> Key kernel) */
#include "ll_adapter.h"

uint16_t col_gpios[] = {
        GPIO_PIN_0,  /* index = 0 */
        GPIO_PIN_1,  /* index = 1 */
        GPIO_PIN_2,  /* index = 2 */
        GPIO_PIN_3,  /* index = 3 */
        GPIO_PIN_4,  /* index = 4 */
        GPIO_PIN_5,  /* index = 5 */
        GPIO_PIN_6,  /* index = 6 */
        GPIO_PIN_7,  /* index = 7 */
        GPIO_PIN_8,  /* index = 8 */
        GPIO_PIN_9,  /* index = 9 */
        GPIO_PIN_10, /* index = 10 */
        GPIO_PIN_12, /* index = 11 */
        GPIO_PIN_13, /* index = 12 */
        GPIO_PIN_14, /* index = 13 */
        GPIO_PIN_15, /* index = 14 */
};

uint16_t row_gpios[] = {
        GPIO_PIN_1, /* index = 0 */
        GPIO_PIN_2, /* index = 1 */
        GPIO_PIN_3, /* index = 2 */
        GPIO_PIN_4, /* index = 3 */
        GPIO_PIN_5, /* index = 4 */
        GPIO_PIN_6, /* index = 5 */
};

void update_row_gpio_state_ll(gpio_action_t action, uint8_t index)
{
        if (ACTIVATE == action) {
                HAL_GPIO_WritePin(GPIOA, row_gpios[index], GPIO_PIN_SET);
        } else {
                HAL_GPIO_WritePin(GPIOA, row_gpios[index], GPIO_PIN_RESET);
        }
}

bool get_button_state_ll(uint8_t index)
{
        GPIO_PinState state = GPIO_PIN_RESET;

        state = HAL_GPIO_ReadPin(GPIOB, col_gpios[index]);
        if (GPIO_PIN_SET == state) {
                return true;
        }

        return false;
}

void delay_ms(uint32_t delay)
{
        HAL_Delay(delay);
}
