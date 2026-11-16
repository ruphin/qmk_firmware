// Copyright 2026 ruphin
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "usb_main.h"

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

/*
 * USB enumeration watchdog.
 *
 * Occasionally the keyboard is not recognised when the computer boots, and
 * only a physical replug fixes it. QMK connects to the host once at startup
 * and never retries, so if that enumeration goes wrong nothing recovers it.
 *
 * During the first USB_WATCHDOG_WINDOW_MS after power-up, if the host has not
 * configured the keyboard for USB_WATCHDOG_TIMEOUT_MS in a row, restart the
 * USB driver. On the Proton C this drives D+ low, which the host sees as an
 * unplug, followed by a reconnect: the same thing as replugging the cable.
 * The number of restarts is capped so a host that legitimately leaves the
 * device unconfigured (e.g. a powered port on a computer that is off) does
 * not cause endless reconnects.
 */

#ifndef USB_WATCHDOG_WINDOW_MS
#    define USB_WATCHDOG_WINDOW_MS 90000
#endif
#ifndef USB_WATCHDOG_TIMEOUT_MS
#    define USB_WATCHDOG_TIMEOUT_MS 5000
#endif
#ifndef USB_WATCHDOG_MAX_RETRIES
#    define USB_WATCHDOG_MAX_RETRIES 5
#endif

// If the main loop did not run for this long, it was blocked (the keyboard
// stays inside protocol_pre_task while suspended); restart the timeout then.
#define USB_WATCHDOG_LOOP_GAP_MS 500

void housekeeping_task_kb(void) {
    static uint32_t last_ok_time   = 0;
    static uint32_t last_loop_time = 0;
    static uint8_t  retries        = 0;

    uint32_t now = timer_read32();

    if (now > USB_WATCHDOG_WINDOW_MS || retries >= USB_WATCHDOG_MAX_RETRIES) {
        return;
    }

    usbstate_t state = USB_DRIVER.state;
    if (state == USB_ACTIVE || state == USB_SUSPENDED || TIMER_DIFF_32(now, last_loop_time) > USB_WATCHDOG_LOOP_GAP_MS) {
        last_ok_time = now;
    }
    last_loop_time = now;

    if (TIMER_DIFF_32(now, last_ok_time) > USB_WATCHDOG_TIMEOUT_MS) {
        retries++;
        dprintf("USB watchdog: not configured for %dms (state %d), restarting USB (%d/%d)\n", USB_WATCHDOG_TIMEOUT_MS, state, retries, USB_WATCHDOG_MAX_RETRIES);
        restart_usb_driver(&USB_DRIVER);
        last_ok_time = timer_read32();
    }
}
