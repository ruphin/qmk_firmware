/* Copyright 2024 ruphin<ruphin@ruphin.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H



// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Used for SHIFT_ESC
#define MODS_SHIFT_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

// Layer shorthand
#define _RP 0
#define _FN 1

/* ROW 1
 * .-----------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * '-----------------------------------------------------------------------------------------------------------------------------'
 */

/* ROW 2
 * .-----------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * '-----------------------------------------------------------------------------------------------------------------------------'
 */

/* ROW 3
 * .------------------------------------------------------------------------------------------------------------- 2u ------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |   X             |
 * '-----------------------------------------------------------------------------------------------------------------------------'
 */

/* ROW 4
 * .- 2u -------------------------------------------------------------------------------------------------------- 2u ------------.
 * |   X             |        |        |        |        |        |        |        |        |        |        |   X             |
 * '-----------------------------------------------------------------------------------------------------------------------------'
 */

/* ROW 5
 * .---------------------------------------------- 2u ---------------------------------------------------------------------------.
 * |        |        |        |        |        |   X             |        |        |        |        |        |        |        |
 * '-----------------------------------------------------------------------------------------------------------------------------'
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 /* RUPHIN
  * .-----------------------------------------------------------------------------------------------------------------------------.
  * | ESC  ~ | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      | -      | =      | BACKSP |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  * | TAB    | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | [      | ]      | NUMPAD |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ------------|
  * | FN     | A      | S      | D      | F      | G      | H      | J      | K      | L      | ;      | '      | ENTER  . XXXXXX |
  * |- 2u ------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ------------|
  * | LSHIFT . XXXXXX | Z      | X      | C      | V      | B      | N      | M      | ,      | .      | /      | RSHIFT . XXXXXX |
  * |-----------------+--------+--------+--------+- 2u ------------+--------+--------+--------+--------+--------+-----------------|
  * | LCTRL  | LGUI   | LALT   | \      | /      | SPACE  . XXXXXX | [      | ]      | PRSCR  | LEFT   | RIGHT  | UP     | DOWN   |
  * '-----------------------------------------------------------------------------------------------------------------------------'
  */

  [_RP] = { /* RUPHIN */
    { KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC },
    { KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_END  },
    { MO(_FN), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_ENT  },
    { KC_LSFT, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RSFT },
    { KC_LCTL, KC_LGUI, KC_LALT, KC_BSLS, KC_SLSH, KC_SPC,  KC_SPC,  KC_LBRC, KC_RBRC, KC_PSCR, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT },
  },


 /* FUNCTION
  * .-----------------------------------------------------------------------------------------------------------------------------.
  * | `      | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    | DEL    |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  * |        |        |        |        |        |        |        | HOME   | UP     | END    |        |        |        |        |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ------------|
  * |        |        |        |        |        |        |        | LEFT   | DOWN   | RIGHT  |        |        |        .        |
  * |- 2u ------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ------------|
  * |        .        |        |        |        |        |        | PGUP   |        | PGDWN  |        |        |        .        |
  * |-----------------+--------+--------+--------+- 2u ------------+--------+--------+--------+--------+--------+-----------------|
  * |        |        |        |        |        |        .        | (      | )      | PRSCR  |        |        |        |        |
  * '-----------------------------------------------------------------------------------------------------------------------------'
  */

  [_FN] = { /* FUNCTION */
    { KC_GRV,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_DEL },
    { _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_UP,   KC_END,  _______, _______, _______, _______ },
    { _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______ },
    { _______, _______, _______, _______, _______, _______, _______, KC_PGUP, _______, KC_PGDN, _______, _______, _______, _______ },
    { _______, _______, _______, _______, _______, _______, _______, S(KC_9), S(KC_0), KC_PSCR, _______, _______, _______, _______ },
  }

};

const key_override_t tilde_esc_override = ko_make_basic(MOD_MASK_SHIFT, KC_ESC, S(KC_GRV));


const key_override_t *key_overrides[] = {
	&tilde_esc_override
};
