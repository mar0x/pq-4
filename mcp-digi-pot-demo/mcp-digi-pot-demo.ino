
#include <SPI.h>
#include "artl/digital_out.h"

using ss = artl::digital_out<10>;

char cmd[256];
uint8_t cmd_size = 0;

void setup() {
    SPI.begin();

    ss().setup();
    ss().high();

    Serial.begin(115200);
}

void dpSet(uint16_t v) {
    v = v & 0x03FF;

    Serial.print("dpSet: ");
    Serial.println(v);

    ss().low();

    SPI.transfer(0 | (v >> 8));
    SPI.transfer(v & 0xFF);

    ss().high();
}

uint16_t aton(char *s) {
    uint16_t res = 0;

    while (*s >= '0' && *s <= '9') {
        res = (res * 10) + (*s - '0');
        s++;
    }

    return res;
}

void loop() {

    if (Serial.available()) {
        uint8_t b = Serial.read();

        if (cmd_size < sizeof(cmd)) {
            if (b == '\n' || b == '\r') {
                cmd[cmd_size] = 0;

                if (cmd_size > 0) {
                    dpSet(aton(cmd));

                    cmd_size = 0;
                }
            } else {
                cmd[cmd_size++] = b;
            }
        }
    }
}
