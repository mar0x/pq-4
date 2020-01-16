
#pragma once

#include "debug.h"
#include "config.h"

namespace pq4 {

class program {
    static uint16_t ee_start_;
    static uint16_t ee_end_;

    enum {
        TITLE_SIZE = 12,

        POT_DEFAULT = 256,
    };

public:
    static uint16_t setup(uint16_t ee_start);

    void reset();
    bool empty() const;

    bool operator==(const program& n) const;
    bool operator!=(const program& n) const;

    bool read(uint8_t prog);
    bool write(uint8_t prog);

    char title[TITLE_SIZE] =
        { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
    char zero = 0;
    uint16_t pot[MAX_POT] = { POT_DEFAULT, POT_DEFAULT, POT_DEFAULT, POT_DEFAULT, POT_DEFAULT, POT_DEFAULT, POT_DEFAULT };

    enum {
        PROG_SIZE = sizeof(title) + sizeof(pot)
    };
};

uint16_t program::ee_start_ = 0;
uint16_t program::ee_end_ = 0;

inline uint16_t
program::setup(uint16_t ee_start) {
    ee_start_ = ee_start;
    ee_end_ = ee_start_ + PROG_SIZE * MAX_PROGRAMS;

    debug(7, "program::setup: start ", ee_start_);

    return ee_end_;
}

inline void
program::reset() {
    for (uint8_t i = 0; i < TITLE_SIZE; ++i) {
        title[i] = ' ';
    }
    for (uint8_t i = 0; i < MAX_POT; ++i) {
        pot[i] = POT_DEFAULT;
    }
}

inline bool
program::empty() const {
    return *this == program();
}

inline bool
program::operator==(const program& n) const {
    return memcmp(title, n.title, sizeof(title)) == 0 &&
      memcmp(pot, n.pot, sizeof(pot)) == 0;
}

inline bool
program::operator!=(const program& n) const {
    return memcmp(title, n.title, sizeof(title)) != 0 ||
      memcmp(pot, n.pot, sizeof(pot)) != 0;
}

inline bool
program::read(uint8_t prog) {
    debug(7, "program::read: prog ", prog);

    int addr = ee_start_ + PROG_SIZE * prog;
    EEPROM.get(addr, title);
    addr += sizeof(title);
    EEPROM.get(addr, pot);

    return true;
}

inline bool
program::write(uint8_t prog) {
    if (ee_start_ == 0) {
        return false;
    }

    debug(7, "program::write: prog ", prog);

    int addr = ee_start_ + PROG_SIZE * prog;
    EEPROM.put(addr, title);
    addr += sizeof(title);
    EEPROM.put(addr, pot);

    return true;
}

}
