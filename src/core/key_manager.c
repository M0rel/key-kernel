#include "key_manager.h"
#include "ll_adapter.h"

static inline
uint8_t get_fn_row_index()
{
        return FN_KEY_ROW_INDEX;
}

static inline
uint8_t get_fn_col_index()
{
        return FN_KEY_COL_INDEX;
}

static
void update_row_gpio_state(gpio_action_t action, uint8_t index)
{
        update_row_gpio_state_ll(action, index);
}

static
button_state_t get_button_state(uint8_t index)
{
        bool state = false;

        state = get_button_state_ll(index);
        if (true == state) {
                return BUTTON_PRESSED;
        }

        return BUTTON_RELEASED;
}

static
button_state_t is_single_key_pressed(uint8_t row_index, uint8_t col_index)
{
        button_state_t state = BUTTON_RELEASED;

        update_row_gpio_state(ACTIVATE, row_index);
        state = get_button_state(col_index);
        update_row_gpio_state(DEACTIVATE, row_index);

        return state;
}

static
button_state_t is_fn_pressed(void)
{
        button_state_t state = BUTTON_PRESSED;
        uint8_t row_index = 0;
        uint8_t col_index = 0;

        bool time_passed = false;
        row_index = get_fn_row_index();
        col_index = get_fn_col_index();

        state = is_single_key_pressed(row_index, col_index);
        timer_set_current_time();

        while (BUTTON_PRESSED == state) {
                time_passed = is_time_passed_ms(2000);
                if (true == time_passed) {
                        reboot_bootloader();

                        /* Should not back here */
                        break;
                }

                state = is_single_key_pressed(row_index, col_index);
        }

        timer_clean_time();

        /* TODO: do we need it? */
        return state;
}

{
        uint8_t *pressed_keys = NULL;
        uint8_t *keys_layout = NULL;

                return;
        }







void get_pressed_keys(keyboard_desc_st_t *key_desc)
{
        button_state_t fn_state = BUTTON_RELEASED;
        uint8_t pressed_cnt = 0;
        int start_indx = 0;
        int i = 0;

        if (NULL == key_desc) {
                return;
        }

        memset(key_desc->pressed_keys, 0, 16);

        fn_state = process_fn_key(key_desc);
        if (BUTTON_PRESSED == fn_state) {
                do_when_key_pressed(key_desc, start_indx, &pressed_cnt,
                                    fill_consumer_keys);
                pressed_cnt = 0;
                start_indx = 1;
        }

        for (i = start_indx; i < key_desc->keys_row_cnt; i++) {
                do_when_key_pressed(key_desc, i, &pressed_cnt,
                                    fill_regular_keys);
        }

        key_desc->pressed_cnt = pressed_cnt;
}

