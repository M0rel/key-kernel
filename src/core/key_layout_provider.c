#include <stdint.h>

#include "key_layout_provider.h"
#include "ll_adapter.h"

#define KEY_ARRAY_ROW_CNT       6
#define KEY_ARRAY_COL_CNT       16

uint8_t consumer_layout[] = {
        /* Row 0 */
        NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, BIT(1),
        BIT(4), BIT(0), BIT(5), BIT(7), BIT(6), NO_KEY,
        NO_KEY, NO_KEY
};

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
        KEY_ESC, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7,
        KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_F13, KEY_F14,
        KEY_DELETE_FORW,
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
        KEY_LEFT_CTRL, KEY_LEFT_ALT, KEY_LEFT_GUI, KEY_SPACE, NO_KEY,
        NO_KEY, NO_KEY, NO_KEY, NO_KEY, KEY_RIGHT_ALT, FN_KEY,
        KEY_LEFT_ARROW, NO_KEY, NO_KEY, KEY_DOWN_ARROW, KEY_RIGHT_ARROW
};

uint8_t *get_keys_layout(os_t os)
{
        switch (os) {
        case OS_MAC:
                return keys_layout_mac_dflt;
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
