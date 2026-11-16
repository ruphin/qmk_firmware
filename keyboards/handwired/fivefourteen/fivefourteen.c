// Copyright 2026 ruphin
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "usb_main.h"

/*
 * USB enumeration watchdog.
 *
 * Occasionally the keyboard is not recognised when the computer boots, and
 * only a physical replug fixes it. QMK connects to the host once at startup
 * and never retries, so if that enumeration goes wrong nothing recovers it.
 *
 * During the first USB_WATCHDOG_WINDOW_MS after power-up, if the host has not
 * configured the keyboard for USB_WATCHDOG_TIMEOUT_MS in a row, reset the
 * microcontroller. The firmware then starts from scratch, including QMK's USB
 * startup that detaches from the bus and reconnects: the same as replugging
 * the cable. A reset is used rather than restarting just the USB driver
 * because QMK disables USB driver restarts on Kinetis (Teensy) boards, where
 * they can leave the keyboard dead until replugged.
 *
 * The reset count is kept in RAM that the startup code does not clear, so it
 * survives the resets, and is capped so a host that legitimately leaves the
 * device unconfigured (e.g. a powered port on a computer that is off) does
 * not cause endless resets. On a real power-up that RAM holds random data,
 * which the check value rejects, so the count starts at zero.
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

#define USB_WATCHDOG_MAGIC 0x5145F00Du

// .ram0.* is the ChibiOS "noinit" area: not zeroed or initialised on reset.
typedef struct {
    uint32_t magic;
    uint32_t resets;
    uint32_t check;
} usb_watchdog_persist_t;

static volatile usb_watchdog_persist_t usb_watchdog_persist __attribute__((section(".ram0.usb_watchdog")));

static uint8_t usb_watchdog_resets;

static bool usb_watchdog_ok(void) {
    return USB_DRIVER.state == USB_ACTIVE || USB_DRIVER.state == USB_SUSPENDED;
}

void keyboard_pre_init_kb(void) {
    if (usb_watchdog_persist.magic == USB_WATCHDOG_MAGIC && usb_watchdog_persist.check == ~usb_watchdog_persist.resets && usb_watchdog_persist.resets <= USB_WATCHDOG_MAX_RETRIES) {
        usb_watchdog_resets = usb_watchdog_persist.resets; // reset by the watchdog
    } else {
        usb_watchdog_resets = 0; // power-up
    }
    usb_watchdog_persist.magic  = USB_WATCHDOG_MAGIC;
    usb_watchdog_persist.resets = usb_watchdog_resets;
    usb_watchdog_persist.check  = ~(uint32_t)usb_watchdog_resets;

    keyboard_pre_init_user();
}

void housekeeping_task_kb(void) {
    static uint32_t last_ok_time   = 0;
    static uint32_t last_loop_time = 0;

    uint32_t now = timer_read32();

    if (now > USB_WATCHDOG_WINDOW_MS || usb_watchdog_resets >= USB_WATCHDOG_MAX_RETRIES) {
        return;
    }

    if (usb_watchdog_ok() || TIMER_DIFF_32(now, last_loop_time) > USB_WATCHDOG_LOOP_GAP_MS) {
        last_ok_time = now;
    }
    last_loop_time = now;

    if (TIMER_DIFF_32(now, last_ok_time) > USB_WATCHDOG_TIMEOUT_MS) {
        usb_watchdog_persist.resets = usb_watchdog_resets + 1;
        usb_watchdog_persist.check  = ~(uint32_t)(usb_watchdog_resets + 1);
        dprintf("USB watchdog: not configured for %dms, resetting (%d/%d)\n", USB_WATCHDOG_TIMEOUT_MS, usb_watchdog_resets + 1, USB_WATCHDOG_MAX_RETRIES);
        soft_reset_keyboard();
    }
}
