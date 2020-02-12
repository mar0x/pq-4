
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
#include <Wire.h>

using re_a = artl::digital_in<artl::pin::id::pb1>;
using re_b = artl::digital_in<artl::pin::id::pb0>;

using re_a_change = artl::pin_change_int<re_a::pin>;
using re_b_change = artl::pin_change_int<re_b::pin>;

using a0 = artl::digital_in<artl::pin::id::pd3>;
using a1 = artl::digital_in<artl::pin::id::pd4>;
using a2 = artl::digital_in<artl::pin::id::pb6>;

using chg = artl::digital_pin<artl::pin::id::pb7>;

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

enum {
    SPI_POT_MIN = 0,
    SPI_POT_MAX = 256,

    POT_MIN = 0,
    POT_MAX = SPI_POT_MAX * 2,
    POT_CENTER = SPI_POT_MAX,
};

enum {
    ENC_MIN = 0,
    ENC_MAX = 86,
    ENC_CENTER = ENC_MAX / 2,

    POT2ENC = (POT_MAX * 10 / ENC_MAX + 5) / 10,
    POT2ENC_2 = POT2ENC / 2 + 1,
};

struct enc_handler {
    void on_rotate(short dir, unsigned long t);

    void set_pos(int16_t pot) {
        pos_ = pot2enc(pot);
        err_ = pot - enc2pot(pos_);
    }

    int16_t get_pos() const {
        return enc2pot(pos_) + err_;
    }

    void ready() { ready_ = true; }

private:
    int8_t pos_ = ENC_CENTER;
    int8_t err_ = 0;
    bool ready_ = false;

    static int8_t pot2enc(int16_t pot) {
        return (pot + POT2ENC_2) / POT2ENC;
    }

    static int16_t enc2pot(int8_t enc) {
        int16_t pot = enc * POT2ENC - POT2ENC_2 / 2;

        if (pot < POT_MIN) pot = POT_MIN;
        if (pot > POT_MAX) pot = POT_MAX;

        return pot;
    }
};

struct enc_time_traits {
    unsigned long bounce() const { return 2; }
    unsigned long hold() const { return 500; }
};

using enc = artl::encoder<enc_handler, enc_time_traits, 1>;

enc my_enc;

enum {
    MODE_GAIN = 0,
    MODE_FREQ = 1,
    MODE_LEVEL = 2,
};

enum {
    RED_DOT_OFF = 0,
    RED_DOT_ON = 1,
    RED_DOT_AUTO = 255,
};

enum {
    DIM_OFF = 1,
    DIM_ON = 2,
    DIM_AUTO = 255,
};

uint8_t mode = MODE_GAIN;
uint8_t red_dot_mode = RED_DOT_AUTO;
uint8_t dim_mode = DIM_AUTO;

struct led_array {
    enum {
        MAX_LED_GROUP         = 4,
        LED_GROUP_FRAME_MASK  = 0x03,
        MAX_LED_IN_GROUP      = 4,

        LED_MAX   = 14,
        POS2LED   = POT_MAX / LED_MAX,
        POS2LED_2 = POS2LED / 2,
    };

    using led1 = artl::digital_pin<artl::pin::id::pc3>;
    using led2 = artl::digital_pin<artl::pin::id::pc2>;
    using led3 = artl::digital_pin<artl::pin::id::pc1>;
    using led4 = artl::digital_pin<artl::pin::id::pc0>;
    using led5 = artl::digital_out<artl::pin::id::pb2>;
    using led6 = artl::digital_out<artl::pin::id::pd7>;
    using led7 = artl::digital_out<artl::pin::id::pd6>;
    using led8 = artl::digital_out<artl::pin::id::pd5>;

    void setup() {
        led1().input();
        led2().input();
        led3().input();
        led4().input();
        led5().setup();
        led6().setup();
        led7().setup();
        led8().setup();
    }

    void update(unsigned long t) {
        if (t - last_update < 1) {
            return;
        }

        last_update = t;

        uint8_t led_group = (frame % MAX_LED_GROUP);

        led_group_off(led_group);

        frame++;

        led_group = (frame % MAX_LED_GROUP);

        if ( ((frame / 4) % brightness_a) > brightness_b ) {
            return;
        }

        uint8_t group_mask = (mask >> (led_group * MAX_LED_IN_GROUP));

        led8().write(group_mask & 1);
        led7().write(group_mask & 2);
        led6().write(group_mask & 4);
        led5().write(group_mask & 8);

        led_group_on(led_group);
    }

    static void led_group_off(uint8_t led_group) {
        switch(led_group) {
        case 0: led1().input(); break;
        case 1: led2().input(); break;
        case 2: led3().input(); break;
        case 3: led4().input(); break;
        }
    }

    static void led_group_on(uint8_t led_group) {
        switch(led_group) {
        case 0: led1().output(); led1().low(); break;
        case 1: led2().output(); led2().low(); break;
        case 2: led3().output(); led3().low(); break;
        case 3: led4().output(); led4().low(); break;
        }
    }

    void set_pos(uint16_t pos) {
        uint8_t b = (pos + POS2LED_2) / POS2LED;

        switch (mode) {
        case MODE_GAIN:
        case MODE_LEVEL:
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
            break;

        case MODE_FREQ:
            mask = 1 << b;
            break;
/*
        case MODE_LEVEL:
            mask = 0;

            for (uint8_t i = 0; i <= b; i++) {
                mask |= 1 << i;
            }
            break;
*/
        }

        if (red_dot_state) {
            mask |= 0x8000;
        }
    }

    void red_dot(bool h) {
        red_dot_state = h;

        if (h) {
            mask |= 0x8000;
        } else {
            mask &= ~0x8000;
        }
    }

    void dim(uint8_t d) {
        if (d == 0) d = 1;

        brightness_a = d;
    }

    unsigned long last_update = 0;
    uint16_t mask = 0;
    uint8_t brightness_a = 2;
    uint8_t brightness_b = 0;
    uint8_t frame = 0;
    bool red_dot_state = false;
};

led_array led_ring;

struct spi_pot {
    using cs = artl::digital_pin<artl::pin::id::pd1>;
    using shdn = artl::digital_pin<artl::pin::id::pd0>;

    void setup() {
        cs().output();
        cs().high();

        shdn().output();
        shdn().low();

        SPI.begin();

        SPI.setBitOrder(MSBFIRST);
        SPI.setDataMode(SPI_MODE0);
        // SPI.setClockDivider(SPI_CLOCK_DIV128);
    }

    void enable() {
        shdn().high();
    }

    void spi_transfer(uint8_t cmd, uint16_t pos) {
        uint8_t hi = (pos >> 8) & 0x01;
        uint8_t lo = pos & 0xFF;

        SPI.transfer(cmd | hi);
        SPI.transfer(lo);
    }

    static inline uint16_t pos2spi(uint16_t pos) {
        return SPI_POT_MAX - pos;
    }

    void set_pos(uint16_t pos) {
        cs().low();

        if (mode == MODE_GAIN) {
            if (pos < POT_CENTER) {
                spi_transfer(0x00, pos2spi(pos));
                spi_transfer(0x10, pos2spi(SPI_POT_MIN));
            } else {
                spi_transfer(0x00, pos2spi(SPI_POT_MAX));
                spi_transfer(0x10, pos2spi(pos - POT_CENTER));
            }
        } else {
            pos = pos / 2;

            spi_transfer(0x00, pos2spi(pos));
            spi_transfer(0x10, pos2spi(pos));
        }

        cs().high();
    }
};

struct on_disable_highlight {
    void operator() (unsigned long /* t */) {
        if (red_dot_mode == RED_DOT_AUTO) led_ring.red_dot(false);
        if (dim_mode == DIM_AUTO) led_ring.dim(2);
    }
};

artl::timer<on_disable_highlight> disable_highlight_timer;

void enc_handler::on_rotate(short dir, unsigned long t) {
    if (!ready_) return;

    pos_ += dir;
    err_ = 0;

    if (pos_ > ENC_MAX) pos_ = ENC_MAX;
    if (pos_ < ENC_MIN) pos_ = ENC_MIN;

    int16_t pot = get_pos();

    spi_pot().set_pos(pot);
    led_ring.set_pos(pot);

    if (red_dot_mode == RED_DOT_AUTO) led_ring.red_dot(true);
    if (dim_mode == DIM_AUTO) led_ring.dim(1);

    disable_highlight_timer.schedule(t + 2000);

    chg().output();
    chg().high();
}

enum {
    I2C_DIGIPOT_POS = 0,
    I2C_DIGIPOT_CHG,
    I2C_DIGIPOT_RED_DOT,
    I2C_DIGIPOT_DIM,
};

uint8_t i2c_reg = I2C_DIGIPOT_POS;

void on_i2c_request() {
    if (i2c_reg == I2C_DIGIPOT_POS) {
        int16_t pos = my_enc.get_pos();

        uint8_t hi = (pos >> 8) & 0xFF;
        uint8_t lo = pos & 0xFF;

        Wire.write(hi);
        Wire.write(lo);

        chg().input();
    }

    if (i2c_reg == I2C_DIGIPOT_RED_DOT) {
        Wire.write(red_dot_mode);
    }

    if (i2c_reg == I2C_DIGIPOT_DIM) {
        Wire.write(dim_mode);
    }
}

void on_i2c_receive(int n) {
    i2c_reg = Wire.read();

    if (i2c_reg == I2C_DIGIPOT_POS && n == 3) {
        uint16_t hi = Wire.read();
        uint16_t lo = Wire.read();
        int16_t pos = (hi << 8) | lo;

        if (pos < POT_MIN) pos = POT_MIN;
        if (pos > POT_MAX) pos = POT_MAX;

        my_enc.set_pos(pos);
        spi_pot().set_pos(pos);
        led_ring.set_pos(pos);

        chg().input();
    }

    if (i2c_reg == I2C_DIGIPOT_CHG && n == 2) {
        uint8_t v = Wire.read();

        if (v != 0) {
            chg().output();
            chg().high();
        } else {
            chg().input();
        }
    }

    if (i2c_reg == I2C_DIGIPOT_RED_DOT && n == 2) {
        red_dot_mode = Wire.read();

        led_ring.red_dot(red_dot_mode == RED_DOT_ON);
    }

    if (i2c_reg == I2C_DIGIPOT_DIM && n == 2) {
        dim_mode = Wire.read();

        led_ring.dim(dim_mode == DIM_AUTO ? (uint8_t) DIM_OFF : dim_mode);
    }

}

uint8_t get_id() {
    return (a0().read() ? 1 : 0) +
        (a1().read() ? 2 : 0) +
        (a2().read() ? 4 : 0);
}

void setup() {
    led_ring.setup();

    re_a().setup();
    re_b().setup();

    re_a_change().enable();
    re_b_change().enable();

    chg().input();

    a0().setup();
    a1().setup();
    a2().setup();

    uint8_t id = get_id();

    Wire.begin(id);
    Wire.onRequest(on_i2c_request);
    Wire.onReceive(on_i2c_receive);

    switch (id) {
    case 0:
    case 2:
        mode = MODE_FREQ;
        break;

    case 6:
        mode = MODE_LEVEL;
        break;

    default:
        mode = MODE_GAIN;
        break;
    }

    // 8 000 000 / presc / ocra = 200 updates per second
    // presc = 64
    // ocra = 8000000 / 200 / presc = 62.5
    led_update_tc().setup(0, 0, 4, led_update_tc::cs::presc_64);
    led_update_tc().ocra() = 62;
    led_update_tc().cnt() = 0;
    led_update_tc().oca().enable();

    int16_t pos = my_enc.get_pos();

    spi_pot().setup();

    spi_pot().set_pos(pos);
    spi_pot().enable();

    led_ring.set_pos(pos);

    unsigned long start = millis();
    unsigned long t = start;

    my_enc.update(re_a().read(), re_b().read(), t);

    do {
        delay(1);
        t = millis();
        my_enc.update(re_a().read(), re_b().read(), t);
    } while (t - start < enc_time_traits().bounce());

    my_enc.ready();


    if (red_dot_mode == RED_DOT_AUTO) led_ring.red_dot(true);
    if (dim_mode == DIM_AUTO) led_ring.dim(1);

    disable_highlight_timer.schedule(t + 2000);

    chg().output();
    chg().high();
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
