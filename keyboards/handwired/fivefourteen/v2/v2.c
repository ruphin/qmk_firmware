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
