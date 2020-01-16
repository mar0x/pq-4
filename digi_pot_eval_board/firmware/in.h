
#pragma once

#include "artl/button.h"
#include "artl/encoder.h"
#include "artl/digital_in.h"
#include "artl/pin_change_int.h"

#include "config.h"

namespace pq4 {

template<typename T>
struct in {
    using traits = T;

    in();

    void setup();
    void update(unsigned long t, bool slow);

    bool midi_available() const { return Serial1.available(); }
    int midi_read() const { return Serial1.read(); }

    bool serial_available() const { return Serial.available(); }
    int serial_read() const { return Serial.read(); }

    bool pot_changed() const { return pot_changed_in().read() != 0; }

    using button_type = artl::button<typename traits::button_handler>;

    const button_type& left() const { return left_; }
    const button_type& right() const { return right_; }
    const button_type& store() const { return store_; }
    const button_type& bypass() const { return bypass_; }

private:
    enum {
        enc_a_pin = artl::pin::id::pb5,
        enc_b_pin = artl::pin::id::pb6,
    };

    using enc_a_in = artl::digital_in< enc_a_pin >;
    using enc_b_in = artl::digital_in< enc_b_pin >;

    using enc_a_int = artl::pin_change_int< enc_a_pin >;
    using enc_b_int = artl::pin_change_int< enc_a_pin >;

    using encoder_type = artl::encoder<typename traits::encoder_handler>;

    using left_in = artl::digital_in< artl::pin::id::pd7 >;
    using right_in = artl::digital_in< artl::pin::id::pd5 >;
    using store_in = artl::digital_in< artl::pin::id::pd6 >;
    using bypass_in = artl::digital_in< artl::pin::id::pd4 >;

    using pot_changed_in = artl::digital_in< artl::pin::id::pb4 >;
    using pot_changed_int = artl::pin_change_int< artl::pin::id::pb4 >;

    button_type left_;
    button_type right_;
    button_type store_;
    button_type bypass_;
    encoder_type encoder_;
};

template<typename T> inline
in<T>::in() :
    left_(traits::LEFT),
    right_(traits::RIGHT),
    store_(traits::STORE),
    bypass_(traits::BYPASS)
{ }

template<typename T> inline void
in<T>::setup()
{
    enc_a_in().setup();
    enc_b_in().setup();

    left_in().setup();
    right_in().setup();
    store_in().setup();
    bypass_in().setup();

    pot_changed_in().setup();

    Serial1.begin(31250);

    enc_a_int().enable();
    enc_b_int().enable();

    pot_changed_int().enable();
}

template<typename T> inline void
in<T>::update(unsigned long t, bool slow)
{
    encoder_.update(enc_a_in().read(), enc_b_in().read(), t);

    if (!slow) return;

    store_.update(store_in().read(), t);
    left_.update(left_in().read(), t);
    right_.update(right_in().read(), t);
    bypass_.update(!bypass_in().read(), t);
}

}
