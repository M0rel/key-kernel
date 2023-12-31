/* This file contain low level adapters (STM32 HAL -> Key kernel) */
#include "ll_adapter.h"

#include "usbd_hid.h"
#include "usb_device.h"

#include "stm32f4xx_hal_tim.h"

extern USBD_HandleTypeDef hUsbDeviceFS;

extern TIM_HandleTypeDef htim11;

volatile uint16_t time_record = 0;
#define REBOOT_DELAY_SEC        3

GPIO_TypeDef *col_ports[] = {
        GPIOB,  /* index = 0 */
        GPIOB,  /* index = 1 */
        GPIOB,  /* index = 2 */
        GPIOB,  /* index = 3 */
        GPIOB,  /* index = 4 */
        GPIOB,  /* index = 5 */
        GPIOB,  /* index = 6 */
        GPIOB,  /* index = 7 */
        GPIOB,  /* index = 8 */
        GPIOB,  /* index = 9 */
        GPIOB, /* index = 10 */
        GPIOB, /* index = 11 */
        GPIOB, /* index = 12 */
        GPIOB, /* index = 13 */
        GPIOB, /* index = 14 */
        GPIOC, /* index = 15 */
};

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
        GPIO_PIN_14, /* index = 15 */
};

uint16_t row_gpios[] = {
        GPIO_PIN_0, /* index = 0 */
        GPIO_PIN_1, /* index = 1 */
        GPIO_PIN_2, /* index = 2 */
        GPIO_PIN_3, /* index = 3 */
        GPIO_PIN_4, /* index = 4 */
        GPIO_PIN_5, /* index = 5 */
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

        state = HAL_GPIO_ReadPin(col_ports[index], col_gpios[index]);
        if (GPIO_PIN_SET == state) {
                return true;
        }

        return false;
}

void delay_ms(uint32_t delay)
{
        HAL_Delay(delay);
}

void usb_send_report(void *report, size_t size)
{
        USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)report, size);
}

static
void indicate_reboot(void)
{
        int i = 0;
        for (; i < REBOOT_DELAY_SEC; i++) {
                HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
                HAL_Delay(500);
        }
}

void reboot_bootloader(void)
{
        /* Charge capacitor connected to BOOT1 */
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET);
        indicate_reboot();
        NVIC_SystemReset();
}

static
uint16_t get_tim_counter_value(void)
{
        return __HAL_TIM_GET_COUNTER(&htim11);
}

void timer_init(void)
{
        HAL_TIM_Base_Start(&htim11);
}

void timer_deinit(void)
{
        HAL_TIM_Base_Stop(&htim11);
}

void timer_set_current_time(void)
{
        time_record = get_tim_counter_value();
}

void timer_clean_time(void)
{
        time_record = 0;
}

bool is_time_passed_ms(size_t time_ms)
{
        uint16_t current_time = 0;

        current_time = get_tim_counter_value();
        if (current_time - time_record >= time_ms * 10)
        {
                timer_set_current_time();

                return true;
        }

        return false;
}
