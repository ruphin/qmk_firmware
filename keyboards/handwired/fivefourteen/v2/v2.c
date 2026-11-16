// Copyright 2026 ruphin
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

/*
 * Row 0 on either A13 or A14.
 *
 * Every through-hole GPIO on a Proton C with the speaker section broken off is
 * in use, so row 0 is wired to one of the SWD pads instead: A13 on one board,
 * possibly A14 on another. Both pads are driven in lockstep as row 0, so the
 * same firmware works whichever pad the wire is on. The pads always carry the
 * same level, so a solder bridge between them is harmless.
 *
 * This replaces QMK's default COL2ROW matrix_init_pins/matrix_read_cols_on_row
 * (quantum/matrix.c) and mirrors their behaviour.
 */

#define ROW0_ALT_PIN A14

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

static void select_row(uint8_t row) {
    ATOMIC_BLOCK_FORCEON {
        gpio_set_pin_output(row_pins[row]);
        gpio_write_pin_low(row_pins[row]);
        if (row == 0) {
            gpio_set_pin_output(ROW0_ALT_PIN);
            gpio_write_pin_low(ROW0_ALT_PIN);
        }
    }
}

static void unselect_row(uint8_t row) {
    ATOMIC_BLOCK_FORCEON {
        gpio_set_pin_input_high(row_pins[row]);
        if (row == 0) {
            gpio_set_pin_input_high(ROW0_ALT_PIN);
        }
    }
}

void matrix_init_pins(void) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        unselect_row(row);
    }
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        ATOMIC_BLOCK_FORCEON {
            gpio_set_pin_input_high(col_pins[col]);
        }
    }
}

void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    matrix_row_t current_row_value = 0;

    select_row(current_row);
    matrix_output_select_delay();

    matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;
    for (uint8_t col = 0; col < MATRIX_COLS; col++, row_shifter <<= 1) {
        if (gpio_read_pin(col_pins[col]) == 0) {
            current_row_value |= row_shifter;
        }
    }

    unselect_row(current_row);
    matrix_output_unselect_delay(current_row, current_row_value != 0);

    current_matrix[current_row] = current_row_value;
}
