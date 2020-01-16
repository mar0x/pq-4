
#pragma once

#include "log_window.h"

namespace pq4 {

struct out {
    void setup();

    void store_led(bool v);
    void bypass_led(bool v);

    void midi_write(const void* data, int s);

    void bypass_relay(bool v);
    void mid_relay(bool v);
    void hi_relay(bool v);
    void low_relay(bool v);
    void presence_relay(bool v);

    template<typename T1>
    void serial_print(const T1& a1) { pts.print(a1); }

    template<typename T1, typename ...Args>
    void serial_print(const T1& a1, Args... args) {
        pts.print(a1);
        serial_print(args...);
    }

    template<typename T1>
    void serial_println(const T1& a1) { pts.println(a1); }

    template<typename T1, typename ...Args>
    void serial_println(const T1& a1, Args... args) {
        pts.print(a1);
        serial_println(args...);
    }

private:
    serial midi_;
};


inline void
out::setup()
{
}

inline void
out::store_led(bool v) {
    mvwprintw(np_win, 0, 9, "%c", (v ? 'o' : '.'));
    wrefresh(np_win);
}

inline void
out::bypass_led(bool v) {
    mvwprintw(bp_win, 2, 4, "%c", (v ? 'o' : '.'));
    wrefresh(bp_win);
}

inline void
out::midi_write(const void* data, int s) {
    log_window::print("midi write: ");

    uint8_t *b = (uint8_t *) data;
    for (uint8_t i = 0; i < s; i++) {
        log_window::print(b[i], " ");
    }
    log_window::println("");
}

void update_relay(uint8_t i, bool v);

inline void
out::bypass_relay(bool v) {
    mvwprintw(bp_win, 1, 7, "%c", (v ? '\\' : '/'));
    wrefresh(bp_win);
}

inline void
out::mid_relay(bool v) {
    update_relay(1, v);
}

inline void
out::hi_relay(bool v) {
    update_relay(3, v);
}

inline void
out::low_relay(bool v) {
    update_relay(5, v);
}

inline void
out::presence_relay(bool v) {
    update_relay(4, v);
}

}
