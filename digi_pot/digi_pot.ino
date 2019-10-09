
#include "artl/encoder.h"
#include "artl/digital_in.h"
#include "artl/digital_pin.h"
#include "artl/digital_out.h"
#include "artl/yield.h"
#include "artl/tc.h"
#include "artl/pin_change_int.h"
#include "artl/timer.h"

#include "artl/bits/variants/standard/pin_traits.h"
#include "artl/bits/variants/standard/pin_change_traits.h"

#include <SPI.h>

using re_a = artl::digital_in<artl::pin::id::pb1>;
using re_b = artl::digital_in<artl::pin::id::pb0>;

using re_a_change = artl::pin_change_int<re_a::pin>;
using re_b_change = artl::pin_change_int<re_b::pin>;

using mcp_cs = artl::digital_pin<artl::pin::id::pd1>;
using led = artl::digital_out<artl::pin::id::pd2>;

using led1 = artl::digital_pin<artl::pin::id::pc3>;
using led2 = artl::digital_pin<artl::pin::id::pc2>;
using led3 = artl::digital_pin<artl::pin::id::pc1>;
using led4 = artl::digital_pin<artl::pin::id::pc0>;
using led5 = artl::digital_out<artl::pin::id::pb2>;
using led6 = artl::digital_out<artl::pin::id::pd7>;
using led7 = artl::digital_out<artl::pin::id::pd6>;
using led8 = artl::digital_out<artl::pin::id::pd5>;

using a0 = artl::digital_in<artl::pin::id::pd3>;
using a1 = artl::digital_in<artl::pin::id::pd4>;
using a2 = artl::digital_in<artl::pin::id::pb5>;

using led_update_tc = artl::tc<1>;

#if defined(ISR) && defined(PCINT0_vect)
ISR(PCINT0_vect) {
}
#endif

bool led_update = false;

#if defined(ISR) && defined(TIMER1_COMPA_vect)
ISR(TIMER1_COMPA_vect)
{
    led_update = true;
}
#endif

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
        if (t - last_update < 1) {
            return;
        }

        last_update = t;

        uint8_t group = (frame % 4);

        group_off(group);

        frame++;

        group = (frame % 4);

        if ( ((frame / 4) % brightness_a) > brightness_b ) {
            return;
        }

        uint8_t group_mask = (mask >> (group * 4));

        led8().write(group_mask & 1);
        led7().write(group_mask & 2);
        led6().write(group_mask & 4);
        led5().write(group_mask & 8);

        group_on(group);
    }

    static void group_off(uint8_t group) {
        switch(group) {
        case 0: led1().input(); break;
        case 1: led2().input(); break;
        case 2: led3().input(); break;
        case 3: led4().input(); break;
        }
    }

    static void group_on(uint8_t group) {
        switch(group) {
        case 0: led1().output(); led1().low(); break;
        case 1: led2().output(); led2().low(); break;
        case 2: led3().output(); led3().low(); break;
        case 3: led4().output(); led4().low(); break;
        }
    }

    void set_pos(uint8_t pos) {
        if (pos > 0) { pos -= 1; }

        uint8_t b = pos / 17;

        mask = 0;

        if (b > 7) {
            for (uint8_t i = 7; i <= b; i++) {
                mask |= 1 << i;
            }
        } else {
            for (uint8_t i = b; i <= 7; i++) {
                mask |= 1 << i;
            }
        }

        // mask = 1 << (pos / 17);

        if (high) {
            mask |= 0x8000;
        }
    }

    void highlight(bool h) {
        high = h;

        brightness_a = h ? 1 : 2;

        if (h) {
            mask |= 0x8000;
        } else {
            mask &= ~0x8000;
        }
    }

    unsigned long last_update = 0;
    uint16_t mask = 0;
    uint8_t brightness_a = 2;
    uint8_t brightness_b = 0;
    uint8_t frame = 0;
    bool high = false;
};

led_array led_ring;

void set_pos(uint8_t pos) {
    mcp_cs().low();

    SPI.transfer(0x00);
    SPI.transfer(pos);

    mcp_cs().high();

    led_ring.set_pos(pos);
}

bool led_state = false;

struct on_disable_highlight {
    void operator() (unsigned long t) {
        led_ring.highlight(false);
    }
};

artl::timer<on_disable_highlight> disable_highlight_timer;

void enc_handler::on_rotate(short dir, unsigned long t) {
    pos += dir + dir + dir;

    if (pos > 255) pos = 255;
    if (pos < 0) pos = 0;

    set_pos(pos);

    led_state = !led_state;

    led().write(led_state);

    led_ring.highlight(true);

    disable_highlight_timer.schedule(t + 2000);
}

void setup() {
    re_a().setup();
    re_b().setup();

    re_a_change().enable();
    re_b_change().enable();

    mcp_cs().output();
    mcp_cs().high();

    led().setup();

    led1().input();
    led2().input();
    led3().input();
    led4().input();
    led5().setup();
    led6().setup();
    led7().setup();
    led8().setup();

    // 8 000 000 / presc / ocra = 200 updates per second
    // presc = 64
    // ocra = 8000000 / 200 / presc = 62.5

    led_update_tc().setup(0, 0, 4, led_update_tc::cs::presc_64);
    led_update_tc().ocra() = 62;
    led_update_tc().cnt() = 0;
    led_update_tc().oca().enable();

    SPI.begin();

    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);
/*
    SPI.setClockDivider(SPI_CLOCK_DIV128);
 */

    set_pos(my_enc.pos);
}

void loop() {
    unsigned long t = millis();

    my_enc.update(re_a().read(), re_b().read(), t);

    disable_highlight_timer.update(t);

    if (led_update) {
        led_update = false;

        led_ring.update(t);
    }

    artl::yield();
}
