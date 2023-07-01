#ifndef __LL_ADAPTER_H__
#define __LL_ADAPTER_H__

#include "stm32f4xx_hal.h"

#include <stdbool.h>
#include <stdint.h>

#define BIT(x)                  (1 << (x))

typedef enum {
        ACTIVATE   = 0,
        DEACTIVATE = 1,
} gpio_action_t;

void update_row_gpio_state_ll(gpio_action_t action, uint8_t index);
bool get_button_state_ll(uint8_t index);

void delay_ms(uint32_t delay);

void usb_send_report(void *report, size_t size);

void timer_init(void);
void timer_deinit(void);

void timer_set_current_time(void);
void timer_clean_time(void);

bool is_time_passed_ms(size_t time_ms);

void reboot_bootloader(void);

#endif /* __LL_ADAPTER_H__ */
