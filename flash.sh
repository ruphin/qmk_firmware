#!/bin/bash

# Fivefourteen v0 (Teensy 2.0)
# ./teensy_loader_cli -mmcu=atmega32u4 -v -w ./.build/handwired_fivefourteen_default.hex

# Fivefourteen v1 (Teensy LC)
./teensy_loader_cli -mmcu=mkl26z64 -v -w ./.build/chibios_test_fivefourteen_fivefourteen.hex
