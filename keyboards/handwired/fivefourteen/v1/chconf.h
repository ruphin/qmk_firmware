// Copyright 2026 ruphin
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Tick-based system timer, as used by the other QMK Teensy LC keyboards.
#define CH_CFG_ST_FREQUENCY 1000
#define CH_CFG_ST_TIMEDELTA 0
#define CH_CFG_TIME_QUANTUM 20

#include_next <chconf.h>
