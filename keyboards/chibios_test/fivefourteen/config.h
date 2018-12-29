#ifndef FIVEFOURTEEN_CONFIG_H
#define FIVEFOURTEEN_CONFIG_H


/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6061
#define DEVICE_VER      0x0002
#define MANUFACTURER    ruphin.net
#define PRODUCT         fivefourteen
#define DESCRIPTION     handwired 5x14 matrix keyboard

/*
 * Row pins top to bottom: 4,3,2,1,0
 * Column pins left to right: [5,6,7,8,9,10,11,12,14,15,16,17,18,19]
 */

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* force NKRO */
#define FORCE_NKRO

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

#endif
