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
#include QMK_KEYBOARD_H

#define TABR C(KC_TAB)
#define TABL C(S(KC_TAB))
#define RALTZ RALT_T(KC_Z)

// Home row mods
#define CTLA LCTL_T(KC_A)
#define ALTR LALT_T(KC_R)
#define GUIS LGUI_T(KC_S)
#define SFTT LSFT_T(KC_T)

#define SFTN RSFT_T(KC_N)
#define GUIE RGUI_T(KC_E)
#define ALTI LALT_T(KC_I)
#define CTLO RCTL_T(KC_O)

// Thumbs layers
#define NUMD LT(2, KC_D)
#define LSYMESC LT(3, KC_ESC)
#define RSYMBSP LT(4, KC_BSPC)
#define NAVSPC LT(1, KC_SPC)
#define EXTENT  LT(5, KC_ENT)

enum {
    ARR,
};

void dance_arrow(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        SEND_STRING("-> ");
    }

    if (state->count == 2) {
        SEND_STRING("=> ");
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [ARR] = ACTION_TAP_DANCE_FN(dance_arrow),
};

bool achordion_chord(uint16_t tap_hold_keycode,
                     keyrecord_t* tap_hold_record,
                     uint16_t other_keycode,
                     keyrecord_t* other_record) {
    switch (tap_hold_keycode) {
        case RALTZ:
        case EXTENT:
        case NAVSPC:
        case RSYMBSP:
        case LSYMESC: {
            return true;
        }
    }

    return achordion_opposite_hands(tap_hold_record, other_record);
}

const custom_shift_key_t custom_shift_keys[] = {
    {KC_DOT , KC_QUES}, // Shift . is ?
    {KC_COMM, KC_EXLM}, // Shift , is !
    {KC_COLN, KC_SCLN}, // Shift : is ;
    {KC_UNDS, KC_AT  }, // Shift _ is @
    {NAVSPC, KC_TAB  }, // Shift <space> is <tab>
    {KC_SPC, KC_TAB  }, // Shift <space> is <tab>
};

uint8_t NUM_CUSTOM_SHIFT_KEYS =
    sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_achordion(keycode, record)) { return false; }
    if (!process_custom_shift_keys(keycode, record)) { return false; }

    return true;
}

void matrix_scan_user(void) {
    achordion_task();
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // BASE layer ✅
  [0] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_QUOT, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX,    CTLA,    ALTR,    GUIS,    SFTT,    KC_G,                         KC_M,    SFTN,    GUIE,    ALTI,    CTLO, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX,   RALTZ,    KC_X,    KC_C,    NUMD,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, KC_UNDS, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            XXXXXXX, LSYMESC,  NAVSPC,     EXTENT, RSYMBSP, XXXXXXX
                                       //`--------------------------'  `--------------------------'
   ),

  // NAV layer ✅
  [1] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, CW_TOGG, XXXXXXX,                      XXXXXXX,   TABL,     TABR, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_HOME, KC_PGDN, KC_PGUP,  KC_END, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX, XXXXXXX, _______,     KC_ENT, KC_BSPC, XXXXXXX
                                       //`--------------------------'  `--------------------------'
    ),

  // NUM layer ✅
  [2] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, CW_TOGG, XXXXXXX,                      KC_ASTR,    KC_7,    KC_8,    KC_9, KC_PLUS, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX,                      KC_SLSH,    KC_4,    KC_5,    KC_6, KC_MINS, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX,                      KC_COMM,    KC_1,    KC_2,    KC_3,  KC_DOT, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX,  KC_ESC,  KC_SPC,       KC_0, KC_BSPC, XXXXXXX
                                       //`--------------------------'  `--------------------------'
   ),

  // LSYM layer ✅
  [3] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, CW_TOGG, XXXXXXX,                      KC_AMPR, TD(ARR), KC_RBRC, KC_LBRC, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX,                      KC_PIPE, KC_COLN, KC_RPRN, KC_LPRN, KC_SCLN, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       KC_GRV,  KC_DLR, KC_RCBR, KC_LCBR, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX, _______, XXXXXXX,     KC_ENT, KC_BSPC, XXXXXXX
                                       //`--------------------------'  `--------------------------'
    ),

  // RSYM layer ✅
  [4] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, XXXXXXX, KC_LABK, KC_RABK, KC_BSLS, KC_PERC,                      XXXXXXX, CW_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, KC_EXLM, KC_MINS, KC_PLUS,  KC_EQL, KC_HASH,                      XXXXXXX, KC_RSFT, KC_RGUI, KC_LALT, KC_RCTL, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, XXXXXXX, KC_SLSH, KC_ASTR, KC_CIRC, KC_TILD,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX,  KC_ESC,  KC_SPC,    XXXXXXX, _______, XXXXXXX
                                       //`--------------------------'  `--------------------------'
    ),

  // EXTRA layer ✅
  [5] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, QK_BOOT, XXXXXXX, KC_BRID, KC_BRIU, KC_MUTE,                      XXXXXXX, CW_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD, KC_VOLU, KC_MPLY,                      XXXXXXX, KC_RSFT, KC_RGUI, KC_LALT, KC_RCTL, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV, KC_MNXT, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX,  KC_ESC, CW_TOGG,    _______, XXXXXXX, XXXXXXX
                                       //`--------------------------'  `--------------------------'
   ),
};


