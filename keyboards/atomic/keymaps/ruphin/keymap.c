#include "atomic.h"

// Fillers to make layering more clear
#define _______ KC_TRNS
#define ___T___ KC_TRNS
#define XXXXXXX KC_NO

// Used for SHIFT_ESC
#define MODS_SHIFT_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

// Layer shorthand
#define _RP 0
#define _FN 1
#define _NP 2

/* ROW 1 OPTIONS
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 *                                                                                                                      .- 2u ------------.
 *                                                                                                                      | KEY    . XXXXXX |
 *                                                                                                                      '-----------------'
 */

/* ROW 2 OPTIONS
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 * .- 2u ------------.                                                                                                  .- 2u ------------.
 * | KEY    . XXXXXX |                                                                                                  | KEY    . XXXXXX |
 * '-----------------'                                                                                                  '-----------------'
 */

/* ROW 3 OPTIONS
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 * .- 2u ------------.                                                                                         .- 2u ------------.
 * | KEY    . XXXXXX |                                                                                         |   X             |
 * '-----------------'                                                                                         '-----------------'
 *                                                                                                                      .- 2u ------------.
 *                                                                                                                      |   X             |
 *                                                                                                                      '-----------------'
 */

/* ROW 4 OPTIONS
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 *                                                                                                    .- 2u ------------.
 *                                                                                                    | KEY    . XXXXXX |
 *                                                                                                    '-----------------'
 * .- 2u ------------.                                                                                         .- 2u ------------.
 * | KEY    . XXXXXX |                                                                                         | KEY    . XXXXXX |
 * '-----------------'                                                                                         '-----------------'
 *                                                                                                                      .- 2u ------------.
 *                                                                                                                      | KEY    . XXXXXX |
 *                                                                                                                      '-----------------'
 */

/* ROW 5 OPTIONS
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 * .- 1.25u --+ 1.25u ------- 1.25u +--- 1.25u --- 2u -------------- 1.25u ---- 1.25u ------ 1.25u +---- 1.25u .
 * |   X      | X        |        X |      X    |   X             |   X      | X        |        X |      X    |
 * '-----------------------------------------------------------------------------------------------------------'
 *                                                                .- 2u ------------.
 *                                                                |   X             |
 *                                                                '-----------------'
 *                                  .--------------------- 6.25u ----------------------------.
 *                                  |                        X                               |
 *                                  '--------------------------------------------------------'
 *                       .----------------------- 6.25u ---------------------------- 1.25u ---- 1.25u ---- 1.25u ------ 1.25u +-- 1.25u --.
 *                       |                          X                             |     X    |   X      | X        |        X |      X    |
 *                       '----------------------------------------------------------------------------------------------------------------'
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 /* RUPHIN
  * .--------------------------------------------------------------------------------------------------------------------------------------.
  * | ESC  ~ | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      | -      | =      | DEL    | BACKSP |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
  * | TAB    | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | [      | ]      | NUMPAD | HOME   |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ------------+--------|
  * | FN     | A      | S      | D      | F      | G      | H      | J      | K      | L      | ;      | '      | XXXXXX . ENTER  | END    |
  * |- 2u ---+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
  * | XXXXXX . LSHIFT | Z      | X      | C      | V      | B      | N      | M      | ,      | .      | /      | RSHIFT | RSHIFT | UP     |
  * |--------+--------+--------+--------+--------+- 3u ------------+--------+--------+--------+--------+-----------------+--------+--------|
  * | LCTRL  | LGUI   | LALT   | \      | /      | XXXXXX . SPACE  . XXXXXX | [      | ]      | INSERT | RCTRL  | LEFT   | RIGHT  | DOWN   |
  * '--------------------------------------------------------------------------------------------------------------------------------------'
  */

  [_RP] = { /* RUPHIN */
    { F(0),    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_DEL,  KC_BSPC },
    { KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, TG(_NP), KC_HOME },
    { MO(_FN), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_ENT,  KC_END  },
    { KC_LSFT, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RSFT, KC_UP   },
    { KC_LCTL, KC_LGUI, KC_LALT, KC_BSLS, KC_SLSH, KC_SPC,  KC_SPC,  KC_SPC,  KC_LBRC, KC_RBRC, KC_INS,  KC_RCTL, KC_LEFT, KC_RGHT, KC_DOWN },
  },


 /* FUNCTION
  * .--------------------------------------------------------------------------------------------------------------------------------------.
  * | `      | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    |        |        |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
  * |        |        |        |        |        |        |        |        | HOME   | UP     | END    |        |        |        | PGUP   |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ------------+--------|
  * |        |        |        |        |        |        |        |        | LEFT   | DOWN   | RIGHT  |        |        .        | PGDWN  |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
  * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
  * |--------+--------+--------+--------+--------+- 3u ------------+--------+--------+--------+--------+-----------------+--------+--------|
  * |        |        |        |        |        |        .        .        | (      | )      | PRSCR  |        |        |        |        |
  * '--------------------------------------------------------------------------------------------------------------------------------------'
  */

  [_FN] = { /* FUNCTION */
    { KC_GRV,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______, _______ },
    { _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_UP,   KC_END,  _______, _______, _______, KC_PGUP },
    { _______, _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, KC_PGDN },
    { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
    { _______, _______, _______, _______, _______, _______, _______, _______, F(1),    F(2)   , KC_PSCR, _______, _______, _______, _______ },
  },

 /* NUMPAD
  * .--------------------------------------------------------------------------------------------------------------------------------------.
  * |        |        |        |        |        |        |        |        | NUMLK  | /      | *      | -      |        |        |        |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
  * |        |        |        |        |        |        |        |        | 7      | 8      | 9      | +      |        |        |        |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ------------+--------|
  * |        |        |        |        |        |        |        |        | 4      | 5      | 6      | +      |        .        |        |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
  * |        |        |        |        |        |        |        |        | 1      | 2      | 3      | ENTER  |        |        |        |
  * |--------+--------+--------+--------+--------+- 3u ------------+--------+--------+--------+--------+-----------------+--------+--------|
  * |        |        |        |        |        |        .        .        | 0      | 0      | .      | ENTER  |        |        |        |
  * '--------------------------------------------------------------------------------------------------------------------------------------'
  */

  [_NP] = { /* NUMPAD */
    { _______, _______, _______, _______, _______, _______, _______, _______, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, _______, _______, _______ },
    { _______, _______, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, _______, _______, _______ },
    { _______, _______, _______, _______, _______, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, _______, _______, _______ },
    { _______, _______, _______, _______, _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PENT, _______, _______, _______ },
    { _______, _______, _______, _______, _______, _______, _______, _______, KC_P0,   KC_P0,   KC_PDOT, KC_PENT, _______, _______, _______ },
  },

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
