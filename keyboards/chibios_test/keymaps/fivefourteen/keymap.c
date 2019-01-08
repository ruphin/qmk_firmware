#include "fivefourteen.h"

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
    { F(0),    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC },
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
    { _______, _______, _______, _______, _______, _______, _______, F(1),    F(2)   , KC_PSCR, _______, _______, _______, _______ },
  }

};

enum function_id {
    KEY_0,
    KEY_1,
    KEY_2,
};

const uint16_t PROGMEM fn_actions[] = {
    [0]  = ACTION_FUNCTION(KEY_0),
    [1]  = ACTION_FUNCTION(KEY_1),
    [2]  = ACTION_FUNCTION(KEY_2),
};

void key_remap_unshift(keyrecord_t *record, const uint16_t kc)
{
    const uint8_t isShifted = get_mods()&MODS_SHIFT_MASK;
    if (record->event.pressed) {
        del_mods(isShifted);
        add_key(kc);
        send_keyboard_report();
        add_mods(isShifted);
    } else {
        del_key(kc);
        send_keyboard_report();
    }
}

void key_remap_shift(keyrecord_t *record, const uint16_t kc)
{
    const uint8_t isShifted = get_mods()&MODS_SHIFT_MASK;
    if (record->event.pressed) {
        if (!isShifted) {
            add_mods(MODS_SHIFT_MASK);
        }

        add_key(kc);
        send_keyboard_report();

        if (!isShifted) {
            del_mods(MODS_SHIFT_MASK);
        }
    } else {
        del_key(kc);
        send_keyboard_report();
    }
}

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {

    const uint8_t isShifted = get_mods()&MODS_SHIFT_MASK;

    switch (id) {
        case KEY_0:
            if (isShifted) {
                key_remap_shift(record, KC_GRV);
            } else {
                key_remap_unshift(record, KC_ESC);
            }
            break;
        case KEY_1:
            key_remap_shift(record, KC_9);
            break;
        case KEY_2:
            key_remap_shift(record, KC_0);
            break;
    }
}
