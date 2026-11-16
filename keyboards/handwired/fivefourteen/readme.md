# fivefourteen

A handwired keyboard with a 5x14 matrix. Two builds exist with different controllers:

* `v1`: Teensy LC (MKL26Z64)
* `v2`: QMK Proton C (STM32F303), speaker section removed; row 0 is wired to the A13 or A14 pad

* Keyboard Maintainer: [ruphin](https://github.com/ruphin)
* Hardware Supported: fivefourteen v1 (Teensy LC), fivefourteen v2 (Proton C)
* Hardware Availability: Handwired, one-off build

Make example for this keyboard (after setting up your build environment):

    make handwired/fivefourteen/v1:default
    make handwired/fivefourteen/v2:default

Flashing example for this keyboard:

    make handwired/fivefourteen/v1:default:flash
    make handwired/fivefourteen/v2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Hold Esc (the top-left key) while plugging in the keyboard to enter the bootloader. Alternatively, press the reset button on the Teensy or Proton C.
