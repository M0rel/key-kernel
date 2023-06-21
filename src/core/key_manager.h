#ifndef __KEY_MANAGER_H__
#define __KEY_MANAGER_H__

#include <stdbool.h>
#include <stdint.h>

#define FN_KEY_ROW_INDEX        5
#define FN_KEY_COL_INDEX        10

typedef enum {
        BUTTON_RELEASED = 0,
        BUTTON_PRESSED  = 1,
} button_state_t;

/* TODO: Should it be in another file/layer? */
typedef struct keyboard_desc {
        uint8_t        *keys_layout;
        uint8_t        keys_row_cnt;
        uint8_t        keys_col_cnt;
        uint8_t        *pressed_keys;
        uint8_t        pressed_cnt;
        button_state_t fn_pressed;
} keyboard_desc_st_t;

void get_pressed_keys(keyboard_desc_st_t *key_desc);

#endif /* __KEY_MANAGER_H__ */
