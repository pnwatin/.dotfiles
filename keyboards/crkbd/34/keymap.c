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
#include QMK_KEYBOARD_H
#include "features/custom_shift_keys.h"
#include "features/swapper.h"

enum layers {
  BASE,
  NUM,
  NAV,
  SYM,
  META
};

enum custom_keycodes {
  SW_WIN = SAFE_RANGE,
  SW_LANG,
  NUMWORD,
  CANCEL,
};

enum tap_dances {
  TD_ARROWS
};

// HOMEROW
#define HRM_A LCTL_T(KC_A)
#define HRM_R LT(SYM, KC_R)
#define HRM_S LGUI_T(KC_S)
#define HRM_T LSFT_T(KC_T )
#define HRM_D LT(NUM, KC_D)

#define HRM_N RSFT_T(KC_N)
#define HRM_E RGUI_T(KC_E)
#define HRM_I LT(SYM, KC_I)
#define HRM_O RCTL_T(KC_O)

// THUMBROW
#define TRM_ESC LALT_T(KC_ESC)
#define TRM_SPC LT(NAV, KC_SPC)

#define TRM_BSPC RALT_T(KC_BSPC)
#define TRM_ENT LT(META, KC_ENT)

// TABS
#define RGHT_TAB C(KC_TAB)
#define LEFT_TAB C(S(KC_TAB))
#define SFT_TAB S(KC_TAB)

// TAP DANCES
#define ARROWS TD(TD_ARROWS)

// OTHERS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_QUOT, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX,   HRM_A,   HRM_R,   HRM_S,   HRM_T,    KC_G,                         KC_M,   HRM_N,   HRM_E,   HRM_I,   HRM_O, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX,    KC_Z,    KC_X,    KC_C,   HRM_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, KC_UNDS, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX, TRM_ESC, TRM_SPC,    TRM_ENT,TRM_BSPC, XXXXXXX
                                       //`--------------------------'  `--------------------------'
   ),
  [NUM] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,    KC_7,    KC_8,    KC_9, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                         KC_0,    KC_1,    KC_2,    KC_3, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,    KC_4,    KC_5,    KC_6, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX,  KC_ESC,  KC_SPC,    QK_LLCK, KC_BSPC, XXXXXXX
                                       //`--------------------------'  `--------------------------'
   ),
  [NAV] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_HOME, KC_PGDN, KC_PGUP,  KC_END, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,  SW_WIN, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     LEFT_TAB,  KC_TAB, SFT_TAB,RGHT_TAB, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX, XXXXXXX, _______,     KC_ENT,  KC_DEL, XXXXXXX
                                       //`--------------------------'  `--------------------------'
   ),
  [SYM] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, XXXXXXX, KC_LABK, KC_RABK, KC_SLSH, KC_AMPR,                      KC_CIRC, KC_RCBR, KC_LCBR,  KC_DLR,  KC_GRV, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, KC_EXLM, KC_ASTR, KC_MINS,  KC_EQL, KC_PIPE,                      KC_HASH, KC_RPRN, KC_LPRN,  ARROWS, KC_SCLN, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, KC_TILD, KC_PLUS, KC_LBRC, KC_RBRC, KC_PERC,                      KC_BSLS, KC_COLN, KC_COMM,  KC_DOT, KC_UNDS, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX, _______, _______,    _______, _______, XXXXXXX
                                       //`--------------------------'  `--------------------------'
   ),
  [META] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, QK_BOOT, XXXXXXX, KC_BRID, KC_BRIU, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, SW_LANG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX
                                       //`--------------------------'  `--------------------------'
   ),
};

// SWAPPERS booleans
bool sw_win_active = false;
bool sw_lang_active = false;

// COMBOS
const uint16_t one_shot_shift[] PROGMEM = {TRM_SPC, TRM_ENT, COMBO_END};
const uint16_t capsword[] PROGMEM = {HRM_T, HRM_N, COMBO_END};

combo_t key_combos[] = {
    COMBO(capsword, CW_TOGG),
    COMBO(one_shot_shift, OSM(MOD_LSFT)),
};

// TAP DANCES
void dance_arrow(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        SEND_STRING("-> ");
    }

    if (state->count == 2) {
        SEND_STRING("=> ");
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_ARROWS] = ACTION_TAP_DANCE_FN(dance_arrow),
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_swapper(
        &sw_win_active, MOD_MASK_GUI, KC_TAB, SW_WIN,
        keycode, record
    );
    update_swapper(
        &sw_lang_active, MOD_MASK_CTRL | MOD_MASK_ALT, KC_SPC, SW_LANG,
        keycode, record
    );

    if (!process_custom_shift_keys(keycode, record)) { return false; }

    switch (keycode) {
    }

    return true;
}

