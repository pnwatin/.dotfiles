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
#include "features/achordion.h"
#include "features/swapper.h"
#include QMK_KEYBOARD_H

enum layers {
  BASE,
  NUM,
  NAV,
  SYM,
  WIN
};

enum {
  ARROW_DANCE
};

enum keycodes {
  SW_WIN = SAFE_RANGE,  // Switch to next window         (cmd-tab)
  SW_LANG,              // Switch to next input language (ctl-spc)
};

// HOMEROW
#define HRM_T LT(NAV, KC_T)
#define HRM_R LT(SYM, KC_R)
#define HRM_A LCTL_T(KC_A)
#define HRM_S LSFT_T(KC_S)
#define HRM_Z LALT_T(KC_Z)
#define HRM_D LGUI_T(KC_D)

#define HRM_N LT(NUM, KC_N)
#define HRM_I LT(SYM, KC_I)
#define HRM_DOT LT(WIN, KC_DOT)
#define HRM_E RSFT_T(KC_E)
#define HRM_O RCTL_T(KC_O)
#define HRM_UND LALT_T(KC_F23)
#define HRM_H RGUI_T(KC_H)

// TABS
#define RGHT_TAB C(KC_TAB)
#define LEFT_TAB C(S(KC_TAB))
#define SFT_TAB S(KC_TAB)

// WINDOWS MANAGEMENT
#define WIN_1 G(A(KC_1))
#define WIN_2 G(A(KC_2))
#define WIN_3 G(A(KC_3))
#define WIN_4 G(A(KC_4))
#define WIN_5 G(A(KC_5))
#define WIN_6 G(A(KC_6))
#define WIN_MAX G(A(KC_ENT))

// OTHERS
#define ALT_ESC RALT_T(KC_ESC)
#define ARROW TD(ARROW_DANCE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_QUOT, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX,   HRM_A,   HRM_R,   HRM_S,   HRM_T,    KC_G,                         KC_M,   HRM_N,   HRM_E,   HRM_I,   HRM_O, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX,   HRM_Z,    KC_X,    KC_C,   HRM_D,    KC_V,                         KC_K,   HRM_H, KC_COMM, HRM_DOT, HRM_UND, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX, ALT_ESC,  KC_SPC,     KC_ENT, KC_BSPC, XXXXXXX
                                       //`--------------------------'  `--------------------------'
   ),
  [NUM] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, KC_SLSH,    KC_9,    KC_8,    KC_7, KC_ASTR,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, KC_MINS,    KC_3,    KC_2,    KC_1, KC_PLUS,                      XXXXXXX, XXXXXXX, XXXXXXX, KC_RGUI, KC_RCTL, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX,    KC_X,    KC_6,    KC_5,    KC_4, KC_PERC,                      XXXXXXX, XXXXXXX, KC_COMM,  KC_DOT, KC_LALT, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX,    KC_0, _______,    QK_LLCK, _______, XXXXXXX
                                       //`--------------------------'  `--------------------------'
   ),
  [NAV] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_HOME, KC_PGDN, KC_PGUP,  KC_END, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, KC_LCTL, KC_LGUI, KC_LSFT, XXXXXXX, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, KC_LALT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     LEFT_TAB,  KC_TAB, SFT_TAB,RGHT_TAB, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX, XXXXXXX, XXXXXXX,    QK_LLCK, _______, XXXXXXX
                                       //`--------------------------'  `--------------------------'
   ),
  [SYM] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, XXXXXXX, KC_LABK, KC_RABK, KC_MINS, KC_PIPE,                      KC_CIRC, KC_RCBR, KC_LCBR,  KC_DLR,  KC_GRV, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, KC_EXLM, KC_ASTR, KC_SLSH,  KC_EQL, KC_AMPR,                      KC_HASH, KC_RPRN, KC_LPRN, KC_SCLN,   ARROW, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, KC_TILD, KC_PLUS, KC_LBRC, KC_RBRC, KC_PERC,                      KC_BSLS, KC_COLN, KC_COMM,  KC_DOT, KC_UNDS, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX, _______, _______,    _______, _______, XXXXXXX
                                       //`--------------------------'  `--------------------------'
   ),
  [WIN] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, QK_BOOT, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX,  SW_WIN,   WIN_3,   WIN_2,   WIN_1, WIN_MAX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, SW_LANG,   WIN_6,   WIN_5,   WIN_4, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX, XXXXXXX, XXXXXXX,    QK_LLCK, XXXXXXX, XXXXXXX
                                       //`--------------------------'  `--------------------------'
   ),
};

bool sw_win_active = false;
bool sw_lang_active = false;

const uint16_t caps_combo[] PROGMEM = {KC_C, KC_COMM, COMBO_END};

combo_t key_combos[] = {
    COMBO(caps_combo, CW_TOGG),          // C and , => activate Caps Word.
};

void dance_arrow(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        SEND_STRING("->");
    }

    if (state->count == 2) {
        SEND_STRING("=>");
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [ARROW_DANCE] = ACTION_TAP_DANCE_FN(dance_arrow),
};

const custom_shift_key_t custom_shift_keys[] = {
    {HRM_DOT , KC_QUES}, // Shift . is ?
    {KC_COMM, KC_EXLM},  // Shift , is !
    {HRM_UND, KC_AT},    // Shift _ is @
    {KC_BSPC, KC_DEL},   // Shift backspace is delete
};


uint8_t NUM_CUSTOM_SHIFT_KEYS =
    sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

bool achordion_chord(uint16_t tap_hold_keycode,
                     keyrecord_t* tap_hold_record,
                     uint16_t other_keycode,
                     keyrecord_t* other_record) {
    if (other_record->event.key.row % (MATRIX_ROWS / 2) >= 3) { return true; }

    switch (tap_hold_keycode) {
        case ALT_ESC: {
            return true;
        }
    }

    return achordion_opposite_hands(tap_hold_record, other_record);
}

bool achordion_eager_mod(uint8_t mod) {
    switch (mod) {
        case MOD_LSFT:
        case MOD_RSFT:
        case MOD_LCTL:
        case MOD_RCTL:
        case MOD_LGUI:
        case MOD_RGUI:
            return true;

        default:
            return false;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_swapper(
        &sw_win_active, KC_LGUI, KC_TAB, SW_WIN,
        keycode, record
    );
    update_swapper(
        &sw_lang_active, KC_LCTL, KC_SPC, SW_LANG,
        keycode, record
    );

    if (!process_achordion(keycode, record)) { return false; }
    if (!process_custom_shift_keys(keycode, record)) { return false; }


    switch (keycode) {
        case HRM_UND:
            if (record->event.pressed && record->tap.count > 0) {
                tap_code16(KC_UNDS);
                return false;
            }
        break;
    }

    return true;
}

