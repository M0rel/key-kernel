#include <stdint.h>

#include "key_layout_provider.h"
#include "ll_adapter.h"

#if 0
#define KEY_ARRAY_ROW_CNT       6
#define KEY_ARRAY_COL_CNT       16


#define KEY_ARRAY_ROW_CNT       16
#define KEY_ARRAY_COL_CNT       6
#endif

#define KEY_ARRAY_ROW_CNT       6
#define KEY_ARRAY_COL_CNT       16


uint8_t consumer_layout[] = {
        /* Row 0 */
        NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY,
        /*F7    F8,     F9,     F10,    F11,    F12 */
        BIT(1), BIT(4), BIT(0), BIT(5), BIT(7), BIT(6),
        NO_KEY, NO_KEY, NO_KEY
};

uint8_t keys_layout_dflt[6 * 16] = {
        /* Col 0 */
        KEY_ESC, KEY_TILDE, KEY_TAB, KEY_CAPS_LOCK, KEY_LEFT_SHIFT,
        KEY_LEFT_CTRL,
        /* 0    1       2       3       4       5 */
        KEY_F1, KEY_1, KEY_Q, KEY_A, KEY_Z, KEY_LEFT_ALT,       /* Col 1 */
        /* 0    1       2       3       4       5 */
        KEY_F2, KEY_2, KEY_W, KEY_S, KEY_X, KEY_LEFT_GUI,  /* Col 2 */
        /* 0    1       2       3       4       5 */
        KEY_F3, KEY_3, KEY_E, KEY_D, KEY_C, NO_KEY,  /* Col 3 */
        /* 0    1       2       3       4       5 */
        KEY_F4, KEY_4, KEY_R, KEY_F, KEY_V, NO_KEY,  /* Col 4 */
        /* 0    1       2       3       4       5 */
        KEY_F5, KEY_5, KEY_T, KEY_G, KEY_B, KEY_SPACE,  /* Col 5 */
        /* 0    1       2       3       4       5 */
        KEY_F6, KEY_6, KEY_Y, KEY_H, KEY_N, NO_KEY,  /* Col 6 */
        /* 0    1       2       3       4       5 */
        KEY_F7, KEY_7, KEY_U, KEY_J, KEY_M, NO_KEY,  /* Col 7 */
        /* 0    1       2       3       4           5 */
        KEY_F8, KEY_8, KEY_I, KEY_K, KEY_LESS_THAN, KEY_RIGHT_ALT,  /* Col 8 */
        /* 0    1       2       3       4              5 */
        KEY_F9, KEY_9, KEY_O, KEY_L, KEY_GREATER_THAN, FN_KEY,  /* Col 9 */
        /* 0     1      2      3              4          5 */
        KEY_F10, KEY_0, KEY_P, KEY_SEMICOLON, KEY_SLASH, KEY_RIGHT_CTRL,  /* Col 10 */
        /* 0     1               2               3      */
        KEY_F11, KEY_UNDERSCORE, KEY_OPEN_BRACE, KEY_SINGLE_QUOTE,
        KEY_RIGHT_SHIFT, KEY_LEFT_ARROW,  /* Col 11 */
        /* 0     1          2                3          4       */
        KEY_F12, KEY_EQUAL, KEY_CLOSE_BRACE, KEY_ENTER, KEY_UP_ARROW,
        KEY_DOWN_ARROW,  /* Col 12 */
        /* 0          1           2              3       4       5 */
        KEY_PRT_SCRN, KEY_DELETE, KEY_BACKSLASH, NO_KEY, NO_KEY, NO_KEY,  /* Col 13 */
        /* 0           1       2       3              4       5 */
        KEY_SCRL_LOCK, NO_KEY, NO_KEY, KEY_BACKSLASH, NO_KEY, NO_KEY,   /* Col 14 */ 
        /* 0             1         2            3              4       */
        KEY_DELETE_FORW, KEY_HOME, KEY_PAGE_UP, KEY_PAGE_DOWN, KEY_END,
        KEY_RIGHT_ARROW,  /* Col 15 */
};

#if 0
uint8_t keys_layout_dflt[] = {
        /* Row 0 */
        KEY_ESC, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7,
        KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_PRT_SCRN,
        KEY_SCRL_LOCK, KEY_DELETE_FORW,
        /* Row 1 */
        KEY_TILDE, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7,
        KEY_8, KEY_9, KEY_0, KEY_UNDERSCORE, KEY_EQUAL, NO_KEY,
        KEY_DELETE, KEY_HOME,
        /* Row 2 */
        KEY_TAB, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I,
        KEY_O, KEY_P, KEY_OPEN_BRACE, KEY_CLOSE_BRACE, NO_KEY,
        KEY_BACKSLASH, KEY_PAGE_UP,
        /* Row 3 */
        KEY_CAPS_LOCK, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J,
        KEY_K, KEY_L, KEY_SEMICOLON, KEY_SINGLE_QUOTE, NO_KEY, NO_KEY,
        KEY_ENTER, KEY_PAGE_DOWN,
        /* Row 4 */
        KEY_LEFT_SHIFT, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M,
        KEY_LESS_THAN, KEY_GREATER_THAN, KEY_SLASH, KEY_RIGHT_SHIFT,
        NO_KEY, NO_KEY, KEY_UP_ARROW, KEY_END,
        /* Row 5 */
        KEY_LEFT_CTRL, KEY_LEFT_GUI, KEY_LEFT_ALT, KEY_SPACE, NO_KEY,
        NO_KEY, NO_KEY, NO_KEY, NO_KEY, KEY_RIGHT_ALT, FN_KEY,
        KEY_LEFT_ARROW, NO_KEY, NO_KEY, KEY_DOWN_ARROW, KEY_RIGHT_ARROW
};

uint8_t keys_layout_mac_dflt[] = {
        /* Row 0 */
        KEY_ESC, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_F13, KEY_F14, KEY_DELETE_FORW,
        /* Row 1 */
        KEY_TILDE, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, KEY_UNDERSCORE, KEY_EQUAL, NO_KEY, KEY_DELETE, KEY_HOME,
        /* Row 2 */
        KEY_TAB, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, KEY_OPEN_BRACE, KEY_CLOSE_BRACE, NO_KEY, KEY_BACKSLASH, KEY_PAGE_UP,
        /* Row 3 */
        KEY_CAPS_LOCK, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON, KEY_SINGLE_QUOTE, NO_KEY, NO_KEY, KEY_ENTER, KEY_PAGE_DOWN,
        /* Row 4 */
        KEY_LEFT_SHIFT, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M, KEY_LESS_THAN, KEY_GREATER_THAN, KEY_SLASH, KEY_RIGHT_SHIFT, NO_KEY, NO_KEY, KEY_UP_ARROW, KEY_END,
        /* Row 5 */
        KEY_LEFT_CTRL, KEY_LEFT_ALT, KEY_LEFT_GUI, KEY_SPACE, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, KEY_RIGHT_ALT, FN_KEY, KEY_LEFT_ARROW, NO_KEY, NO_KEY, KEY_DOWN_ARROW, KEY_RIGHT_ARROW
};
#endif

uint8_t *get_keys_layout(os_t os)
{
        switch (os) {
        case OS_MAC:
                //return keys_layout_mac_dflt;
        case OS_LINUX:
        case OS_WINDOWS:
        default:
                return keys_layout_dflt;
        }
}

uint8_t *get_consumer_layout(void)
{
        return consumer_layout;
}

uint8_t get_keys_row_cnt(void)
{
        return KEY_ARRAY_ROW_CNT;
}

uint8_t get_keys_col_cnt(void)
{
        return KEY_ARRAY_COL_CNT;
}
