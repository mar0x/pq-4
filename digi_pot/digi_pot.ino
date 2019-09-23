
#include "artl/encoder.h"
#include "artl/digital_in.h"
#include "artl/digital_pin.h"
#include "artl/digital_out.h"

#include "artl/bits/variants/standard/pin_traits.h"

#include <SPI.h>

using re_a = artl::digital_in<artl::pin::id::pb1>;
using re_b = artl::digital_in<artl::pin::id::pb0>;
using mcp_cs = artl::digital_pin<artl::pin::id::pd1>;
using led = artl::digital_out<artl::pin::id::pd2>;

using led1 = artl::digital_out<artl::pin::id::pc3>;
using led2 = artl::digital_out<artl::pin::id::pc2>;
using led3 = artl::digital_out<artl::pin::id::pc1>;
using led4 = artl::digital_out<artl::pin::id::pc0>;
using led5 = artl::digital_out<artl::pin::id::pb2>;
using led6 = artl::digital_out<artl::pin::id::pd7>;
using led7 = artl::digital_out<artl::pin::id::pd6>;
using led8 = artl::digital_out<artl::pin::id::pd5>;

using a0 = artl::digital_in<artl::pin::id::pd3>;
using a1 = artl::digital_in<artl::pin::id::pd4>;
using a2 = artl::digital_in<artl::pin::id::pb5>;

struct enc_handler {
    void on_rotate(short dir, unsigned long t);

    short pos = 127;
};

struct enc_time_traits {
    unsigned long bounce() const { return 2; }
    unsigned long hold() const { return 500; }
};

using enc = artl::encoder<enc_handler, enc_time_traits, 1>;

enc my_enc;

struct led_array {

    void update(unsigned long t) {
        if (t - last_update < 10) {
            return;
        }

        last_update = t;

        uint8_t group = (frame % 4);

        group_off(group);

        frame++;

        group = (frame % 4);

        uint8_t group_mask = (mask >> (group * 4));

        led8().write(group_mask & 1);
        led7().write(group_mask & 2);
        led6().write(group_mask & 4);
        led5().write(group_mask & 8);

        group_on(group);
    }

    static void group_off(uint8_t group) {
        switch(group) {
        case 0: led1().high(); break;
        case 1: led2().high(); break;
        case 2: led3().high(); break;
        case 3: led4().high(); break;
        }
    }

    static void group_on(uint8_t group) {
        switch(group) {
        case 0: led1().low(); break;
        case 1: led2().low(); break;
        case 2: led3().low(); break;
        case 3: led4().low(); break;
        }
    }

    unsigned long last_update = 0;
    uint16_t mask = 0;
    uint8_t brightness;
    uint8_t frame = 0;
};

led_array led_ring;

void set_pos(uint8_t pos) {
    mcp_cs().low();

    SPI.transfer(0x00);
    SPI.transfer(pos);

    mcp_cs().high();

    if (pos > 0) { pos -= 1; }

    led_ring.mask = 1 << (pos / 17);
}

bool led_state = false;

void enc_handler::on_rotate(short dir, unsigned long) {
    pos += dir + dir;

    if (pos > 255) pos = 255;
    if (pos < 0) pos = 0;

    set_pos(pos);

    led_state = !led_state;

    led().write(led_state);
}

void setup() {
    re_a().setup();
    re_b().setup();

    mcp_cs().output();
    mcp_cs().high();

    led().setup();

    SPI.begin();

    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);
/*
    SPI.setClockDivider(SPI_CLOCK_DIV128);
 */
}

void loop() {
    unsigned long t = millis();

    my_enc.update(re_a().read(), re_b().read(), t);
    led_ring.update(t);
}
