#ifndef __KEY_SCANCODES_H__
#define __KEY_SCANCODES_H__

#define NO_KEY  0
#define FN_KEY  0xFF

typedef enum {
        KEY_F1  = 0x3A,
        KEY_F2  = 0x3B,
        KEY_F3  = 0x3C,
        KEY_F4  = 0x3D,
        KEY_F5  = 0x3E,
        KEY_F6  = 0x3F,
        KEY_F7  = 0x40,
        KEY_F8  = 0x41,
        KEY_F9  = 0x42,
        KEY_F10 = 0x43,
        KEY_F11 = 0x44,
        KEY_F12 = 0x45
} key_f_t;

typedef enum {
        KEY_A = 0x4,
        KEY_B = 0x5,
        KEY_C = 0x6,
        KEY_D = 0x7,
        KEY_E = 0x8,
        KEY_F = 0x9,
        KEY_G = 0xA,
        KEY_H = 0xB,
        KEY_I = 0xC,
        KEY_J = 0xD,
        KEY_K = 0xE,
        KEY_L = 0xF,
        KEY_M = 0x10,
        KEY_N = 0x11,
        KEY_O = 0x12,
        KEY_P = 0x13,
        KEY_Q = 0x14,
        KEY_R = 0x15,
        KEY_S = 0x16,
        KEY_T = 0x17,
        KEY_U = 0x18,
        KEY_V = 0x19,
        KEY_W = 0x1A,
        KEY_X = 0x1B,
        KEY_Y = 0x1C,
        KEY_Z = 0x1D
} key_letters_t;

typedef enum {
        KEY_1 = 0x1E,
        KEY_2 = 0x1F,
        KEY_3 = 0x20,
        KEY_4 = 0x21,
        KEY_5 = 0x22,
        KEY_6 = 0x23,
        KEY_7 = 0x24,
        KEY_8 = 0x25,
        KEY_9 = 0x26,
        KEY_0 = 0x27
} key_nums_symb_t;

typedef enum {
        KEY_ENTER        = 0x28,
        KEY_ESC          = 0x29,
        KEY_DELETE       = 0x2A,
        KEY_TAB          = 0x2B,
        KEY_SPACE        = 0x2C,
        KEY_UNDERSCORE   = 0x2D,
        KEY_EQUAL        = 0x2E,
        KEY_OPEN_BRACE   = 0x2F,
        KEY_CLOSE_BRACE  = 0x30,
        KEY_BACKSLASH    = 0x31,
        KEY_TILDE_SHARP  = 0x32, /* Not used */
        KEY_SEMICOLON    = 0x33,
        KEY_SINGLE_QUOTE = 0x34,
        KEY_TILDE        = 0x35,
        KEY_LESS_THAN    = 0x36,
        KEY_GREATER_THAN = 0x37,
        KEY_SLASH        = 0x38,
        KEY_CAPS_LOCK    = 0x39,
        /**********************/
        KEY_PRT_SCRN     = 0x46,
        KEY_SCRL_LOCK    = 0x47,
        KEY_HOME         = 0x4A,
        KEY_PAGE_UP      = 0x4B,
        KEY_DELETE_FORW  = 0x4C,
        KEY_END          = 0x4D,
        KEY_PAGE_DOWN    = 0x4E,
        KEY_RIGHT_ARROW  = 0x4F,
        KEY_LEFT_ARROW   = 0x50,
        KEY_DOWN_ARROW   = 0x51,
        KEY_UP_ARROW     = 0x52,
        /**********************/
        KEY_LEFT_CTRL    = 0xE0,
        KEY_LEFT_SHIFT   = 0xE1,
        KEY_LEFT_ALT     = 0xE2,
        KEY_LEFT_GUI     = 0xE3,
        KEY_RIGHT_CTRL   = 0xE4,
        KEY_RIGHT_SHIFT  = 0xE5,
        KEY_RIGHT_ALT    = 0xE6,
        KEY_RIGHT_GUI    = 0xE7
} key_spec_symb_t;

typedef enum {
        KEY_MUTE        = 0x7F,
        KEY_VOLUME_UP   = 0x80,
        KEY_VOLUME_DOWN = 0x81,
} key_media_t;

#endif /* __KEY_SCANCODES_H__ */
