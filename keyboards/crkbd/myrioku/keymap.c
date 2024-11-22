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
#define CTL_QUO RCTL_T(KC_QUOT)

// Thumbs keys
#define SYM_ESC LT(3, KC_ESC)
#define NUM_TAB LT(2, KC_TAB)
#define NAV_SPC LT(1, KC_SPC)

#define ALT_ENT RALT_T(KC_ENT)
#define FN_DEL LT(4, KC_DEL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // BASE layer ✅
  [0] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX,   CTL_A,   ALT_S,   GUI_D,   SFT_F,    KC_G,                         KC_H,   SFT_J,   GUI_K,   ALT_L, CTL_QUO, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           SYM_ESC, NUM_TAB, NAV_SPC,    ALT_ENT, KC_BSPC,  FN_DEL
                                       //`--------------------------'  `--------------------------'
   ),

  // NAV layer ✅
  [1] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, CW_TOGG,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_HOME, KC_PGDN, KC_PGUP,  KC_END, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX, XXXXXXX, _______,    ALT_ENT, KC_BSPC,  KC_DEL
                                       //`--------------------------'  `--------------------------'
    ),

  // NUM layer ✅
  [2] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_LBRC,   KC_7,     KC_8,    KC_9, KC_RBRC, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, CW_TOGG,                       KC_EQL,    KC_4,    KC_5,    KC_6, KC_SCLN, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_BSLS,    KC_1,    KC_2,    KC_3,  KC_GRV, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX, _______, XXXXXXX,    KC_MINS,    KC_0,  KC_DOT
                                       //`--------------------------'  `--------------------------'
    ),

  // SYM layer ✅
  [3] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, CW_TOGG,                      KC_PLUS,  KC_DLR, KC_PERC, KC_CIRC, KC_COLN, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_PIPE, KC_EXLM,   KC_AT, KC_HASH, KC_TILD, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           _______, XXXXXXX, XXXXXXX,    KC_UNDS, KC_LPRN, KC_RPRN
                                       //`--------------------------'  `--------------------------'
    ),

  // MEDIA layer ✅
  [4] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, KC_MRWD, KC_VOLD, KC_VOLU, KC_MFFD, XXXXXXX,                      XXXXXXX, KC_RSFT, KC_RGUI, KC_LALT, KC_RCTL, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, QK_BOOT, KC_BRID, KC_BRIU, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           KC_MSTP, KC_MUTE, KC_MPLY,    XXXXXXX, XXXXXXX, _______
                                      //``--------------------------'  `--------------------------'
    ),
};

