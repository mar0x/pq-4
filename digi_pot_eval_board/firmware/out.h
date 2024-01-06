
#pragma once

#include "artl/digital_out.h"
#include "artl/digital_pin.h"

#include "config.h"
#include "debug.h"

namespace pq4 {

struct out {
    void setup();

    void store_led(bool v) {
        analogWrite(store_led_out(), v ? 16 : 0);
        // store_led_out().write(v);
    }
    void bypass_led(bool v) {
        if (v) {
            bypass_led_out().output();
            analogWrite(bypass_led_out(), v ? 224 : 0);
            //bypass_led_out().low();
        } else {
            bypass_led_out().input();
        }
    }

    void midi_write(const void* buf, int s) { Serial1.write((const char*) buf, s); }

    void bypass_relay(bool v) { /* bypass_relay_out().write(v); */ }
    void mid_relay(bool v) { /* mid_relay_out().write(v); */ }
    void hi_relay(bool v) { /* hi_relay_out().write(v); */ }
    void low_relay(bool v) { /* low_relay_out().write(v); */ }
    void presence_relay(bool v) { /* presence_relay_out().write(v); */ }

#if 0
#if defined(DEBUG)
    template<typename T1>
    static void debug_println(const T1& a1) { Serial.println(a1); }

    template<typename T1, typename ...Args>
    static void debug_println(const T1& a1, Args... args) {
        Serial.print(a1);
        debug_println(args...);
    }
#else
    template<typename ...Args>
    static void debug_println(Args... args) { }
#endif
#endif

    template<typename T1>
    void serial_print(const T1& a1) { Serial.print(a1); }

    template<typename T1, typename ...Args>
    void serial_print(const T1& a1, Args... args) {
        Serial.print(a1);
        serial_print(args...);
    }

    template<typename T1>
    void serial_println(const T1& a1) { Serial.println(a1); }

    template<typename T1, typename ...Args>
    void serial_println(const T1& a1, Args... args) {
        Serial.print(a1);
        serial_println(args...);
    }

private:

    using store_led_out = artl::digital_out< artl::pin::id::pc7 >;
    using bypass_led_out = artl::digital_pin< artl::pin::id::pc6 >;

    using bypass_relay_out = artl::digital_out< artl::pin::id::pf1 >;
    using mid_relay_out = artl::digital_out< artl::pin::id::pf7 >;
    using hi_relay_out = artl::digital_out< artl::pin::id::pf6 >;
    using low_relay_out = artl::digital_out< artl::pin::id::pf4 >;
    using presence_relay_out = artl::digital_out< artl::pin::id::pf5 >;
};


inline void
out::setup()
{
#if defined(DEBUG)
    Serial.begin(115200);
#endif

    store_led_out().setup();
    bypass_led_out().input();

    bypass_relay_out().setup();
    mid_relay_out().setup();
    hi_relay_out().setup();
    low_relay_out().setup();
    presence_relay_out().setup();
}

}
