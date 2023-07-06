#include <string.h>

#include "key_manager.h"
#include "key_layout_provider.h"
#include "key_buffers_manager.h"

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

static inline
button_state_t is_home_pressed(void)
{
        return is_single_key_pressed(1, 15);
}

static inline
button_state_t is_del_pressed(void)
{
        return is_single_key_pressed(0, 15);
}

static inline
button_state_t is_fn_pressed(void)
{
        uint8_t row_index = 0;
        uint8_t col_index = 0;

        row_index = get_fn_row_index();
        col_index = get_fn_col_index();

        return is_single_key_pressed(row_index, col_index);
}

static
os_t switch_os(keyboard_desc_st_t *key_desc)
{
        bool flag = false;
        os_t ret_os = OS_WINDOWS;

        if (NULL == key_desc) {
                return OS_MAC;
        }

        flag = key_desc->functional.os_state;

        if (flag) {
                ret_os = OS_WINDOWS;
        } else {
                ret_os = OS_MAC;
        }

        key_desc->functional.os_state = !flag;

        return ret_os;
}

static
void fill_consumer_keys(keyboard_desc_st_t *key_desc, uint8_t write_index,
        uint8_t map_index)
{
        uint8_t *keys_layout = NULL;

        keys_layout = key_desc->consumer_layout;

        key_desc->pressed_consumer |= keys_layout[map_index];
}

static
void fill_regular_keys(keyboard_desc_st_t *key_desc, uint8_t write_index,
        uint8_t map_index)
{
        uint8_t *pressed_keys = NULL;
        uint8_t *keys_layout = NULL;

        pressed_keys = key_desc->pressed_keys;
        keys_layout = key_desc->keys_layout;

        pressed_keys[write_index] = keys_layout[map_index];
}

/* TODO: pressed_cnt is optional */
static
void do_when_key_pressed(keyboard_desc_st_t *key_desc, uint8_t row_index,
        uint8_t *pressed_cnt,
        void (*handler)(keyboard_desc_st_t *, uint8_t, uint8_t))
{
        button_state_t state = BUTTON_RELEASED;
        uint8_t pressed = 0;
        uint8_t keymap_indx = 0;
        uint8_t j = 0;

        if (NULL == key_desc || NULL == handler) {
                return;
        }

        update_row_gpio_state(ACTIVATE, row_index);
        for (j = 0; j < key_desc->keys_col_cnt; j++) {
                state = get_button_state(j);
                if (BUTTON_RELEASED == state) {
                        continue;
                }

                keymap_indx = row_index * key_desc->keys_col_cnt + j;
                handler(key_desc, *pressed_cnt, keymap_indx);

                (*pressed_cnt)++;
        }

        update_row_gpio_state(DEACTIVATE, row_index);
}

static
void process_layout_switch(keyboard_desc_st_t *key_desc)
{
        button_state_t home_state = BUTTON_RELEASED;
        os_t os = OS_MAC;

        home_state = is_home_pressed();
        if (BUTTON_PRESSED == home_state &&
            BUTTON_PRESSED != key_desc->functional.home_prev) {
                /* need to add counting down timer? */
                os = switch_os(key_desc);
                key_desc->keys_layout = get_keys_layout(os);
        }

        key_desc->functional.home_prev = home_state;
}

static
void process_reboot_bootloader(keyboard_desc_st_t *key_desc)
{
        bool time_passed = false;
        button_state_t del_state = BUTTON_RELEASED;

        del_state = is_del_pressed();
        if (BUTTON_PRESSED != del_state) {
                key_desc->functional.time_initialized = false;
                timer_clean_time();

                /* No reboot bootloader */
                return;
        }

        if (false == key_desc->functional.time_initialized) {
                key_desc->functional.time_initialized = true;
                timer_set_current_time();

                return;
        }

        time_passed = is_time_passed_ms(5000);
        if (true == time_passed) {
                reboot_bootloader();

                /* Should not back here */
                return;
        }
}

static
button_state_t process_fn_key(keyboard_desc_st_t *key_desc)
{
        button_state_t fn_state = BUTTON_RELEASED;

        if (NULL == key_desc) {
                return BUTTON_RELEASED;
        }

        fn_state = is_fn_pressed();
        if (BUTTON_RELEASED == fn_state) {
                return fn_state;
        }

        process_layout_switch(key_desc);

        process_reboot_bootloader(key_desc);

        return BUTTON_PRESSED;
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

