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
bool is_fn_pressed(void)
{
        button_state_t state = BUTTON_RELEASED;
        uint8_t row_index = 0;
        uint8_t col_index = 0;

        row_index = get_fn_row_index();
        col_index = get_fn_col_index();

        update_row_gpio_state(ACTIVATE, row_index);
        state = get_button_state(col_index);
        update_row_gpio_state(DEACTIVATE, row_index);

        if (BUTTON_PRESSED == state) {
                return true;
        }

        return false;
}

void get_pressed_keys(keyboard_desc_st_t *key_desc)
{
        button_state_t state = BUTTON_RELEASED;
        uint8_t pressed_cnt = 0;
        uint8_t keymap_indx = 0;
        uint8_t *pressed_keys = NULL;
        uint8_t *keys_layout = NULL;
        int i = 0;
        int j = 0;

        if (NULL == key_desc) {
                return;
        }

        pressed_keys = key_desc->pressed_keys;
        keys_layout = key_desc->keys_layout;

        key_desc->fn_pressed = is_fn_pressed();

        for (i = 0; i < key_desc->keys_row_cnt; i++) {
                update_row_gpio_state(ACTIVATE, i);

                for (j = 0; j < key_desc->keys_col_cnt; j++) {
                        state = get_button_state(j);
                        if (BUTTON_RELEASED == state) {
                                continue;
                        }

                        /* To pass a pointers to array in a normal way it's
                         * decided to use single-dimensional array instead of
                         * two-dimensional.
                         * Example: Need to access element with index [2][2] of
                         * 4x4 two-dimensional array
                         * It may look like: 2 * 4 + 2 */
                        keymap_indx = i * key_desc->keys_col_cnt + j;
                        pressed_keys[pressed_cnt] = keys_layout[keymap_indx];

                        pressed_cnt++;
                }

                update_row_gpio_state(DEACTIVATE, i);
        }

        key_desc->pressed_cnt = pressed_cnt;
}

