
#pragma once

#include <Wire.h>

namespace pq4 {

struct pot {

    enum {
        I2C_DIGIPOT_POS = 0,
        I2C_DIGIPOT_CHG,
        I2C_DIGIPOT_HLT,
        I2C_DIGIPOT_DIM,
    };

    static void setup() {
        Wire.begin();
    }

    pot(uint8_t id) : id_(id) { }

    void update(unsigned long) { }

    uint16_t get(bool &c) const {
        uint16_t old = val_;

        value();

        c = old != val_;

        return val_;
    }

    uint16_t value() const {
        Wire.beginTransmission(id_);
        Wire.write(I2C_DIGIPOT_POS);
        Wire.endTransmission(false);
        Wire.requestFrom((uint8_t) id_, (uint8_t) 2, (uint8_t) true);
        uint16_t hi = Wire.read();
        uint16_t lo = Wire.read();
        val_ = (hi << 8) | lo;

        return val_;
    }

    void value(uint16_t v) {
        Wire.beginTransmission(id_);
        Wire.write(I2C_DIGIPOT_POS);
        Wire.write((uint8_t) (v >> 8));
        Wire.write((uint8_t) (v & 0xFFU));
        Wire.endTransmission();

        val_ = v;
    }

    void red_dot(uint8_t v) {
        Wire.beginTransmission(id_);
        Wire.write(I2C_DIGIPOT_HLT);
        Wire.write(v);
        Wire.endTransmission();
    }

private:
    uint8_t id_;
    mutable uint16_t val_ = 256;
};

}
