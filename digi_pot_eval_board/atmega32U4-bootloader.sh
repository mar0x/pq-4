#!/bin/bash

TOOLS_AVR=/Applications/Arduino-1.8.10.app/Contents/Java/hardware/tools/avr
$TOOLS_AVR/bin/avrdude -C $TOOLS_AVR/etc/avrdude.conf -v -patmega32u4 -cstk500v1 -P/dev/cu.Bluetooth-Incoming-Port -e -Ulock:w:0x3F:m -Uefuse:w:0xcb:m -Uhfuse:w:0xd8:m -Ulfuse:w:0xff:m 

