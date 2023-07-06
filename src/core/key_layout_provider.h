#ifndef __KEY_LAYOUT_PROVIDER__
#define __KEY_LAYOUT_PROVIDER__

#include "key_scancodes.h"

typedef enum {
        OS_MAC     = 0,
        OS_LINUX   = 1,
        OS_WINDOWS = 2,
} os_t;

uint8_t *get_keys_layout(os_t os);
uint8_t *get_consumer_layout(void);

uint8_t get_keys_row_cnt(void);
uint8_t get_keys_col_cnt(void);

#endif /* __KEY_LAYOUT_PROVIDER__ */
