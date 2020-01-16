
#pragma once

/*

PC <P>
CC <C> <V>
LP [ <L> [ <V> ] ]
ST
RS

      3     4      15
PR [ <P> [ <L> [ <NAME> [ <PATCHES> ] ] ] ]
<P> <L> <NAME> [ <PATCHES> ]

MC [ <C> ]
<C>

MLI <L> [ <C> ]
MLO <L> [ <C> ]
MO [ 1/0 ]
MF [ 1/0 ]
DL [ <L> ]
MD [ <ms> ]
HC [ <s> ]
V
HEX [ <A> [ <S> [ <v> ] ] ]
:LLAAAATTDD...CC

FR <V>

*/

namespace pq4 {

struct serial_cmd {

    enum {
        CMD_UNKNOWN,
        CMD_PROG_CHANGE,        // PC p
        CMD_CTRL_CHANGE,        // CC c v
        CMD_POT,                // PT l v
        CMD_STORE,              // ST
        CMD_RESTORE,            // RS
        CMD_PROGRAM,            // PR p l n
        CMD_MIDI_CHANNEL,       // MC c
        CMD_MIDI_POT_IN_CTRL,   // MPI l c
        CMD_MIDI_POT_OUT_CTRL,  // MPO l c
        CMD_MIDI_PROG_OUT,      // MO o
        CMD_MIDI_FORWARD,       // MF f
        CMD_DEBUG_LEVEL,        // DL l
        CMD_MUTE_DELAY,         // MD d
        CMD_HIDE_CURSOR_DELAY,  // HC s
        CMD_VERSION,            // V
        CMD_HEX,                // HEX a s v
        CMD_FACTORY_RESET,      // FR v
        CMD_MIDI_MON_IN,        // MMI
        CMD_MIDI_MON_OUT,       // MMO

        MAX_SIZE = 50,
        MAX_ARGS = 5,
    };

    serial_cmd() : ready_(false), size_(0), command_(CMD_UNKNOWN) { }

    void read(uint8_t b);

    operator bool() const { return ready_; }

    void reset() {
        ready_ = false;
        size_ = 0;
        command_ = CMD_UNKNOWN;
    }

    uint8_t command() const { return command_; }

    bool get_arg(uint8_t n, uint8_t& v) {
        if (n >= arg_size_) {
            return false;
        }

        v = 0;

        for (uint8_t p = arg_[n].start; p < arg_[n].end; p++) {
            v = v * 10 + (buf_[p] - '0');
        }

        return true;
    }

    bool get_arg(uint8_t n, uint16_t& v) {
        if (n >= arg_size_) {
            return false;
        }

        v = 0;

        for (uint8_t p = arg_[n].start; p < arg_[n].end; p++) {
            v = v * 10 + (buf_[p] - '0');
        }

        return true;
    }

    template<typename T>
    bool get_arg(uint8_t n, T& v) {
        if (n >= arg_size_) {
            return false;
        }

        uint8_t l = arg_[n].end - arg_[n].start;
        if (l > sizeof(T)) { l = sizeof(T); }

        memcpy(&v, &buf_[arg_[n].start], l);

        return true;
    }

//private:
    void parse();

    struct arg {
        uint8_t start;
        uint8_t end;
    };

    char buf_[MAX_SIZE];
    bool ready_;
    uint8_t size_;
    uint8_t command_;

    arg arg_[MAX_ARGS];
    uint8_t arg_size_;
};

inline void
serial_cmd::read(uint8_t b) {
    if (b == '\n' || b == '\r') {
        buf_[size_] = 0;

        parse();
        ready_ = true;

        return;
    }

    if (size_ >= MAX_SIZE) {
        return;
    }

    buf_[size_++] = b;
}

inline void
serial_cmd::parse() {
    arg_size_ = 0;
    arg *a = &arg_[0];
    char in_quote = 0;

    a->start = 0;

    for (uint8_t i = 0; i < size_; i++) {
        char b = buf_[i];

        if (b == '"' && i == a->start) {
            a->start = i + 1;
            in_quote = b;
            continue;
        }

        if (in_quote && in_quote == b) {
            a->end = i;

            debug(7, "arg #", arg_size_, ", start ", a->start, ", end ", a->end);
            //log_window::println("arg #", arg_size_, ", start ", a->start, ", end ", a->end);

            arg_size_++;
            a++;

            a->start = i + 1;
            in_quote = 0;

            if (arg_size_ >= MAX_ARGS) {
                return;
            }
        }

        if (in_quote == 0 && (b == ' ' || b == '\t')) {
            if (i == a->start) {
                a->start = i + 1;
                continue;
            }

            a->end = i;

            //log_window::println("arg #", arg_size_, ", start ", a->start, ", end ", a->end);

            arg_size_++;
            a++;

            a->start = i + 1;

            if (arg_size_ >= MAX_ARGS) {
                return;
            }
        }
    }

    if (a->start < size_) {

        a->end = size_;

        //log_window::println("arg #", arg_size_, ", start ", a->start, ", end ", a->end);

        arg_size_++;
    }

    if (arg_size_ > 0) {
        a = &arg_[0];

        if (a->end - a->start == 1 && buf_[a->start] == 'V') {
            command_ = CMD_VERSION;
        }

        if (a->end - a->start == 2) {
            char *b = &buf_[a->start];

            if (b[0] == 'P' && b[1] == 'C') { command_ = CMD_PROG_CHANGE; }
            if (b[0] == 'C' && b[1] == 'C') { command_ = CMD_CTRL_CHANGE; }
            if (b[0] == 'P' && b[1] == 'T') { command_ = CMD_POT; }
            if (b[0] == 'S' && b[1] == 'T') { command_ = CMD_STORE; }
            if (b[0] == 'R' && b[1] == 'S') { command_ = CMD_RESTORE; }
            if (b[0] == 'P' && b[1] == 'R') { command_ = CMD_PROGRAM; }
            if (b[0] == 'M' && b[1] == 'C') { command_ = CMD_MIDI_CHANNEL; }
            if (b[0] == 'M' && b[1] == 'O') { command_ = CMD_MIDI_PROG_OUT; }
            if (b[0] == 'M' && b[1] == 'F') { command_ = CMD_MIDI_FORWARD; }
            if (b[0] == 'D' && b[1] == 'L') { command_ = CMD_DEBUG_LEVEL; }
            if (b[0] == 'M' && b[1] == 'D') { command_ = CMD_MUTE_DELAY; }
            if (b[0] == 'H' && b[1] == 'C') { command_ = CMD_HIDE_CURSOR_DELAY; }
            if (b[0] == 'F' && b[1] == 'R') { command_ = CMD_FACTORY_RESET; }
        }

        if (a->end - a->start == 3) {
            char *b = &buf_[a->start];

            if (b[0] == 'M' && b[1] == 'P' && b[2] == 'I') { command_ = CMD_MIDI_POT_IN_CTRL; }
            if (b[0] == 'M' && b[1] == 'P' && b[2] == 'O') { command_ = CMD_MIDI_POT_OUT_CTRL; }
            if (b[0] == 'H' && b[1] == 'E' && b[2] == 'X') { command_ = CMD_HEX; }
            if (b[0] == 'M' && b[1] == 'M' && b[2] == 'I') { command_ = CMD_MIDI_MON_IN; }
            if (b[0] == 'M' && b[1] == 'M' && b[2] == 'O') { command_ = CMD_MIDI_MON_OUT; }
        }
    }
}

}
