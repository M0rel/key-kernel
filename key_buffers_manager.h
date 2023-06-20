#include "key_manager.h"

#define MAX_PRESSED_IN_REPORT   6

typedef struct usb_report {
        uint8_t id;
        uint8_t modifier;
        uint8_t reserved;
        uint8_t keys[MAX_PRESSED_IN_REPORT];
} usb_report_st_t;

void prepare_send_buffer(keyboard_desc_st_t *key_desc, usb_report_st_t *report);
