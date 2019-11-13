#include QMK_KEYBOARD_H
#ifdef AUDIO_ENABLE
#include "muse.h"
#endif
#include "eeprom.h"
#include "keymap_german.h"
#include "keymap_nordic.h"
#include "keymap_french.h"
#include "keymap_spanish.h"
#include "keymap_hungarian.h"
#include "keymap_swedish.h"
#include "keymap_br_abnt2.h"
#include "keymap_canadian_multilingual.h"
#include "keymap_german_ch.h"
#include "keymap_jp.h"

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
#define ES_LESS_MAC KC_GRAVE
#define ES_GRTR_MAC LSFT(KC_GRAVE)
#define ES_BSLS_MAC ALGR(KC_6)
#define NO_PIPE_ALT KC_GRAVE
#define NO_BSLS_ALT KC_EQUAL


typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

enum planck_keycodes {
  RGB_SLD = EZ_SAFE_RANGE,
  RANSWORLD,
  EMDASH,
  ENDASH,
  CENT,
  DEGREES,
  MINUS1,
  MINUS3
};

//Tap Dance Declarations
enum {
  CT_CLN = 0,
  CT_APOST, //apostrophe, quote
  APOST_CTL, //apostrophe, quote, ctrl, alt
  SPACE_SHIFT, //tap space, hold shift, double tap hold space
  CT_SE,
  X_CTL //x, esc, ctrl, alt
};

enum unicode_names {
    BANG,
    IRONY,
    SNEK
};

int cur_dance (qk_tap_dance_state_t *state);

void x_finished (qk_tap_dance_state_t *state, void *user_data);
void x_reset (qk_tap_dance_state_t *state, void *user_data);
void apost_finished (qk_tap_dance_state_t *state, void *user_data);
void apost_reset (qk_tap_dance_state_t *state, void *user_data);
void space_finished (qk_tap_dance_state_t *state, void *user_data);
void space_reset (qk_tap_dance_state_t *state, void *user_data);

enum planck_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
  _LAYER4,
  _LAYER5,
  _LAYER6,
  _LAYER7,
  _LAYER8,
  _LAYER9,
  _LAYER10,
  _LAYER11,
  _LAYER12,
  _LAYER13,
  _LAYER14,
  _LAYER15,
  _LAYER16,
  _LAYER17,
  _LAYER18,
};


#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_planck_grid(LT(15,KC_ESCAPE),KC_Q,KC_W,KC_F,KC_P,KC_B,KC_J,KC_L,KC_U,KC_Y,OSM(MOD_LSFT),LT(14,KC_ENTER),
  	LCTL_T(KC_TAB),LT(9,KC_A),LALT_T(KC_R),LGUI_T(KC_S),LSFT_T(KC_T),KC_G,KC_M,RSFT_T(KC_N),RGUI_T(KC_E),RALT_T(KC_I),LT(9,KC_O),TD(CT_APOST),
  	MT(MOD_HYPR, KC_F16),LT(11,KC_Z),KC_X,KC_C,KC_D,KC_V,KC_K,KC_H,KC_COMMA,KC_DOT,KC_UP,TD(CT_CLN),
  	LCTL_T(KC_F18),LALT_T(KC_F19),LGUI_T(KC_F17),LT(8,KC_DELETE),LT(1,KC_BSPACE),KC_SPACE,KC_NO,LT(2,KC_ENTER),LT(13,KC_MINUS),KC_LEFT,KC_DOWN,KC_RIGHT),

  [_LOWER] = LAYOUT_planck_grid(KC_TRANSPARENT,LGUI(KC_DELETE),KC_HOME,KC_UP,KC_PGUP,LGUI(KC_2),KC_KP_SLASH,KC_KP_7,KC_KP_8,KC_KP_9,KC_MINUS,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_BSPACE,KC_LEFT,KC_DOWN,KC_RIGHT,LGUI(KC_3),KC_ASTR,KC_KP_4,KC_KP_5,KC_KP_6,KC_KP_PLUS,KC_LBRACKET,
  	KC_TRANSPARENT,KC_DELETE,KC_END,KC_TRANSPARENT,KC_PGDOWN,LGUI(LSFT(KC_4)),KC_PERC,KC_KP_1,KC_KP_2,KC_KP_3,KC_EQUAL,KC_RBRACKET,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,LSFT_T(KC_SPACE),KC_NO,KC_KP_0,KC_COMMA,KC_KP_DOT,KC_HOME,KC_END),

  [_RAISE] = LAYOUT_planck_grid(KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_PGUP,KC_UP,KC_HOME,KC_CAPSLOCK,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_LCTRL,KC_LALT,KC_LGUI,KC_LSHIFT,KC_TRANSPARENT,KC_BSPACE,KC_LEFT,KC_DOWN,KC_RIGHT,KC_DELETE,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_PGDOWN,KC_TRANSPARENT,KC_END,KC_PGUP,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,LSFT_T(KC_SPACE),KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_HOME,KC_PGDOWN,KC_END),

  [_ADJUST] = LAYOUT_planck_grid(RGB_HUI,RGB_HUD,AU_TOG,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,RESET,
  	RGB_VAI,RGB_VAD,MU_TOG,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
  	RGB_MOD,RGB_SLD,MU_MOD,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
  	TOGGLE_LAYER_COLOR,RGB_TOG,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_SPACE,KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

  [_LAYER4] = LAYOUT_planck_grid(LT(15,KC_ESCAPE),KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
  	LCTL_T(KC_TAB),LT(10,KC_A),KC_TRANSPARENT,LCTL_T(KC_S),KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,RCTL_T(KC_E),KC_TRANSPARENT,LT(10,KC_O),KC_TRANSPARENT,
  	MT(MOD_MEH, KC_F16),LT(12,KC_Z),KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_LGUI,KC_TRANSPARENT,LT(5,KC_BSPACE),KC_TRANSPARENT,KC_NO,LT(6,KC_ENTER),KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

  [_LAYER5] = LAYOUT_planck_grid(KC_TRANSPARENT,KC_TRANSPARENT,KC_HOME,KC_UP,KC_PGUP,KC_TRANSPARENT,KC_KP_SLASH,KC_KP_7,KC_KP_8,KC_KP_9,KC_MINUS,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_BSPACE,KC_LEFT,KC_DOWN,KC_RIGHT,KC_TRANSPARENT,KC_KP_ASTERISK,KC_KP_4,KC_KP_5,KC_KP_6,KC_KP_PLUS,KC_LBRACKET,
  	KC_TRANSPARENT,KC_DELETE,KC_END,KC_TRANSPARENT,KC_PGDOWN,KC_TRANSPARENT,KC_PERC,KC_KP_1,KC_KP_2,KC_KP_3,KC_EQUAL,KC_RBRACKET,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_LGUI,KC_TRANSPARENT,KC_TRANSPARENT,LSFT_T(KC_SPACE),KC_NO,KC_KP_0,KC_COMMA,KC_KP_DOT,KC_HOME,KC_END),

  [_LAYER6] = LAYOUT_planck_grid(KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_PGUP,KC_UP,KC_HOME,KC_CAPSLOCK,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_LGUI,KC_LALT,KC_LCTRL,KC_LSHIFT,KC_TRANSPARENT,KC_BSPACE,KC_LEFT,KC_DOWN,KC_RIGHT,KC_DELETE,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_PGDOWN,KC_TRANSPARENT,KC_END,KC_PGUP,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_LGUI,KC_TRANSPARENT,KC_TRANSPARENT,LSFT_T(KC_SPACE),KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_HOME,KC_PGDOWN,KC_END),

  [_LAYER7] = LAYOUT_planck_grid(KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

  [_LAYER8] = LAYOUT_planck_grid(KC_MINUS,KC_PLUS,KC_KP_9,KC_KP_8,KC_KP_7,KC_TRANSPARENT,KC_TRANSPARENT,KC_KP_7,KC_KP_8,KC_KP_9,KC_TRANSPARENT,KC_TRANSPARENT,
  	KC_TRANSPARENT,MINUS3,KC_KP_6,KC_KP_5,KC_KP_4,KC_TRANSPARENT,LALT(LCTL(LGUI(LSFT(KC_U)))),KC_KP_4,KC_KP_5,KC_KP_6,LALT(LCTL(LGUI(LSFT(KC_D)))),KC_TRANSPARENT,
  	KC_TRANSPARENT,MINUS1,KC_KP_3,KC_KP_2,KC_KP_1,KC_TRANSPARENT,LALT(LCTL(LGUI(LSFT(KC_I)))),KC_KP_1,KC_KP_2,KC_KP_3,KC_PGUP,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_KP_0,LALT(LCTL(LGUI(LSFT(KC_Y)))),KC_NO,KC_KP_0,KC_TRANSPARENT,KC_HOME,KC_PGDOWN,KC_END),

  [_LAYER9] = LAYOUT_planck_grid(KC_TRANSPARENT,KC_TRANSPARENT,LALT(LSFT(KC_8)),KC_AMPR,KC_LBRACKET,KC_BSLASH,KC_GRAVE,KC_RBRACKET,KC_HASH,LALT(KC_MINUS),KC_TRANSPARENT,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_EXLM,KC_QUES,KC_LPRN,KC_PIPE,KC_PERC,KC_RPRN,KC_DLR,KC_MINUS,KC_TRANSPARENT,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_UNDS,KC_AT,KC_LCBR,KC_SLASH,KC_TILD,KC_RCBR,LALT(KC_4),LALT(LSFT(KC_MINUS)),KC_TRANSPARENT,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,LGUI(LSFT(KC_S)),LGUI(KC_S),LGUI(KC_O),KC_NO,KC_F12,RANSWORLD,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

  [_LAYER10] = LAYOUT_planck_grid(KC_TRANSPARENT,KC_TRANSPARENT,DEGREES,KC_AMPR,KC_LBRACKET,KC_BSLASH,KC_GRAVE,KC_RBRACKET,KC_HASH,ENDASH,KC_TRANSPARENT,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_EXLM,KC_QUES,KC_LPRN,KC_PIPE,KC_PERC,KC_RPRN,KC_DLR,KC_MINUS,KC_TRANSPARENT,KC_TRANSPARENT,
  	KC_MEH,KC_TRANSPARENT,KC_UNDS,KC_AT,KC_LCBR,KC_SLASH,KC_TILD,KC_RCBR,CENT,EMDASH,KC_TRANSPARENT,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,LCTL(LSFT(KC_S)),LCTL(KC_S),LCTL(KC_O),KC_NO,KC_F12,RANSWORLD,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

  [_LAYER11] = LAYOUT_planck_grid(KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
  	LALT(LCTL(LGUI(LSFT(KC_K)))),KC_TRANSPARENT,KC_MAC_CUT,KC_MAC_COPY,KC_MAC_PASTE,LALT(LGUI(KC_V)),KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,LALT(KC_F4),LGUI(KC_Q),LGUI(KC_W),KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

  [_LAYER12] = LAYOUT_planck_grid(KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
  	KC_MEH,KC_TRANSPARENT,KC_PC_CUT,KC_PC_COPY,KC_PC_PASTE,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,LALT(KC_F4),LCTL(KC_Q),LCTL(KC_W),KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

  [_LAYER13] = LAYOUT_planck_grid(KC_TRANSPARENT,KC_TRANSPARENT,KC_F17,KC_F18,KC_F19,KC_TRANSPARENT,KC_TRANSPARENT,KC_F7,KC_F8,KC_F9,KC_TRANSPARENT,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_F14,KC_F15,KC_F16,KC_TRANSPARENT,KC_TRANSPARENT,KC_F4,KC_F5,KC_F6,KC_TRANSPARENT,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_F11,KC_F12,KC_F13,KC_TRANSPARENT,KC_TRANSPARENT,KC_F1,KC_F2,KC_F3,KC_TRANSPARENT,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_F20,KC_TRANSPARENT,KC_TRANSPARENT,KC_SPACE,KC_NO,KC_F10,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

  [_LAYER14] = LAYOUT_planck_grid(KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_AUDIO_MUTE,KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_MEDIA_PREV_TRACK,KC_MEDIA_PLAY_PAUSE,KC_NO,KC_MEDIA_NEXT_TRACK,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

  [_LAYER15] = LAYOUT_planck_grid(KC_TRANSPARENT,TO(0),TO(4),TT(17),TT(16),KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_SPACE,KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

  [_LAYER16] = LAYOUT_planck_grid(KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_MS_WH_UP,KC_MS_BTN1,KC_MS_UP,KC_MS_BTN2,KC_MS_ACCEL0,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_MS_BTN1,KC_MS_BTN2,KC_TRANSPARENT,KC_TRANSPARENT,KC_MS_WH_DOWN,KC_MS_LEFT,KC_MS_DOWN,KC_MS_RIGHT,KC_MS_ACCEL1,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_MS_WH_LEFT,KC_MS_WH_RIGHT,KC_TRANSPARENT,KC_TRANSPARENT,KC_MS_ACCEL2,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_SPACE,KC_NO,KC_TRANSPARENT,TO(15),KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

  [_LAYER17] = LAYOUT_planck_grid(KC_BSPACE,KC_Q,KC_W,KC_E,KC_R,KC_T,KC_Y,KC_U,KC_I,KC_O,KC_P,KC_ENTER,
  	KC_TAB,KC_A,KC_S,KC_D,KC_F,KC_G,KC_H,KC_J,KC_K,KC_L,KC_SCOLON,KC_QUOTE,
  	KC_LSHIFT,KC_Z,KC_X,KC_C,KC_V,KC_B,KC_N,KC_M,KC_COMMA,KC_DOT,KC_TRANSPARENT,KC_DELETE,
  	KC_LCTRL,KC_LALT,KC_LGUI,KC_ESCAPE,TT(18),KC_SPACE,KC_NO,KC_RCTRL,TO(15),KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

  [_LAYER18] = LAYOUT_planck_grid(KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_KP_SLASH,KC_KP_7,KC_KP_8,KC_KP_9,KC_MINUS,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_KP_ASTERISK,KC_KP_4,KC_KP_5,KC_KP_6,KC_KP_PLUS,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_PERC,KC_KP_1,KC_KP_2,KC_KP_3,KC_EQUAL,KC_TRANSPARENT,
  	KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_SPACE,KC_NO,KC_KP_0,KC_COMMA,KC_DOT,KC_KP_ENTER,KC_TRANSPARENT),

};

extern bool g_suspend_state;
extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [1] = { {0,0,0}, {0,0,0}, {0,0,0}, {237,255,255}, {0,0,0}, {0,0,255}, {0,0,0}, {237,255,255}, {237,255,255}, {237,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {8,255,255}, {8,255,255}, {8,255,255}, {0,0,255}, {0,0,0}, {8,255,255}, {8,255,255}, {8,255,255}, {0,0,0}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,0}, {24,255,255}, {24,255,255}, {24,255,255}, {0,0,0}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {170,230,255}, {0,0,0}, {35,255,255}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,255} },

    [2] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {237,255,255}, {0,0,0}, {0,0,255}, {0,0,0}, {0,0,0}, {105,255,255}, {249,255,255}, {35,255,255}, {170,230,255}, {0,0,0}, {0,0,0}, {8,255,255}, {8,255,255}, {8,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {170,230,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [3] = { {0,0,255}, {0,0,255}, {170,230,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,255,255}, {0,0,255}, {0,0,255}, {170,230,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,255}, {170,230,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,255}, {0,0,0}, {0,0,0}, {170,230,255}, {0,0,0}, {170,230,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [4] = { {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {129,255,255}, {129,255,255}, {129,255,255}, {129,255,255}, {129,255,255}, {129,255,255}, {129,255,255}, {129,255,255}, {129,255,255}, {129,255,255}, {129,255,255}, {129,255,255}, {170,230,255}, {170,230,255}, {170,230,255}, {170,230,255}, {170,230,255}, {170,230,255}, {170,230,255}, {170,230,255}, {170,230,255}, {170,230,255}, {170,230,255}, {170,230,255}, {209,255,255}, {209,255,255}, {209,255,255}, {209,255,255}, {209,255,255}, {209,255,255}, {209,255,255}, {209,255,255}, {209,255,255}, {209,255,255}, {209,255,255} },

    [5] = { {0,0,0}, {0,0,0}, {0,0,0}, {105,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {105,255,255}, {105,255,255}, {105,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {129,255,255}, {129,255,255}, {129,255,255}, {0,0,0}, {0,0,0}, {129,255,255}, {129,255,255}, {129,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {170,230,255}, {170,230,255}, {170,230,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {170,230,255}, {0,0,0}, {209,255,255}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,255} },

    [6] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {105,255,255}, {0,0,0}, {0,0,255}, {0,0,0}, {0,0,0}, {105,255,255}, {249,255,255}, {35,255,255}, {170,230,255}, {0,0,0}, {0,0,0}, {129,255,255}, {129,255,255}, {129,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {249,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [8] = { {0,0,0}, {0,0,0}, {105,255,255}, {105,255,255}, {105,255,255}, {0,0,0}, {0,0,0}, {105,255,255}, {105,255,255}, {105,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {129,255,255}, {129,255,255}, {129,255,255}, {0,0,0}, {0,0,255}, {129,255,255}, {129,255,255}, {129,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {170,230,255}, {170,230,255}, {170,230,255}, {0,0,0}, {0,0,255}, {170,230,255}, {170,230,255}, {170,230,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {209,255,255}, {0,0,0}, {209,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [9] = { {0,0,0}, {0,0,0}, {255,255,255}, {249,255,255}, {26,255,255}, {35,255,255}, {35,255,255}, {26,255,255}, {249,255,255}, {255,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {255,255,255}, {249,255,255}, {26,255,255}, {35,255,255}, {35,255,255}, {26,255,255}, {249,255,255}, {255,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {255,255,255}, {249,255,255}, {26,255,255}, {35,255,255}, {35,255,255}, {26,255,255}, {249,255,255}, {255,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {170,230,255}, {170,230,255}, {170,230,255}, {170,230,255}, {249,255,255}, {249,255,255}, {0,0,0}, {0,0,0} },

    [10] = { {0,0,0}, {0,0,0}, {255,255,255}, {249,255,255}, {26,255,255}, {35,255,255}, {35,255,255}, {26,255,255}, {249,255,255}, {255,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {255,255,255}, {249,255,255}, {26,255,255}, {35,255,255}, {35,255,255}, {26,255,255}, {249,255,255}, {255,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {255,255,255}, {249,255,255}, {26,255,255}, {35,255,255}, {35,255,255}, {26,255,255}, {249,255,255}, {255,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {170,230,255}, {170,230,255}, {170,230,255}, {170,230,255}, {249,255,255}, {249,255,255}, {0,0,0}, {0,0,0} },

    [11] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {249,255,255}, {249,255,255}, {26,255,255}, {35,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,255,255}, {0,255,255}, {0,255,143}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [12] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {249,255,255}, {249,255,255}, {26,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,255,255}, {0,255,255}, {0,255,143}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [13] = { {0,0,0}, {0,0,0}, {105,255,255}, {105,255,255}, {105,255,255}, {0,0,0}, {0,0,0}, {105,255,255}, {105,255,255}, {105,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {129,255,255}, {129,255,255}, {129,255,255}, {0,0,0}, {0,0,0}, {129,255,255}, {129,255,255}, {129,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {170,230,255}, {170,230,255}, {170,230,255}, {0,0,0}, {0,0,0}, {170,230,255}, {170,230,255}, {170,230,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {209,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {209,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [14] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [15] = { {0,0,0}, {35,255,255}, {209,255,255}, {0,255,255}, {0,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [16] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,255,255}, {0,0,0}, {0,0,0}, {0,0,0} },

    [17] = { {0,3,69}, {0,3,69}, {0,255,255}, {0,3,69}, {0,3,69}, {0,3,69}, {0,3,69}, {0,3,69}, {0,3,69}, {0,3,69}, {0,3,69}, {0,3,69}, {0,3,69}, {0,255,255}, {0,255,255}, {0,255,255}, {0,3,69}, {0,3,69}, {0,3,69}, {0,3,69}, {0,3,69}, {0,3,69}, {0,3,69}, {0,3,69}, {0,3,69}, {0,3,69}, {0,3,69}, {0,3,69}, {0,3,69}, {0,3,69}, {0,3,69}, {0,3,69}, {0,3,69}, {0,3,69}, {0,3,69}, {0,3,69}, {0,3,69}, {0,3,69}, {0,3,69}, {0,3,69}, {0,3,69}, {0,3,69}, {0,3,69}, {0,255,255}, {0,3,69}, {0,3,69}, {0,3,69} },

    [18] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,255,255}, {0,255,255}, {0,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,255,255}, {0,255,255}, {0,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,255,255}, {0,255,255}, {0,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

};

void set_layer_color(int layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

void rgb_matrix_indicators_user(void) {
  if (g_suspend_state || keyboard_config.disable_layer_led) { return; }
  switch (biton32(layer_state)) {
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
    case 3:
      set_layer_color(3);
      break;
    case 4:
      set_layer_color(4);
      break;
    case 5:
      set_layer_color(5);
      break;
    case 6:
      set_layer_color(6);
      break;
    case 8:
      set_layer_color(8);
      break;
    case 9:
      set_layer_color(9);
      break;
    case 10:
      set_layer_color(10);
      break;
    case 11:
      set_layer_color(11);
      break;
    case 12:
      set_layer_color(12);
      break;
    case 13:
      set_layer_color(13);
      break;
    case 14:
      set_layer_color(14);
      break;
    case 15:
      set_layer_color(15);
      break;
    case 16:
      set_layer_color(16);
      break;
    case 17:
      set_layer_color(17);
      break;
    case 18:
      set_layer_color(18);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
}

//Macro start
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
    case RANSWORLD:
      if (record->event.pressed) {
        SEND_STRING("ransworld@gmail.com");
      } else {
      }
      break;
    case EMDASH:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_5) SS_TAP(X_KP_1)));
      } else {
      }
      break;
    case ENDASH:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_5) SS_TAP(X_KP_0)));
      } else {
      }
      break;
    case CENT:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_6) SS_TAP(X_KP_2)));
      } else {
      }
      break;
    case DEGREES:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_7) SS_TAP(X_KP_6)));
      } else {
      }
      break;
    case MINUS1:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_MINUS) SS_TAP(X_KP_1));
      } else {
      }
      break;
    case MINUS3:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_MINUS) SS_TAP(X_KP_3));
      } else {
      }
      break;
  }
  return true;
}
//Macro finish

const uint32_t PROGMEM unicode_map[] = {
    [BANG]  = 0x203D,  // ‽
    [IRONY] = 0x2E2E,  // ⸮
    [SNEK]  = 0x1F40D, // 🐍
};

#ifdef AUDIO_ENABLE
bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
    if (muse_mode) {
        if (IS_LAYER_ON(_RAISE)) {
            if (clockwise) {
                muse_offset++;
            } else {
                muse_offset--;
            }
        } else {
            if (clockwise) {
                muse_tempo+=1;
            } else {
                muse_tempo-=1;
            }
        }
    } else {
        if (clockwise) {
        #ifdef MOUSEKEY_ENABLE
            register_code(KC_MS_WH_DOWN);
            unregister_code(KC_MS_WH_DOWN);
        #else
            register_code(KC_PGDN);
            unregister_code(KC_PGDN);
        #endif
        } else {
        #ifdef MOUSEKEY_ENABLE
            register_code(KC_MS_WH_UP);
            unregister_code(KC_MS_WH_UP);
        #else
            register_code(KC_PGUP);
            unregister_code(KC_PGUP);
        #endif
        }
    }
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
    case RAISE:
    case LOWER:
        return false;
    default:
        return true;
    }
}
#endif

uint32_t layer_state_set_user(uint32_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

//Tap Dance start
void dance_cln_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_RSFT);
    register_code (KC_SCLN);
  } else {
    register_code (KC_SCLN);
  }
}

void dance_cln_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_RSFT);
    unregister_code (KC_SCLN);
  } else {
    unregister_code (KC_SCLN);
  }
}

void dance_apost_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_QUOT);
  } else {
    register_code (KC_RSFT);
    register_code (KC_QUOT);
  }
}

void dance_apost_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_QUOT);
  } else {
    unregister_code (KC_RSFT);
    unregister_code (KC_QUOT);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
 [CT_CLN] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_cln_finished, dance_cln_reset)
 ,[CT_APOST] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_apost_finished, dance_apost_reset)
 ,[CT_SE] = ACTION_TAP_DANCE_DOUBLE (KC_SPC, KC_ENT)
 ,[X_CTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,x_finished, x_reset)
 ,[APOST_CTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,apost_finished, apost_reset)
 ,[SPACE_SHIFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,space_finished, space_reset)
};

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8;
}

static tap xtap_state = {
  .is_press_action = true,
  .state = 0
};

void x_finished (qk_tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_TAP: register_code(KC_X); break;
    case SINGLE_HOLD: register_code(KC_LCTRL); break;
    case DOUBLE_TAP: register_code(KC_ESC); break;
    case DOUBLE_HOLD: register_code(KC_LALT); break;
    case DOUBLE_SINGLE_TAP: register_code(KC_X); unregister_code(KC_X); register_code(KC_X);
  }
}

void x_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    case SINGLE_TAP: unregister_code(KC_X); break;
    case SINGLE_HOLD: unregister_code(KC_LCTRL); break;
    case DOUBLE_TAP: unregister_code(KC_ESC); break;
    case DOUBLE_HOLD: unregister_code(KC_LALT);
    case DOUBLE_SINGLE_TAP: unregister_code(KC_X);
  }
  xtap_state.state = 0;
}

static tap aposttap_state = {
  .is_press_action = true,
  .state = 0
};

void apost_finished (qk_tap_dance_state_t *state, void *user_data) {
  aposttap_state.state = cur_dance(state);
  switch (aposttap_state.state) {
    case SINGLE_TAP: register_code(KC_QUOT); break;
    case SINGLE_HOLD: register_code(KC_LCTRL); break;
    case DOUBLE_TAP: register_code(KC_X); break;
    case DOUBLE_HOLD: register_code(KC_LALT); break;
    case DOUBLE_SINGLE_TAP: register_code(KC_QUOT); unregister_code(KC_QUOT); register_code(KC_QUOT);
    case TRIPLE_TAP: register_code(KC_Z);
  }
}

void apost_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (aposttap_state.state) {
    case SINGLE_TAP: unregister_code(KC_QUOT); break;
    case SINGLE_HOLD: unregister_code(KC_LCTRL); break;
    case DOUBLE_TAP: unregister_code(KC_X); break;
    case DOUBLE_HOLD: unregister_code(KC_LALT);
    case DOUBLE_SINGLE_TAP: unregister_code(KC_QUOT);
    case TRIPLE_TAP: unregister_code(KC_Z);
  }
  aposttap_state.state = 0;
}

static tap spacetap_state = {
  .is_press_action = true,
  .state = 0
};

void space_finished (qk_tap_dance_state_t *state, void *user_data) {
  spacetap_state.state = cur_dance(state);
  switch (spacetap_state.state) {
    case SINGLE_TAP: register_code(KC_SPC); break;
    case SINGLE_HOLD: register_code(KC_LSFT); break;
    case DOUBLE_TAP: register_code(KC_MINS); break;
  }
}

void space_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (spacetap_state.state) {
    case SINGLE_TAP: unregister_code(KC_SPC); break;
    case SINGLE_HOLD: unregister_code(KC_LSFT); break;
    case DOUBLE_TAP: unregister_code(KC_MINS); break;
  }
  spacetap_state.state = 0;
}
//Tap dance finish