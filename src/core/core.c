#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "key_buffers_manager.h"
#include "key_layout_provider.h"
#include "key_manager.h"
#include "key_scancodes.h"

#include "ll_adapter.h"

uint8_t pressed_keys[16] = {0};
keyboard_desc_st_t key_desc = {0};
usb_report_st_t usb_report = {0};
consumer_report_st_t consumer_report = {0};

static
void usb_report_init(void)
{
        usb_report.id = 1;
}

void key_descriptor_init(void)
{
        key_desc.keys_layout = get_keys_layout(OS_MAC);
        key_desc.consumer_layout = get_consumer_layout();

        key_desc.keys_row_cnt = get_keys_row_cnt();
        key_desc.keys_col_cnt = get_keys_col_cnt();
        key_desc.pressed_keys = pressed_keys;
}

int user_main(void)
{
        usb_report_init();
        key_descriptor_init();

        timer_init();

        delay_ms(1000);

        while (true) {
                key_desc.pressed_consumer = 0;
                consumer_report.keys = 0;
                consumer_report.id = 2;

                get_pressed_keys(&key_desc);

                consumer_report.keys = key_desc.pressed_consumer;

                prepare_send_buffer(&key_desc, &usb_report);

                /* TODO: Without delay see some second report send lags.
                 * Maybe it is data structure corrupt */
                usb_send_report(&usb_report, sizeof(usb_report_st_t));
                delay_ms(5);
                usb_send_report(&consumer_report, sizeof(consumer_report_st_t));
                delay_ms(5);
        };

        return 0;
}
