
#pragma once

#define PQ4_VERSION "2020.01.16"

#include "config.h"
#include "debug.h"

#if defined(ARDUINO)

#include <Arduino.h>
#include <EEPROM.h>

#include "SPI_1602.h"
#include "pot.h"
#include "in.h"
#include "out.h"

#else

#include "mock/serial_pts.h"
#include "mock/time.h"
#include "mock/eeprom.h"
#include "mock/liquid_crystal.h"
#include "mock/pot.h"
#include "mock/in.h"
#include "mock/out.h"

#endif

#include "artl/button.h"
#include "artl/encoder.h"
#include "artl/timer.h"
#include "artl/tc.h"

#include "midi_cmd.h"
#include "serial_cmd.h"
#include "settings.h"
#include "program.h"

#if defined(ARDUINO_ARCH_AVR)
#include "artl/yield.h"
#endif

#include "lcd.h"
#include "midi_mon.h"

#if defined(WITH_SNAKE)
#include "snake/game.h"
#endif

#if defined(WITH_HERO)
#include "hero/game.h"
#endif

namespace pq4 {

struct controller {

    enum {
        MIN_CURSOR_POS = 4,
        MAX_CURSOR_POS = 15,
    };

    controller();

    void setup();
    void loop();

    bool read_eeprom();
    void reset_eeprom();

    void process_midi_cmd();
    void process_serial_cmd();
    void midi_out(const midi_cmd& cmd);

    void set_program(uint8_t prog);
    void set_pot(uint8_t i, uint16_t v);
    void send_pot(uint8_t i, uint16_t v);

    void update_pot_relay(uint8_t i, uint16_t v);
    void bypass(unsigned long t, bool v);
    void on_pot_changed(unsigned long);

    void on_down(uint8_t, bool, unsigned long);
    void on_hold(uint8_t, unsigned long);
    void on_rotate(short, unsigned long);

    void commit(unsigned long);

    void start_edit(unsigned int value, unsigned int min, unsigned int max, unsigned int step = 1);
    void print_edit_value();
    void set_edit_pot(uint8_t edit_pot);
    void set_mode(uint8_t m, unsigned long t);

    void show_cursor(unsigned long t);
    void hide_cursor();

    void show_title_hint();
    void show_bypass_hint(unsigned long);
    void hide_hint();

    void set_dirty(bool dirty);

    void show_master(bool master);

    struct button_handler : public artl::default_button_handler {
        button_handler(uint8_t id) : id_(id) { }

        void on_down(bool, unsigned long);
        void on_hold(unsigned long);

        uint8_t id_;
    };

    struct encoder_handler : public artl::default_encoder_handler {
        void on_rotate(short, unsigned long);
    };

    struct in_traits {
        using button_handler = controller::button_handler;
        using encoder_handler = controller::encoder_handler;

        enum {
            STORE = 8,
            LEFT,
            RIGHT,
            BYPASS
        };
    };

    enum {
        STORE = in_traits::STORE,
        LEFT = in_traits::LEFT,
        RIGHT = in_traits::RIGHT,
        BYPASS = in_traits::BYPASS
    };

    struct hide_cursor_timer_callback {
        void operator ()(unsigned long);
    };

    using hide_cursor_timer = artl::timer<hide_cursor_timer_callback>;


    struct store_blink_timer_callback {
        void operator ()(unsigned long);

        void start(unsigned long t, uint8_t count = 3, unsigned long period = 100);
        void stop();

        uint8_t rest_;
        bool led_on_;
        unsigned long period_;
    };

    using store_blink_timer = artl::timer<store_blink_timer_callback>;


    enum {
        MODE_INITIAL,
        MODE_NORMAL,
        MODE_SETTINGS_FIRST,
        MODE_SETTINGS_CHANNEL = MODE_SETTINGS_FIRST,
        MODE_SETTINGS_CTRL_IN,
        MODE_SETTINGS_CTRL_OUT,
        MODE_SETTINGS_PROG_OUT,
        MODE_SETTINGS_MIDI_FWD,
        MODE_SETTINGS_HIDE_CURSOR,
#if defined(DEBUG)
        MODE_SETTINGS_USB_DEBUG,
#endif
        MODE_SETTINGS_FACTORY_RESET,
        MODE_SETTINGS_LAST = MODE_SETTINGS_FACTORY_RESET,
        MODE_MIDI_IN_MONITOR,
        MODE_MIDI_OUT_MONITOR,
        MODE_ABOUT,
        MODE_UPTIME,
        MODE_LOOP_COUNT,
        MODE_INPUT_COUNT,
        MODE_PC_COUNT,
#if defined(WITH_SNAKE)
        MODE_GAME_SNAKE,
#endif
#if defined(WITH_HERO)
        MODE_GAME_HERO,
#endif
        MODE_MAX,
    };

    in<in_traits> in_;
    out out_;
    pot pot_[7] = {0, 1, 2, 3, 4, 5, 6};
    uint8_t last_changed_pot_ = 0;
    bool bypass_ = false;

    store_blink_timer store_blink_timer_;

    uint8_t mode_ = MODE_INITIAL;
    settings settings_;

    uint8_t edit_pot_ = 1;
    unsigned int edit_value_;
    unsigned int edit_value_master_;
    unsigned int edit_value_min_;
    unsigned int edit_value_max_;
    unsigned int edit_value_step_;

    midi_cmd midi_cmd_;
    midi_cmd last_out_cmd_;

    serial_cmd serial_cmd_;

    bool dirty_ = false;
    bool bad_magic_;

    uint8_t prog_id_ = 0;

    program program_;
    program program_master_;

    uint8_t cursor_pos_ = MIN_CURSOR_POS;
    hide_cursor_timer hide_cursor_timer_;

    unsigned long uptime_;
    unsigned long loop_count_ = 0;
    unsigned long pc_count_ = 0;
    unsigned long input_count_ = 0;
    unsigned long last_out_ms_ = 0;

    midi_mon midi_mon_[2];

#if defined(WITH_SNAKE)
    snake::Game snake_;
#endif
#if defined(WITH_HERO)
    hero::Game hero_;
#endif


    volatile bool enable_input_;
    using input_tc = artl::tc<1>;

    bool show_master_;
};

controller controller_;

#if defined(ISR) && defined(PCINT0_vect)
ISR(PCINT0_vect) {
    ++controller_.pc_count_;
}
#endif

#if defined(ISR) && defined(TIMER1_COMPA_vect)
ISR(TIMER1_COMPA_vect)
{
    controller_.enable_input_ = true;
}
#endif

inline void
print_number(char *buf, uint8_t size, unsigned long n)
{
    char *p = buf + size;

    do {
        char c = n % 10;
        n /= 10;

        *--p = c + '0';
    } while (n);

    while (p > buf) { *--p = ' '; }
}

template<typename T> T rotate(T v, unsigned int max, int dir) {
    T res = (v + max + dir) % max;
    debug(2, "rotate: ", v, ", ", max, ", ", dir, " = ", res);
    return res;
}

template<typename T> T rotate(T v, unsigned int min, unsigned int max, int dir) {
    unsigned int range = max - min;
    T res = min + (v - min + range + dir) % range;
    debug(2, "rotate: ", v, ", ", min, ", ", max, ", ", dir, " = ", res);
    return res;
}

inline void
yield()
{
#if defined(ARDUINO_ARCH_AVR)
    artl::yield();
#endif
}

inline
controller::controller()
{
}

inline void
controller::setup() {
    in_.setup();
    out_.setup();
    pot::setup();

    unsigned long t = millis();

    midi_mon_[0].setup(t);
    midi_mon_[1].setup(t);

    lcd_setup();

    if (read_eeprom()) {
        set_mode(MODE_NORMAL, t);
        set_program(0);
    } else {
        set_mode(MODE_SETTINGS_FACTORY_RESET, t);
    }

    enable_input_ = true;

    bypass(0, true);

#if defined(ARDUINO_ARCH_AVR)
    input_tc().setup(0, 0, 4, input_tc::cs::presc_256);
    input_tc().ocra() = 200;
    input_tc().cnt() = 0;
    input_tc().oca().enable();
#endif

    yield();
}

inline void
controller::loop() {
    unsigned long t = millis();

    ++loop_count_;

    while (!midi_cmd_ && in_.midi_available()) {
        uint8_t b = in_.midi_read();

        if (midi_mon_[0].active()) {
            midi_mon_[0].read(b);
        }

        midi_cmd_.read(b);
    }

    if (midi_cmd_) {
        process_midi_cmd();
    }

    while (!serial_cmd_ && in_.serial_available()) {
        uint8_t b = in_.serial_read();

        serial_cmd_.read(b);
    }

    if (serial_cmd_) {
        process_serial_cmd();
    }

    in_.update(t, enable_input_);

#if defined(ISR) && defined(TIMER1_COMPA_vect)
    if (!enable_input_) {
        yield();
        return;
    }

    enable_input_ = false;
#endif

    ++input_count_;

    if (in_.pot_changed()) {
        on_pot_changed(t);
    }

    hide_cursor_timer_.update(t);
    store_blink_timer_.update(t);

    switch (mode_) {
    case MODE_MIDI_IN_MONITOR:
        midi_mon_[0].update(t);
        break;

    case MODE_MIDI_OUT_MONITOR:
        midi_mon_[1].update(t);
        break;

    case MODE_UPTIME: {
        unsigned long s = t / 1000;
        if (uptime_ < s) {
            uptime_ = s;
            print_number(lcd_buf[1], 12, uptime_);
            lcd_update(0, 1, 12);
        }
        break;
    }
    case MODE_LOOP_COUNT: {
        unsigned long s = loop_count_ / 1000;
        if (uptime_ < s) {
            uptime_ = s;
            print_number(lcd_buf[1], 14, uptime_);
            lcd_update(0, 1, 14);
        }
        break;
    }
    case MODE_INPUT_COUNT: {
        unsigned long s = input_count_ / 1000;
        if (uptime_ < s) {
            uptime_ = s;
            print_number(lcd_buf[1], 14, uptime_);
            lcd_update(0, 1, 14);
        }
        break;
    }
    case MODE_PC_COUNT: {
        unsigned long s = pc_count_;
        if (uptime_ < s) {
            uptime_ = s;
            print_number(lcd_buf[1], 14, uptime_);
            lcd_update(0, 1, 14);
        }
        break;
    }
#if defined(WITH_SNAKE)
    case MODE_GAME_SNAKE:
        snake_.update(t);
        break;
#endif
#if defined(WITH_HERO)
    case MODE_GAME_HERO:
        hero_.update(t);
        break;
#endif
    }

    if (!store_blink_timer_.active()) {
        out_.store_led(dirty_);
    }

    yield();
}

static const char eemagic[4] = { 'M', 'P', 'Q', '4' };

inline bool
controller::read_eeprom() {
    char magic_test[sizeof(eemagic)];

    EEPROM.get(0, magic_test);

    if (memcmp(eemagic, magic_test, sizeof(eemagic)) != 0) {
        bad_magic_ = true;
        return false;
    }

    int s = program::setup(sizeof(eemagic));

    s = settings::setup(s);
    settings_.read();

    bad_magic_ = false;
#if defined(DEBUG)
    debug_level_ = settings_.usb_debug;
#endif
    return true;
}

inline void
controller::reset_eeprom() {
    EEPROM.put(0, eemagic);
    int s = program::setup(sizeof(eemagic));

    for (uint8_t i = 0; i < MAX_PROGRAMS; i++) {
        program().write(i);
    }

    s = settings::setup(s);

    settings_ = settings();
    settings_.write();

    EEPROM.update(s, 0);

    bad_magic_ = false;
}

inline void
controller::process_midi_cmd() {
    if (settings_.midi_fwd) {
        midi_out(midi_cmd_);
    }

    if (midi_cmd_.command() == midi_cmd::CMD_PROG_CHANGE &&
        midi_cmd_.channel() == settings_.midi_channel) {
        set_program(midi_cmd_.program());
    }

    if (midi_cmd_.command() == midi_cmd::CMD_CTRL_CHANGE &&
        midi_cmd_.channel() == settings_.midi_channel) {
        for(uint8_t i = 0; i < MAX_POT; i++) {
            if (settings_.midi_pot_ctrl_in[i] == midi_cmd_.controller()) {
                set_pot(i, midi_cmd_.value() * 4);
            }
        }
    }

    midi_cmd_.reset();
}

inline void
controller::process_serial_cmd() {
    out_.serial_println("");

    // out_.serial_println(serial_cmd_.buf_);

    if (serial_cmd_.command() == serial_cmd::CMD_VERSION) {
        out_.serial_println("V ", PQ4_VERSION);
    }
    if (serial_cmd_.command() == serial_cmd::CMD_PROG_CHANGE) {
        uint8_t p;
        if (serial_cmd_.get_arg(1, p)) { set_program(p); }

        out_.serial_println("PC ", prog_id_);
    }
    if (serial_cmd_.command() == serial_cmd::CMD_CTRL_CHANGE) {
        uint8_t c = 0, v = 0;
        if (serial_cmd_.get_arg(1, c) &&
            serial_cmd_.get_arg(2, v)) {
            for(uint8_t i = 0; i < MAX_POT; i++) {
                if (settings_.midi_pot_ctrl_in[i] == c) {
                    set_pot(i, v * 4);
                }
            }
        }

        out_.serial_println("CC ", c, " ", v);
    }
    if (serial_cmd_.command() == serial_cmd::CMD_POT) {
        uint8_t l = 0;
        uint16_t v = 0;
        if (serial_cmd_.get_arg(1, l) &&
            serial_cmd_.get_arg(2, v)) { set_pot(l, v); }

        out_.serial_println("PT ", l, " ", program_.pot[l]);
    }
    if (serial_cmd_.command() == serial_cmd::CMD_STORE) {
        if (!dirty_) { out_.serial_println("CLEAR"); }
        else if (bad_magic_) { out_.serial_println("BAD MAGIC"); }
        else { commit(millis()); }

        out_.serial_print("PR ", prog_id_, " ", program_.pot[0]);
        for (uint8_t i = 1; i < MAX_POT; i++) {
            out_.serial_print(",", program_.pot[i]);
        }
        out_.serial_println(" \"", program_.title, "\"");
    }
    if (serial_cmd_.command() == serial_cmd::CMD_RESTORE) {
        if (!dirty_) { out_.serial_println("CLEAR"); }
        else { set_program(prog_id_); }

        out_.serial_print("PR ", prog_id_, " ", program_.pot[0]);
        for (uint8_t i = 1; i < MAX_POT; i++) {
            out_.serial_print(",", program_.pot[i]);
        }
        out_.serial_println(" \"", program_.title, "\"");
    }
    if (serial_cmd_.command() == serial_cmd::CMD_PROGRAM) {
        // TODO
    }

    serial_cmd_.reset();

    out_.serial_print("> ");
}

inline void
controller::midi_out(const midi_cmd& cmd) {
    if (midi_mon_[1].active()) {
        for (uint8_t i = 0; i < cmd.size(); i++) {
            midi_mon_[1].read(cmd[i]);
        }
    }

    last_out_cmd_ = cmd;
    last_out_ms_ = millis();

    out_.midi_write(cmd, cmd.size());
}

inline void
controller::set_program(uint8_t prog) {
    debug(1, "set_program: ", prog_id_, " -> ", prog);

    prog_id_ = prog;

    program_.read(prog);
    program_master_ = program_;

    if (settings_.midi_out_prog) {
        midi_cmd cmd(settings_.midi_channel, midi_cmd::CMD_PROG_CHANGE, prog_id_);

        midi_out(cmd);
    }

    for(uint8_t i = 0; i < MAX_POT; i++) {
        pot_[i].value(program_.pot[i]);
        update_pot_relay(i, program_.pot[i]);
        send_pot(i, program_.pot[i]);
    }

    if (mode_ != MODE_SETTINGS_CTRL_IN && mode_ != MODE_SETTINGS_CTRL_OUT) {
        for(uint8_t i = 0; i < MAX_POT; i++) {
            pot_[i].red_dot(false);
        }
    }

    if (mode_ == MODE_NORMAL) {
        set_dirty(false);

        print_number(lcd_buf[0], 3, prog_id_ + 1);
        lcd_buf[0][3] = ' ';
        memcpy(lcd_buf[0] + 4, program_.title, 12);

        hide_cursor();

        lcd_update(0, 0, LCD_COLUMNS);
        lcd_update(0, 1, LCD_COLUMNS);
    }
}

inline void
controller::set_pot(uint8_t i, uint16_t v) {
    debug(1, "set_pot: ", i, " ", program_.pot[i], " -> ", v);

    pot_[i].value(v);
    update_pot_relay(i, program_.pot[i]);

    // send controller change MIDI command if configured
    send_pot(i, v);

    program_.pot[i] = v;

    if (mode_ != MODE_SETTINGS_CTRL_IN && mode_ != MODE_SETTINGS_CTRL_OUT) {
        pot_[i].red_dot(program_master_.pot[i] != v);
    }

    if (mode_ == MODE_NORMAL) {
        set_dirty(program_ != program_master_);
    }
}

inline void
controller::send_pot(uint8_t i, uint16_t v) {
    if (settings_.midi_pot_ctrl_out[i] <= 127) {
        v = v / 4;
        if (v > 127) v = 127;

        midi_cmd cmd(settings_.midi_channel, midi_cmd::CMD_CTRL_CHANGE,
            settings_.midi_pot_ctrl_out[i], v);

        midi_out(cmd);
    }
}

inline void
controller::update_pot_relay(uint8_t i, uint16_t v) {
    switch (i) {
    case 1: // MID GAIN
        out_.mid_relay(v > DEFAULT_POT_VALUE);
        break;
    case 3: // HI GAIN
        out_.hi_relay(v > DEFAULT_POT_VALUE);
        break;
    case 4: // PRESENCE
        out_.presence_relay(v > DEFAULT_POT_VALUE);
        break;
    case 5: // LOW
        out_.low_relay(v > DEFAULT_POT_VALUE);
        break;
    }
}

inline void
controller::bypass(unsigned long t, bool v) {
    bypass_ = v;

    if (mode_ == MODE_NORMAL && t > 0) {
        show_bypass_hint(t);
    }

    out_.bypass_relay(bypass_);
    out_.bypass_led(!bypass_);
}

inline void
controller::on_pot_changed(unsigned long t)
{
    static const char *pot_title[] = {
        "MID FREQ ",
        "MID GAIN ",
        "HI FREQ  ",
        "HI GAIN  ",
        "PRESENCE ",
        "LOW      ",
        "LEVEL    "
    };

    uint8_t pot_id = last_changed_pot_;

    for (uint8_t i = 0; in_.pot_changed() && i < MAX_POT; i++) {
        pot_id = (i + last_changed_pot_) % MAX_POT;

        bool changed = false;
        uint16_t v = pot_[pot_id].get(changed);

        if (!changed) continue;

        program_.pot[pot_id] = v;

        update_pot_relay(pot_id, v);

        if (mode_ != MODE_SETTINGS_CTRL_IN && mode_ != MODE_SETTINGS_CTRL_OUT) {
            pot_[pot_id].red_dot(program_master_.pot[pot_id] != v);
        }

        if (mode_ == MODE_NORMAL) {
            lcd.noCursor();

            memcpy(lcd_buf[1], pot_title[pot_id], 9);
            print_number(lcd_buf[1] + 9, 3, v);
            memset(lcd_buf[1] + 12, ' ', LCD_COLUMNS - 12);
            lcd_update(0, 1, LCD_COLUMNS);

            hide_cursor_timer_.schedule(t + settings_.hide_cursor_delay_s * 1000);
        }
    }

    last_changed_pot_ = pot_id;

    if (mode_ == MODE_NORMAL) {
        set_dirty(program_ != program_master_);
    }
}

inline void
controller::on_down(uint8_t i, bool down, unsigned long t) {
    if (!down) {
        debug(5, "on_down: release ", i);

        if (i == RIGHT && show_master_) {
            show_master(false);
        }

        return; // no reaction on key UP
    }

    debug(4, "on_down: ", i);

    if (i == BYPASS) {
        bypass(t, !bypass_);

        return;
    }

    if (mode_ == MODE_NORMAL) {
        // move cursor LEFT
        if (i == LEFT && in_.right().up()) {
            cursor_pos_ = rotate(cursor_pos_, MIN_CURSOR_POS, MAX_CURSOR_POS, -1);
            show_cursor(t);

            return;
        }

        // move cursor RIGHT
        if (i == RIGHT && in_.left().up()) {
            cursor_pos_ = rotate(cursor_pos_, MIN_CURSOR_POS, MAX_CURSOR_POS, 1);
            show_cursor(t);

            return;
        }

        // cancel changes and stay in NORMAL
        // hold RIGHT then press LEFT or
        // hold LEFT then press RIGHT
        if ((i == LEFT && in_.right().hold()) || (i == RIGHT && in_.left().hold()))
        {
            if (dirty_) { set_program(prog_id_); }
            return;
        }

        return;
    }

    // cancel changes and back to NORMAL mode
    // hold RIGHT then press LEFT or
    // hold LEFT then press RIGHT
    if ((i == LEFT && in_.right().hold()) || (i == RIGHT && in_.left().hold()))
    {
        set_mode(MODE_NORMAL, t);
        return;
    }

    if (mode_ == MODE_SETTINGS_CTRL_IN || mode_ == MODE_SETTINGS_CTRL_OUT) {
        bool pot_changed = false;

        // controller -> POT mapping
        if (i == LEFT && in_.right().up()) {
            set_edit_pot(rotate(edit_pot_, 1, MAX_POT + 1, -1));
            pot_changed = true;
        }

        if (i == RIGHT && in_.left().up()) {
            set_edit_pot(rotate(edit_pot_, 1, MAX_POT + 1, 1));
            pot_changed = true;
        }

        if (i < MAX_POT && in_.left().up() && in_.right().up()) {
            if (i + 1 != edit_pot_) {
                set_edit_pot(i + 1);
                pot_changed = true;
            }
        }

        if (pot_changed) {
            lcd_update(0, 1);
            lcd_update(13, 1, 3);
        }

        return;
    }

#if defined(WITH_SNAKE)
    if (mode_ == MODE_GAME_SNAKE) {
        if (i == LEFT && in_.right().up()) {
            snake_.turn_left(t);
        }

        if (i == RIGHT && in_.left().up()) {
            snake_.turn_right(t);
        }
    }
#endif

#if defined(WITH_HERO)
    if (mode_ == MODE_GAME_HERO) {
        if (i == STORE) {
            hero_.jump(t);
        }
    }
#endif

    if (mode_ == MODE_MIDI_IN_MONITOR ||
        mode_ == MODE_MIDI_OUT_MONITOR) {
        uint8_t m = mode_ - MODE_MIDI_IN_MONITOR;
        if (i == STORE) {
            // enable/pause capturing
            set_dirty(midi_mon_[m].toggle_pause(t));
        }

        if (i == LEFT && in_.right().up()) {
            midi_mon_[m].mode_prev(t);
        }

        if (i == RIGHT && in_.left().up()) {
            midi_mon_[m].mode_next(t);
        }

        if (i < MAX_POT && i < midi_mon::MODE_MAX && in_.left().up() && in_.right().up()) {
            midi_mon_[m].mode(i, t);
        }
    }
}

inline void
controller::on_hold(uint8_t i, unsigned long t) {
    debug(4, "on_hold: ", i);

    if (i == STORE && in_.left().hold() && in_.right().hold()) {
        set_mode(MODE_SETTINGS_FACTORY_RESET, t);
        return;
    }

    if (mode_ == MODE_NORMAL) {
        // hold STORE
        if (i == STORE) {
            if (!dirty_) { return; }

            if (bad_magic_) {
                set_mode(MODE_SETTINGS_FACTORY_RESET, t);
                return;
            }

            commit(t);

            return;
        }

        if (i == RIGHT && in_.left().up()) {
            show_master(true);
        }

        if ((i == LEFT && in_.right().down()) || (i == RIGHT && in_.left().down())) {
            // cancel changes
            if (dirty_) { set_program(prog_id_); }
        }

        return;
    }

    if (i == STORE) {
        if (mode_ >= MODE_SETTINGS_FIRST &&
            mode_ <= MODE_SETTINGS_LAST) {
            // No changes made - switch back to NORMAL;
            if (!dirty_) {
                set_mode(MODE_NORMAL, t);
                return;
            }

            // Changes made, but EEPROM not ready - confirm EEPROM Reset first;
            if (bad_magic_ && mode_ != MODE_SETTINGS_FACTORY_RESET) {
                set_mode(MODE_SETTINGS_FACTORY_RESET, t);
                return;
            }
        }

        switch (mode_) {
        case MODE_SETTINGS_CHANNEL:
            settings_.midi_channel = edit_value_ - 1;
            settings_.write(settings_.midi_channel);
            break;

        case MODE_SETTINGS_CTRL_IN:
            settings_.midi_pot_ctrl_in[edit_pot_ - 1] = edit_value_;
            settings_.write(settings_.midi_pot_ctrl_in[edit_pot_ - 1]);

            edit_value_master_ = edit_value_;
            set_dirty(false);

            // stay in MODE_SETTINGS_CTRL_IN for convenience
            store_blink_timer_.start(t);
            return;

        case MODE_SETTINGS_CTRL_OUT:
            settings_.midi_pot_ctrl_out[edit_pot_ - 1] = edit_value_;
            settings_.write(settings_.midi_pot_ctrl_out[edit_pot_ - 1]);

            edit_value_master_ = edit_value_;
            set_dirty(false);

            // stay in MODE_SETTINGS_CTRL_OUT for convenience
            store_blink_timer_.start(t);
            return;

        case MODE_SETTINGS_PROG_OUT:
            settings_.midi_out_prog = edit_value_;
            settings_.write(settings_.midi_out_prog);
            break;

        case MODE_SETTINGS_MIDI_FWD:
            settings_.midi_fwd = edit_value_;
            settings_.write(settings_.midi_fwd);
            break;

        case MODE_SETTINGS_HIDE_CURSOR:
            settings_.hide_cursor_delay_s = edit_value_;
            settings_.write(settings_.hide_cursor_delay_s);
            break;

        case MODE_SETTINGS_FACTORY_RESET:
            reset_eeprom();
            set_mode(MODE_NORMAL, t);
            set_program(0);
            store_blink_timer_.start(t);
            return;

#if defined(DEBUG)
        case MODE_SETTINGS_USB_DEBUG:
            settings_.usb_debug = edit_value_;
            settings_.write(settings_.usb_debug);
            debug_level_ = edit_value_;
            break;
#endif
        }

        set_mode(MODE_NORMAL, t);
        store_blink_timer_.start(t);

        return;
    }

    // cancel changes and back to NORMAL mode
    // hold RIGHT then press LEFT or
    // hold LEFT then press RIGHT
    if ((i == LEFT && in_.right().down()) || (i == RIGHT && in_.left().down())) {
        set_mode(MODE_NORMAL, t);
    }
}

inline void
controller::commit(unsigned long t) {
    // commit program change
    program_.write(prog_id_);
    program_master_ = program_;

    if (mode_ != MODE_SETTINGS_CTRL_IN && mode_ != MODE_SETTINGS_CTRL_OUT) {
        for(uint8_t i = 0; i < MAX_POT; i++) {
            pot_[i].red_dot(false);
        }
    }

    store_blink_timer_.start(t);
    set_dirty(false);
}

/* Available alphabet:
  ABCDEFGHIJKLMNOPRSTUVWXYZ[\]^_
  !"#$%&'()*+,-./
  :;<=>?@
  0123456789
*/

/*
joints = {
    { ' ', 'A' },
    { '_', '!' },
    { '/', ':' },
    { '@', '0' },
    { '9', ' ' }
};

ranges = {
    { ' ', ' ' },
    { 'A', '_' },
    { '!', '/' },
    { ':', '@' }
    { '0', '9' },
};
*/

inline char
rotate_char(char c, short dir) {
    if (dir > 0) {
        if (c == ' ') return 'A';
        if (c >= '0' && c < '9') return c + 1;
        if (c >= 'A' && c < '_') return c + 1;
        if (c >= '!' && c < '/') return c + 1;
        if (c >= ':' && c < '@') return c + 1;
        if (c == '_') return '!';
        if (c == '/') return ':';
        if (c == '@') return '0';
        if (c == '9') return ' ';
        return ' ';
    }

    if (c == ' ') return '9';
    if (c > '0' && c <= '9') return c - 1;
    if (c > 'A' && c <= '_') return c - 1;
    if (c > '!' && c <= '/') return c - 1;
    if (c > ':' && c <= '@') return c - 1;
    if (c == '0') return '@';
    if (c == ':') return '/';
    if (c == '!') return '_';
    if (c == 'A') return ' ';
    return ' ';
}

inline void
controller::on_rotate(short dir, unsigned long t) {
    debug(4, "on_rotate: ", dir);

    // rotate on RIGHT hold - change mode
    if (in_.right().hold()) {
        uint8_t m = rotate(mode_, MODE_NORMAL, MODE_MAX, dir);

        set_mode(m, t);
        return;
    }

    switch(mode_) {
    case MODE_NORMAL: {

        // rotate on LEFT hold - change program
        if (in_.left().hold()) {
            set_program(rotate(prog_id_, MAX_PROGRAMS, dir));

            return;
        }

        char& c = program_.title[cursor_pos_ - MIN_CURSOR_POS];
        c = rotate_char(c, dir);
        lcd_buf[0][cursor_pos_] = c;

        show_title_hint();

        lcd.setCursor(cursor_pos_, 0);
        lcd.write(c);
        show_cursor(t);

        set_dirty(program_ != program_master_);

        return;
    }

    case MODE_SETTINGS_CHANNEL:
    case MODE_SETTINGS_CTRL_IN:
    case MODE_SETTINGS_CTRL_OUT:
    case MODE_SETTINGS_PROG_OUT:
    case MODE_SETTINGS_MIDI_FWD:
    case MODE_SETTINGS_HIDE_CURSOR:
#if defined(DEBUG)
    case MODE_SETTINGS_USB_DEBUG:
#endif
        edit_value_ = rotate(edit_value_, edit_value_min_,
            edit_value_max_ + edit_value_step_, edit_value_step_ * dir);

        set_dirty(edit_value_ != edit_value_master_);

        print_edit_value();

        lcd_update(13, 1, 3);
        break;

#if defined(WITH_SNAKE)
    case MODE_GAME_SNAKE:
        if (dir > 0) {
            snake_.turn_right(t);
        } else {
            snake_.turn_left(t);
        }
        break;
#endif

    case MODE_MIDI_IN_MONITOR:
    case MODE_MIDI_OUT_MONITOR: {
        uint8_t m = mode_ - MODE_MIDI_IN_MONITOR;
        if (dir > 0) {
            midi_mon_[m].scroll_down(t);
        } else {
            midi_mon_[m].scroll_up(t);
        }
        break;
    }

    }
}

inline void
controller::start_edit(unsigned int value, unsigned int min, unsigned int max, unsigned int step) {
    edit_value_master_ = value;
    edit_value_ = edit_value_master_;
    edit_value_min_ = min;
    edit_value_max_ = max;
    edit_value_step_ = step;

    print_edit_value();
    set_dirty(false);
}

inline void
controller::print_edit_value() {
    if (edit_value_ > 127 &&
          (mode_ == MODE_SETTINGS_CTRL_IN ||
           mode_ == MODE_SETTINGS_CTRL_OUT)) {
        memcpy(lcd_buf[1] + 13, "OFF", 3);
    } else if (edit_value_ == 0 &&
          (mode_ == MODE_SETTINGS_PROG_OUT ||
           mode_ == MODE_SETTINGS_MIDI_FWD
#if defined(DEBUG)
           || mode_ == MODE_SETTINGS_USB_DEBUG
#endif
          )) {
        memcpy(lcd_buf[1] + 13, "OFF", 3);
    } else if (edit_value_ != 0 &&
        (mode_ == MODE_SETTINGS_PROG_OUT ||
        mode_ == MODE_SETTINGS_MIDI_FWD)) {
        memcpy(lcd_buf[1] + 13, "ON ", 3);
    } else {
        print_number(lcd_buf[1] + 13, 3, edit_value_);
    }
}

inline void
controller::set_edit_pot(uint8_t edit_pot) {
    edit_pot_ = edit_pot;

    for (uint8_t i = 0; i < MAX_POT; ++i) {
        pot_[i].red_dot(i == edit_pot_ - 1);
    }

    switch (mode_) {
    case MODE_SETTINGS_CTRL_IN:
        start_edit(settings_.midi_pot_ctrl_in[edit_pot_ - 1], 0, 128);
        break;
    case MODE_SETTINGS_CTRL_OUT:
        start_edit(settings_.midi_pot_ctrl_out[edit_pot_ - 1], 0, 128);
        break;
    }

    print_number(lcd_buf[1], 1, edit_pot_);

    // out_.loop_led(1 << (edit_loop_ - 1));
}

inline void
controller::set_mode(uint8_t m, unsigned long t) {
    debug(1, "set_mode: ", mode_, " -> ", m);

    if (m == mode_) return;

    if (mode_ == MODE_SETTINGS_FACTORY_RESET) {
        store_blink_timer_.stop();
    }

    if (mode_ == MODE_MIDI_IN_MONITOR ||
        mode_ == MODE_MIDI_OUT_MONITOR) {
        midi_mon_[mode_ - MODE_MIDI_IN_MONITOR].hide(t);
    }

    mode_ = m;

    set_dirty(false);

    if (mode_ >= MODE_SETTINGS_FIRST &&
        mode_ <= MODE_SETTINGS_LAST) {
        memcpy(lcd_buf[0], " Settings       ", 16);
    }

    switch (mode_) {
    case MODE_INITIAL:
        break;

    case MODE_NORMAL:
        set_dirty(program_ != program_master_);

        print_number(lcd_buf[0], 3, prog_id_ + 1);
        lcd_buf[0][3] = ' ';
        memcpy(lcd_buf[0] + 4, program_.title, 12);
        lcd_buf[1][15] = ' ';
        break;

    case MODE_SETTINGS_CHANNEL:
        start_edit(settings_.midi_channel + 1, 1, 16);
        memcpy(lcd_buf[1], "MIDI Channel ", 13);
        break;

    case MODE_SETTINGS_CTRL_IN:
        set_edit_pot(1);
        memcpy(lcd_buf[1] + 1, " Ctrl IN    ", 12);
        break;

    case MODE_SETTINGS_CTRL_OUT:
        set_edit_pot(1);
        memcpy(lcd_buf[1] + 1, " Ctrl OUT   ", 12);
        break;

    case MODE_SETTINGS_PROG_OUT:
        start_edit(settings_.midi_out_prog, 0, 1, 1);
        memcpy(lcd_buf[1], "Prog Chg OUT ", 13);
        break;

    case MODE_SETTINGS_MIDI_FWD:
        start_edit(settings_.midi_fwd, 0, 1, 1);
        memcpy(lcd_buf[1], "MIDI Forward ", 13);
        break;

    case MODE_SETTINGS_HIDE_CURSOR:
        start_edit(settings_.hide_cursor_delay_s, 1, 60);
        lcd_buf[0][15] = 's';
        memcpy(lcd_buf[1], " Hide cursor ", 13);
        break;

    case MODE_SETTINGS_FACTORY_RESET:
        memcpy(lcd_buf[1], " Factory Reset  ", 16);
        set_dirty(true);
        store_blink_timer_.start(t, 0, 150);
        break;

#if defined(DEBUG)
    case MODE_SETTINGS_USB_DEBUG:
        start_edit(settings_.usb_debug, 0, 9);
        memcpy(lcd_buf[1], "USB Debug    ", 13);
        break;
#endif

    case MODE_MIDI_IN_MONITOR:
        midi_mon_[0].show(t);
        memcpy(lcd_buf[0], "MIDI IN Monitor ", 16);
        memcpy(lcd_buf[1], "0               ", 16);
        set_dirty(midi_mon_[0].active());  // turn 'STORE' led 'ON', capture enabled
        break;

    case MODE_MIDI_OUT_MONITOR:
        midi_mon_[1].show(t);
        memcpy(lcd_buf[0], "MIDI OUT Monitor", 16);
        memcpy(lcd_buf[1], "0               ", 16);
        set_dirty(midi_mon_[1].active());  // turn 'STORE' led 'ON', capture enabled
        break;

    case MODE_ABOUT:
        memcpy(lcd_buf[0], "About " PQ4_VERSION, 16);
        memcpy(lcd_buf[1], " MIDI  PQ4 Eq    ", 16);
        break;

    case MODE_UPTIME:
        memcpy(lcd_buf[0], " Uptime         ", 16);
        memcpy(lcd_buf[1] + 12, " sec", 4);
        uptime_ = t / 1000;
        print_number(lcd_buf[1], 12, uptime_);
        break;

    case MODE_LOOP_COUNT:
        memcpy(lcd_buf[0], " Loop count     ", 16);
        memcpy(lcd_buf[1] + 14, " k", 2);
        uptime_ = loop_count_ / 1000;
        print_number(lcd_buf[1], 14, uptime_);
        break;

    case MODE_INPUT_COUNT:
        memcpy(lcd_buf[0], " Input count    ", 16);
        memcpy(lcd_buf[1] + 14, " k", 2);
        uptime_ = input_count_ / 1000;
        print_number(lcd_buf[1], 14, uptime_);
        break;

    case MODE_PC_COUNT:
        memcpy(lcd_buf[0], " PC count       ", 16);
        memcpy(lcd_buf[1] + 14, "  ", 2);
        uptime_ = pc_count_;
        print_number(lcd_buf[1], 14, uptime_);
        break;

#if defined(WITH_SNAKE)
    case MODE_GAME_SNAKE:
        snake_.setup();
        memcpy(lcd_buf[0], " Snake \4\3\3\3\3 \6  ", 16);
        memcpy(lcd_buf[1], " \1\1\1\1\1\1\4 16x2   ", 16);
        break;
#endif

#if defined(WITH_HERO)
    case MODE_GAME_HERO:
        hero_.setup();
        memcpy(lcd_buf[0], " Hero  \3        ", 16);
        memcpy(lcd_buf[1], "  \1   \6\5\7  16x2 ", 16);
        break;
#endif
    }

    if (mode_ != MODE_SETTINGS_CTRL_IN && mode_ != MODE_SETTINGS_CTRL_OUT) {
        for(uint8_t i = 0; i < MAX_POT; i++) {
            pot_[i].red_dot(program_master_.pot[i] != program_.pot[i]);
        }
    }

    hide_cursor();

    lcd_update();
/*
    if (mode_ == MODE_MIDI_IN_MONITOR ||
        mode_ == MODE_MIDI_OUT_MONITOR) {
        lcd.setCursor(2, 1);
        lcd.cursor();
    }
*/
}

inline void
controller::show_cursor(unsigned long t)
{
    lcd.setCursor(cursor_pos_, 0);
    lcd.cursor();
    hide_cursor_timer_.schedule(t + settings_.hide_cursor_delay_s * 1000);
}

inline void
controller::hide_cursor()
{
    hide_hint();
    lcd.noCursor();
    hide_cursor_timer_.cancel();
}

inline void
controller::show_title_hint()
{
    char c = lcd_buf[0][cursor_pos_];

    for (uint8_t i = cursor_pos_; i < LCD_COLUMNS; ++i, c = rotate_char(c, 1)) {
        lcd_buf[1][i] = c;
    }

    c = rotate_char(lcd_buf[0][cursor_pos_], -1);

    for (uint8_t i = cursor_pos_; i > 0; --i, c = rotate_char(c, -1)) {
        lcd_buf[1][i - 1] = c;
    }

    c = lcd_buf[0][cursor_pos_];

    lcd_update(0, 1, LCD_COLUMNS);
}

inline void
controller::show_bypass_hint(unsigned long t)
{
    lcd.noCursor();

    if (bypass_) {
        memcpy(lcd_buf[1], "BYPASS       ON ", 16);
    } else {
        memcpy(lcd_buf[1], "BYPASS       OFF", 16);
    }

    lcd_update(0, 1, LCD_COLUMNS);

    hide_cursor_timer_.schedule(t + settings_.hide_cursor_delay_s * 1000);
}

inline void
controller::hide_hint()
{
    if (mode_ == MODE_NORMAL) {
        memset(lcd_buf[1], ' ', LCD_COLUMNS);
        lcd_update(0, 1, LCD_COLUMNS);
    }
}

inline void
controller::set_dirty(bool dirty)
{
    if (dirty == dirty_) return;

    debug(3, "dirty = ", dirty);

    dirty_ = dirty;
}

inline void
controller::show_master(bool master)
{
    show_master_ = master;

    if (mode_ != MODE_NORMAL) {
        return;
    }
}

inline void
controller::button_handler::on_down(bool down, unsigned long t)
{
    controller_.on_down(id_, down, t);
}

inline void
controller::button_handler::on_hold(unsigned long t)
{
    controller_.on_hold(id_, t);
}

inline void
controller::encoder_handler::on_rotate(short dir, unsigned long t)
{
    controller_.on_rotate(dir, t);
}

inline void
controller::hide_cursor_timer_callback::operator()(unsigned long)
{
    controller_.hide_cursor();
}

inline void
controller::store_blink_timer_callback::operator()(unsigned long t)
{
    led_on_ = !led_on_;

    controller_.out_.store_led(led_on_);

    if (!led_on_) {
        if (rest_ == 0) {
            return;
        }

        if (rest_ != 0xFF) { rest_--; }
    }

    controller_.store_blink_timer_.schedule(t + period_);
}

inline void
controller::store_blink_timer_callback::start(unsigned long t, uint8_t count, unsigned long period)
{
    led_on_ = false;
    rest_ = count - 1;
    period_ = period;

    (*this)(t);
}

inline void
controller::store_blink_timer_callback::stop()
{
    rest_ = 0;
}

}
