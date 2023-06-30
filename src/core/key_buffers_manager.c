#include "key_buffers_manager.h"
#include "key_scancodes.h"
#include "ll_adapter.h"

#define MAX_ITER_CNT    100

static
uint8_t get_modifier_key_bit(uint8_t keycode)
{
        switch(keycode) {
                case KEY_LEFT_CTRL:
                        return BIT(0);
                case KEY_LEFT_SHIFT:
                        return BIT(1);
                case KEY_LEFT_ALT:
                        return BIT(2);
                case KEY_LEFT_GUI:
                        return BIT(3);
                case KEY_RIGHT_CTRL:
                        return BIT(4);
                case KEY_RIGHT_SHIFT:
                        return BIT(5);
                case KEY_RIGHT_ALT:
                        return BIT(6);
                case KEY_RIGHT_GUI:
                        return BIT(7);
                default:
                        return 0;
        }
}

static
uint8_t fill_buffer_gaps(uint8_t *buff, uint8_t size)
{
        int i = 0;
        uint8_t count = 0;
        uint8_t buffer_size = 0;

        for (i = 0; i < size; i++) {
                if (NO_KEY == buff[i]) {
                        continue;
                }

                buff[count] = buff[i];
                count++;
        }

        buffer_size = count;

        while (count < size || count < MAX_ITER_CNT) {
                buff[count] = NO_KEY;
                count++;
        }

        return buffer_size;
}

static
void set_modifier_keys(keyboard_desc_st_t *key_desc, usb_report_st_t *report)
{
        uint8_t modifier_keys = 0;
        uint8_t key = 0;
        int i = 0;

        for (i = 0; i < key_desc->pressed_cnt; i++) {
                key = key_desc->pressed_keys[i];
                if (KEY_LEFT_CTRL <= key && KEY_RIGHT_GUI >= key) {
                        modifier_keys |= get_modifier_key_bit(key);

                        /* Remove modifier keys from buffer */
                        key_desc->pressed_keys[i] = NO_KEY;
                }
        }

        key_desc->pressed_cnt = fill_buffer_gaps(key_desc->pressed_keys,
                                                 key_desc->pressed_cnt);

        report->modifier = modifier_keys;
}

static
void prepare_buffers(keyboard_desc_st_t *key_desc, usb_report_st_t *report)
{
        bool key_found = false;
        int i = 0;
        int j = 0;

        /* Iterate over every field in report */
        for (i = 0; i < MAX_PRESSED_IN_REPORT; i++) {
                for (j = 0; j < key_desc->pressed_cnt; j++) {
                        if (key_desc->pressed_keys[j] == report->keys[i]) {
                                /* Remove key scancode from buffer as it is
                                 * already present */
                                key_desc->pressed_keys[j] = NO_KEY;

                                key_found = true;

                                break;
                        }

                }

                /* Remove key scancode from USB report as it it's not pressed
                 * anymore */
                if (false == key_found) {
                        report->keys[i] = NO_KEY;
                }

                key_found = false;
        }

        key_desc->pressed_cnt = fill_buffer_gaps(key_desc->pressed_keys,
                                                 key_desc->pressed_cnt);
        /* TODO: Maybe also need to do the same with report buffer here? */
}

static
void fill_usb_report_keys_buffer(keyboard_desc_st_t *key_desc,
        usb_report_st_t *report)
{
        int start_idx = 0;
        int key_idx = 0;

        start_idx = fill_buffer_gaps(report->keys, MAX_PRESSED_IN_REPORT);

        for (; start_idx < MAX_PRESSED_IN_REPORT; start_idx++) {
                if (NO_KEY == key_desc->pressed_keys[key_idx]) {
                        break;
                }

                report->keys[start_idx] = key_desc->pressed_keys[key_idx];
                key_idx++;
        }
}

void prepare_send_buffer(keyboard_desc_st_t *key_desc, usb_report_st_t *report)
{
        if (NULL == key_desc || NULL == report) {
                return;
        }

        set_modifier_keys(key_desc, report);

        prepare_buffers(key_desc, report);

        fill_usb_report_keys_buffer(key_desc, report);
}
