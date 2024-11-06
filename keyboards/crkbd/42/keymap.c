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

#define LALT_SPC LALT_T(KC_SPC)
#define GUI_ENT RGUI_T(KC_ENT)
#define NUM_BSPC LT(2, KC_BSPC)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // BASE layer ✅
  [0] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_ESC,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           KC_RGUI,   MO(1),LALT_SPC,    GUI_ENT,NUM_BSPC, KC_LALT
                                       //`--------------------------'  `--------------------------'
   ),

  [1] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSLS,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MINS,  KC_EQL,  KC_GRV, KC_LBRC, KC_RBRC, KC_PIPE,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_UNDS, KC_PLUS, KC_TILD, KC_LCBR, KC_RCBR, KC_RSFT,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX, _______, XXXXXXX,    GUI_ENT,  KC_DEL, KC_LALT
                                       //`--------------------------'  `--------------------------'
    ),

  // NUM layer ✅
  [2] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       CW_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, CW_TOGG,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           KC_RGUI,   MO(3),LALT_SPC,    XXXXXXX, _______, XXXXXXX
                                       //`--------------------------'  `--------------------------'
    ),

  // FN & MEDIA layer ✅
  [3] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       QK_BOOT,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, XXXXXXX, KC_VOLD, KC_VOLU, KC_MUTE, XXXXXXX,                      XXXXXXX, KC_MPLY, KC_MRWD, KC_MFFD, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, XXXXXXX, KC_BRID, KC_BRIU, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX, _______, XXXXXXX,    XXXXXXX, _______, XXXXXXX
                                      //``--------------------------'  `--------------------------'
    ),
};

