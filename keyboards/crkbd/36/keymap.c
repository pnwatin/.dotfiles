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

#include "features/achordion.h"
#include QMK_KEYBOARD_H

  // BASE layer home row mods
#define CTL_A LCTL_T(KC_A)
#define ALT_R LALT_T(KC_R)
#define GUI_S LGUI_T(KC_S)
#define SHT_T LSFT_T(KC_T)

#define SFT_N RSFT_T(KC_N)
#define GUI_E RGUI_T(KC_E)
#define ALT_I LALT_T(KC_I)
#define CTL_O RCTL_T(KC_O)

// LAYER keys
#define ALT_ESC RALT_T(KC_ESC)
#define NAV_TAB LT(1, KC_TAB)
#define NUM_SPC LT(2, KC_SPC)
#define SYM_BSP LT(3, KC_BSPC)
#define EXT_ENT LT(4, KC_ENT)
#define MDI_CWT LT(5, KC_F23)

enum custom_keycodes {
    THIN_ARR = SAFE_RANGE,
    FAT_ARR,
    D_ANGL,
    EMAIL1,
    EMAIL2,
    EMAIL3,
    PHONE
};

enum {
    MIUN,
    EQPL,
    PIBS,
    GRTI
};

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            tap_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

tap_dance_action_t tap_dance_actions[] = {
    [MIUN] = ACTION_TAP_DANCE_TAP_HOLD(KC_MINS, KC_UNDS),
    [EQPL] = ACTION_TAP_DANCE_TAP_HOLD(KC_EQL, KC_PLUS),
    [PIBS] = ACTION_TAP_DANCE_TAP_HOLD(KC_PIPE, KC_BSLS),
    [GRTI] = ACTION_TAP_DANCE_TAP_HOLD(KC_GRV, KC_TILD),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(MIUN):
        case TD(EQPL):
        case TD(PIBS):
        case TD(GRTI):
            return 100;
        default:
            return TAPPING_TERM;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_achordion(keycode, record)) { return false; }

    tap_dance_action_t *action;

    switch (keycode) {
        case TD(EQPL):
        case TD(PIBS):
        case TD(GRTI):
            action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
        case TD(MIUN): {
            if (is_caps_word_on()) {
                if (!record->event.pressed) {
                    tap_code16(KC_UNDS);
                }

                return false;
            }

            action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
        }
        case MDI_CWT:
            if (record->tap.count && record->event.pressed) {
                caps_word_toggle();
                return false;
            }
            break;
        case THIN_ARR:
            if (record->event.pressed) {
                SEND_STRING("-> ");
                return false;
            }
            break;
        case FAT_ARR:
            if (record->event.pressed) {
                SEND_STRING("=> ");
                return false;
            }
            break;
        case D_ANGL:
            if (record->event.pressed) {
                SEND_STRING("<>");
                tap_code16(KC_LEFT);
                return false;
            }
            break;
        case EMAIL1:
            if (record->event.pressed) {
                SEND_STRING("pnwa@icloud.com");
                return false;
            }
            break;
        case EMAIL2:
            if (record->event.pressed) {
                SEND_STRING("nicolas@nivalis.studio");
                return false;
            }
            break;
        case EMAIL3:
            if (record->event.pressed) {
                SEND_STRING("watinpn@gmail.com");
                return false;
            }
            break;
        case PHONE:
            if (record->event.pressed) {
                SEND_STRING("0638033148");
                return false;
            }
            break;
    }
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
       XXXXXXX,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX,   CTL_A,   ALT_R,   GUI_S,   SHT_T,    KC_G,                         KC_M,   SFT_N,   GUI_E,   ALT_I,   CTL_O, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           ALT_ESC, NAV_TAB, NUM_SPC,    EXT_ENT, SYM_BSP, MDI_CWT
                                       //`--------------------------'  `--------------------------'
   ),

  // NAV layer ✅
  [1] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_LBRC, KC_RBRC, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX, _______, XXXXXXX,     KC_ENT, KC_BSPC,  KC_DEL
                                       //`--------------------------'  `--------------------------'
   ),

  // NUM layer ✅
  [2] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,    KC_7,    KC_8,    KC_9, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX,                      XXXXXXX,    KC_4,    KC_5,    KC_6, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                         KC_0,    KC_1,    KC_2,    KC_3, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX, XXXXXXX, _______,     KC_ENT, KC_BSPC,  KC_DEL
                                       //`--------------------------'  `--------------------------'
   ),

  // SYM layer ✅
  [3] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX,TD(GRTI), XXXXXXX, KC_ASTR, KC_AMPR,TD(PIBS),                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, KC_QUOT, KC_CIRC, KC_PERC,  KC_DLR,TD(EQPL),                      XXXXXXX, KC_RSFT, KC_RGUI, KC_LALT, KC_RCTL, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, KC_DQUO, KC_HASH,   KC_AT, KC_EXLM,TD(MIUN),                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX,   MO(4),  KC_SPC,    XXXXXXX, _______, XXXXXXX
                                       //`--------------------------'  `--------------------------'
   ),

  // EXTRA plus layer ✅
  [4] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX,   PHONE,  EMAIL3,  EMAIL2,  EMAIL1, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, XXXXXXX,  D_ANGL,THIN_ARR, FAT_ARR, XXXXXXX,                      XXXXXXX, KC_RSFT, KC_RGUI, KC_LALT, KC_RCTL, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX, XXXXXXX, XXXXXXX,    _______, XXXXXXX, XXXXXXX
                                       //`--------------------------'  `--------------------------'
   ),

  // MEDIA layer ✅
  [5] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, KC_MRWD, KC_VOLD, KC_VOLU, KC_MFFD, XXXXXXX,                      XXXXXXX, KC_RSFT, KC_RGUI, KC_LALT, KC_RCTL, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, QK_BOOT, KC_BRID, KC_BRIU, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           KC_MSTP, KC_MUTE, KC_MPLY,    XXXXXXX, XXXXXXX, _______
                                       //`--------------------------'  `--------------------------'
   ),
};


