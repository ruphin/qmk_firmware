// Copyright 2026 ruphin
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

// The original (2019) Teensy LC firmware waited 30us after selecting a row
// before reading the columns ("without this wait read unstable value"). Keep
// that proven timing instead of QMK's default of a few CPU cycles; it costs
// 150us per full scan.
void matrix_output_select_delay(void) {
    wait_us(30);
}
