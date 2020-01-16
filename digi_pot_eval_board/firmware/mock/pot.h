
#pragma once

namespace pq4 {

struct pot {

    static uint8_t changed_mask;

    static void setup() { }

    pot(int id) : id_(id), val_(DEFAULT_POT_VALUE) {
    }

    void create_window() {
        int y = 14 + 5 * (id_ % 2);
        int x =  2 + 10 * (id_ / 2);

        //log_window::println("pot::create_window(): ", id_, ", ", val_);

        if (id_ == 6) {
            y = 9;
            x = 2;
        }

        win_ = newwin(5, 9, y, x);
        box(win_, 0, 0);
        mvwprintw(win_, 1, 2, "%c", 'A' + id_);
        mvwprintw(win_, 3, 2, "%c", 'a' + id_);

        mvwprintw(win_, 2, 3, "%3d", val_);

        mvwprintw(win_, 1, 4, ".");
        mvwprintw(win_, 3, 4, ".");
        wrefresh(win_);
    }

    void update(unsigned long t, int key) {
        int16_t old = val_;

        if (key == 'A' + id_) {
            mvwprintw(win_, 1, 4, "^");
            val_ += 4;
            if (val_ > MAX_POT_VALUE) val_ = MAX_POT_VALUE;
        } else {
            mvwprintw(win_, 1, 4, ".");
        }

        if (key == 'a' + id_) {
            mvwprintw(win_, 3, 4, "v");
            val_ -= 4;
            if (val_ < MIN_POT_VALUE) val_ = MIN_POT_VALUE;
        } else {
            mvwprintw(win_, 3, 4, ".");
        }

        if (old != val_) {
            mvwprintw(win_, 2, 3, "%3d*", val_);
            changed(true);
        }

        wrefresh(win_);
    }

    uint16_t get(bool &c) const {
        c = changed();

        return value();
    }

    uint16_t value() const {
        if (changed()) {
            mvwprintw(win_, 2, 3, "%3d ", val_);
            changed(false);
        }

        return val_;
    }

    void value(uint16_t v) {
        int16_t old = val_;

        if (v < MIN_POT_VALUE) v = MIN_POT_VALUE;
        if (v > MAX_POT_VALUE) v = MAX_POT_VALUE;

        val_ = v;

        if (old != val_ || changed()) {
            //log_window::println("pot::update(): ", id_, ", ", old, " -> ", val_);
            mvwprintw(win_, 2, 3, "%3d ", val_);
        }

        if (changed()) {
            changed(false);
        }
    }

    void red_dot(uint8_t v) {
        mvwprintw(win_, 3, 7, "%c", v ? 'o' : ' ');
    }

    void update_relay(bool v) {
        mvwprintw(win_, 1, 7, "%c", v ? '\\' : '/');
    }

private:

    bool changed() const { return (changed_mask & (1 << id_)) != 0; }

    void changed(bool v) const {
        if (v) {
            changed_mask |= 1 << id_;
        } else {
            changed_mask &= ~(1 << id_);
        }
    }

private:
    WINDOW *win_;
    uint8_t id_;
    int16_t val_ = DEFAULT_POT_VALUE;
};

uint8_t pot::changed_mask = 0;

pot pots_[MAX_POT] = {0, 1, 2, 3, 4, 5, 6};

}
