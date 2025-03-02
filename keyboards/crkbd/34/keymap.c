/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "features/custom_shift_keys.h"
#include "features/swapper.h"
#include QMK_KEYBOARD_H

enum layers {
  BASE,
  NUM,
  NAV,
  LSYM,
  RSYM,
  META
};

enum custom_keycodes {
  SW_WIN = SAFE_RANGE,
  SW_LANG,
  NUMWORD,
  CANCEL,
};

// HOMEROW
#define HRM_A LCTL_T(KC_A)
#define HRM_R LALT_T(KC_R)
#define HRM_S LGUI_T(KC_S)
#define HRM_T LSFT_T(KC_T)

#define HRM_N RSFT_T(KC_N)
#define HRM_E RGUI_T(KC_E)
#define HRM_I LALT_T(KC_I)
#define HRM_O RCTL_T(KC_O)

// THUMBROW
#define TRM_ESC LT(RSYM, KC_ESC)
#define TRM_SPC LT(NAV, KC_SPC)

#define TRM_BSPC LT(LSYM, KC_BSPC)
#define TRM_ENT LT(META, KC_ENT)

// TABS
#define RGHT_TAB C(KC_TAB)
#define LEFT_TAB C(S(KC_TAB))
#define SFT_TAB S(KC_TAB)

// WINDOWS MANAGEMENT
#define WIN_MAX G(A(KC_ENT))

// OTHERS
#define OS_RALT OSM(MOD_RALT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_QUOT, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX,   HRM_A,   HRM_R,   HRM_S,   HRM_T,    KC_G,                         KC_M,   HRM_N,   HRM_E,   HRM_I,   HRM_O, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, KC_UNDS, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX, TRM_ESC, TRM_SPC,    TRM_ENT,TRM_BSPC, XXXXXXX
                                       //`--------------------------'  `--------------------------'
   ),
  [NUM] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                         KC_J, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX,    KC_6,    KC_4,    KC_2,    KC_0, XXXXXXX,                      XXXXXXX,    KC_1,    KC_3,    KC_5,    KC_7, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_8, XXXXXXX,                         KC_K,    KC_9, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX, XXXXXXX,  KC_SPC,     CANCEL, KC_BSPC, XXXXXXX
                                       //`--------------------------'  `--------------------------'
   ),
  [NAV] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_HOME, KC_PGDN, KC_PGUP,  KC_END, SW_LANG, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,  SW_WIN, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     LEFT_TAB,  KC_TAB, SFT_TAB,RGHT_TAB, WIN_MAX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX, XXXXXXX, _______,     KC_TAB,  KC_DEL, XXXXXXX
                                       //`--------------------------'  `--------------------------'
   ),
  [LSYM] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, XXXXXXX, KC_LABK, KC_RABK, KC_MINS, KC_AMPR,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, KC_EXLM, KC_ASTR, KC_SLSH,  KC_EQL, KC_PIPE,                      XXXXXXX,    KC_1,    KC_3,    KC_5,    KC_7, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, KC_TILD, KC_PLUS, KC_LBRC, KC_RBRC, KC_PERC,                      XXXXXXX,    KC_9, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX, _______, _______,    _______, _______, XXXXXXX
                                       //`--------------------------'  `--------------------------'
   ),
  [RSYM] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_CIRC, KC_RCBR, KC_LCBR,  KC_DLR,  KC_GRV, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX,    KC_6,    KC_4,    KC_2,    KC_0, XXXXXXX,                      KC_HASH, KC_RPRN, KC_LPRN, KC_QUES, KC_SCLN, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_8, XXXXXXX,                      KC_BSLS, KC_COLN, KC_COMM,  KC_DOT, KC_UNDS, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX, _______, _______,    _______, _______, XXXXXXX
                                       //`--------------------------'  `--------------------------'
   ),
  [META] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, QK_BOOT, KC_BRID, KC_BRIU, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX
                                       //`--------------------------'  `--------------------------'
   ),
};

// SWAPPERS booleans
bool sw_win_active = false;
bool sw_lang_active = false;

// COMBOS
const uint16_t capsword[] PROGMEM = {HRM_T, HRM_N, COMBO_END};
const uint16_t numword[] PROGMEM = {TRM_SPC, TRM_ENT, COMBO_END};
const uint16_t os_ralt[] PROGMEM = {TRM_ESC, HRM_R, COMBO_END};

combo_t key_combos[] = {
    COMBO(capsword, CW_TOGG),
    COMBO(numword, NUMWORD),
    COMBO(os_ralt, OS_RALT),
};

// CUSTOM SHIFT
const custom_shift_key_t custom_shift_keys[] = {
    {KC_DOT , KC_QUES},
    {KC_COMM, KC_EXLM},
    {KC_UNDS, KC_AT},
    {KC_BSPC, KC_DEL},
};


uint8_t NUM_CUSTOM_SHIFT_KEYS =
    sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

// CHORAL HOLD
bool get_chordal_hold(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record,
                      uint16_t other_keycode, keyrecord_t* other_record) {
    switch (tap_hold_keycode) {
        case TRM_ESC:
        case TRM_BSPC:
            return true;
    }
    return get_chordal_hold_default(tap_hold_record, other_record);
}

// NUMWORD
static uint16_t num_word_timer;
static bool _num_word_enabled = false;

bool num_word_enabled(void) {
    return _num_word_enabled;
}

void enable_num_word(void) {
    _num_word_enabled = true;
    layer_on(NUM);
}

void disable_num_word(void) {
    _num_word_enabled = false;
    layer_off(NUM);
}

void process_num_word_activation(const keyrecord_t *record) {
    if (record->event.pressed) {
        layer_on(NUM);
        num_word_timer = timer_read();
    } else {
        if (timer_elapsed(num_word_timer) < TAPPING_TERM) {
            _num_word_enabled = true;
        } else {
            layer_off(NUM);
        }
    }
}
bool process_num_word(uint16_t keycode, const keyrecord_t *record) {
    if (!_num_word_enabled) return true;

    switch (keycode) {
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            if (record->tap.count == 0)
                return true;
            keycode = keycode & 0xFF;
    }

    switch (keycode) {
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_SPC:
        case XXXXXXX:
            break;
        case CANCEL:
            if (record->event.pressed) {
                disable_num_word();
            }
            return false;
        default:
            if (record->event.pressed) {
                disable_num_word();
            }
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_swapper(
        &sw_win_active, MOD_MASK_GUI, KC_TAB, SW_WIN,
        keycode, record
    );
    update_swapper(
        &sw_lang_active, MOD_MASK_CTRL | MOD_MASK_ALT, KC_SPC, SW_LANG,
        keycode, record
    );

    if (!process_num_word(keycode, record)) { return false; }

    if (!process_custom_shift_keys(keycode, record)) { return false; }

    switch (keycode) {
        case NUMWORD:
            process_num_word_activation(record);
            return false;
    }

    return true;
}

