#!/bin/bash

TOOLS_AVR=/Applications/Arduino-1.8.10.app/Contents/Java/hardware/tools/avr

# internal 8 MHz
$TOOLS_AVR/bin/avrdude -C $TOOLS_AVR/etc/avrdude.conf -v -v -v -v -patmega328p -cstk500v1 -P/dev/cu.Bluetooth-Incoming-Port -e -Uefuse:w:0xfd:m -Uhfuse:w:0xdb:m -Ulfuse:w:0xe2:m 

# external 16 MHz
$TOOLS_AVR/bin/avrdude -C $TOOLS_AVR/etc/avrdude.conf -v -v -v -v -patmega328p -cstk500v1 -P/dev/cu.Bluetooth-Incoming-Port -e -Uefuse:w:0xfd:m -Uhfuse:w:0xdb:m -Ulfuse:w:0xff:m 
