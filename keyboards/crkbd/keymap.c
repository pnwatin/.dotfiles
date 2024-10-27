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

// FIX: this resolve the issue with mith modifier keys and shifted keycodes (here # and $)
// see: https://github.com/qmk/qmk_firmware/issues/50
enum custom_keycodes {
    CTL_HASH = SAFE_RANGE,
    ALT_DLR,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t tap_timer;
    switch (keycode) {
        case CTL_HASH:
            if (record->event.pressed) {
                tap_timer = timer_read();
                register_code(KC_LCTL);
            } else {
                unregister_code(KC_LCTL);
                if (timer_elapsed(tap_timer) < TAPPING_TERM) {
                    tap_code16(LSFT(KC_3));
                }
            }
            return false;
        case ALT_DLR:
            if (record->event.pressed) {
                tap_timer = timer_read();
                register_code(KC_LALT);
            } else {
                unregister_code(KC_LALT);
                if (timer_elapsed(tap_timer) < TAPPING_TERM) {
                    tap_code16(LSFT(KC_4));
                }
            }
            return false;
    }
    return true;
}

// BASE layer home row mods
// Left-hand
#define CTL_A LCTL_T(KC_A)
#define ALT_S LALT_T(KC_S)
#define GUI_D LGUI_T(KC_D)
#define SFT_F LSFT_T(KC_F)

// Right-hand
#define SFT_J RSFT_T(KC_J)
#define GUI_K RGUI_T(KC_K)
#define ALT_L LALT_T(KC_L)
#define CTL_SCLN RCTL_T(KC_SCLN)

// NUM layer home row mods
// Left-hand
// #define CTL_HASH MT(MOD_LCTL, KC_HASH)
// #define ALT_DLR MT(MOD_LALT, KC_DLR)
#define GUI_LCBR LGUI_T(KC_LCBR)
#define SFT_RCBR LSFT_T(KC_RCBR)

// Right-hand
#define SFT_4 RSFT_T(KC_4)
#define GUI_5 RGUI_T(KC_5)
#define ALT_6 LALT_T(KC_6)
#define CTL_QUOT RCTL_T(KC_QUOT)

#define RALT_DEL RALT_T(KC_SPC)

#define NAV_ESC LT(1, KC_ESC)
#define NUM_TAB LT(2, KC_TAB)
#define MDI_SPC LT(3, KC_SPC)
#define FN_ENT LT(4, KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // BASE layer ✅
  [0] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX,   CTL_A,   ALT_S,   GUI_D,   SFT_F,    KC_G,                         KC_H,   SFT_J,   GUI_K,   ALT_L,CTL_SCLN, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           NAV_ESC, NUM_TAB, MDI_SPC,     FN_ENT, KC_BSPC,RALT_DEL
                                       //`--------------------------'  `--------------------------'
   ),

  // NAV layer ✅
  [1] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           _______, XXXXXXX, XXXXXXX,     KC_ENT, KC_BSPC,  KC_DEL
                                       //`--------------------------'  `--------------------------'
    ),

  // NUM and SYM layer ✅
  [2] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, KC_EXLM,   KC_AT, KC_LPRN, KC_RPRN, KC_AMPR,                      KC_PLUS,    KC_7,    KC_8,    KC_9, KC_ASTR, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX,CTL_HASH, ALT_DLR,GUI_LCBR,SFT_RCBR,  KC_GRV,                       KC_EQL,   SFT_4,   GUI_5,   ALT_6,CTL_QUOT, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, KC_PERC, KC_CIRC, KC_LCBR, KC_RCBR, KC_PIPE,                      KC_MINS,    KC_1,    KC_2,    KC_3, KC_BSLS, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX, _______, XXXXXXX,     KC_ENT, KC_UNDS,    KC_0
                                       //`--------------------------'  `--------------------------'
    ),


  // MEDIA layer ✅
  [3] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT,    KC_G,                      XXXXXXX, KC_MRWD, KC_VOLD, KC_VOLU, KC_MFFD, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, KC_BRID, KC_BRIU, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX, XXXXXXX, _______,    KC_MSTP, KC_MPLY, KC_MUTE
                                       //`--------------------------'  `--------------------------'
    ),

  // FN layer ✅
  [4] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX,  KC_F12,   KC_F7,   KC_F8,   KC_F9, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX,  KC_F11,   KC_F4,   KC_F5,   KC_F6, XXXXXXX,                      XXXXXXX, KC_RSFT, KC_RGUI, KC_LALT, KC_RCTL, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX,  KC_F10,   KC_F1,   KC_F2,   KC_F3, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX, XXXXXXX, XXXXXXX,    _______, XXXXXXX, XXXXXXX
                                       //`--------------------------'  `--------------------------'
    ),
};
