
#if !defined(ARDUINO)

#include <ncurses.h>

WINDOW *pm_win;
WINDOW *pq_win;
WINDOW *key_win;
WINDOW *lcd_win;
WINDOW *np_win;
WINDOW *bp_win;

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

int random(int) { return 0; }

#define PROGMEM
#define pgm_read_word
#define pgm_read_byte_near(p) (*(p))
#define strcpy_P strcpy

#include "mock/serial.h"

#include "config.h"
#include "debug.h"

#include "mock/serial_pts.h"
#include "mock/time.h"
#include "mock/eeprom.h"
#include "mock/liquid_crystal.h"
#include "mock/in.h"
#include "mock/out.h"

#include "mock/log_window.h"
WINDOW *log_window::win;

#include "mock/pot.h"

#include "controller.h"

#include "mock/nav_panel.h"

namespace pq4 {

void update_relay(uint8_t i, bool v) {
    pq4::controller_.pot_[i].update_relay(v);
}

}

int main() {
/*
    int maxlines = LINES - 1;
    int maxcols = COLS - 1;
*/
    int row, col;

    gettimeofday(&start_time, 0);

#if defined(DEBUG)
    debug_level_ = 7;
#endif

    initscr();
    raw();
    //cbreak();
    noecho();


    // clear();
    halfdelay(1);

    keypad(stdscr, TRUE);

/*
    initscr();
    clear();
    noecho();
    cbreak();
*/

    getmaxyx(stdscr, row, col);

    mvprintw(0, 0, "maxyx: %d x %d\n", row, col);

    pm_win = newwin(4 + LCD_LINES, 82, 4, 1);
    pq_win = newwin(4 + LCD_LINES + 3 * 5 + 4, 1 + 3 * 10, 4, 1);
    key_win = newwin(3, 5, 6, 29);
    lcd_win = newwin(2 + LCD_LINES, 2 + LCD_COLUMNS, 5, 7);
    bp_win = newwin(4, 9, 4 + LCD_LINES + 3 * 5 + 3, 12);

    WINDOW *log_tray = newwin(27, 82, 2 + LCD_LINES, 33);

    log_window::create(25, 80, 3 + LCD_LINES, 34);

    wrefresh(lcd_win);
    wrefresh(log_window::win);

    WINDOW *key_win = newwin(1, 3, 1, 30);

    (void) getch();

    box(lcd_win, 0, 0);

    box(log_tray, 0, 0);
    wrefresh(log_tray);

//    box(pm_win, 0, 0);
//    wrefresh(pm_win);

    box(pq_win, 0, 0);
    wrefresh(pq_win);

    box(bp_win, 0, 0);
    wrefresh(bp_win);

    for (int i = 0; i < 7; i++) {
        pq4::controller_.pot_[i].create_window();
    }

    pq4::nav_panel np;

    np.create_window();

    pq4::controller_.setup();

    /* Get all the mouse events */
    mousemask(ALL_MOUSE_EVENTS, NULL);

    bool quit = false;

    while (!quit) {
        int c = getch();
        //int c = wgetch(pm_win);

        if (c != -1) {
            //log_window::println("key: ", c);
            debug(2, "key: ", c);
        }

        pq4::last_key = c;

        mvwprintw(key_win, 0, 0, "%3d", c);
        wrefresh(key_win);

        if (c == 927 || c == 'q') {
            quit = true;
        }

        for (uint8_t i = 0; i < pq4::MAX_POT; i++) {
            pq4::controller_.pot_[i].update(0, c);
        }

        pq4::controller_.loop();

        np.update(0, c);

        if (lcd.cur_on) {
            lcd.commit_show_cursor();
        }
    }

    refresh();
    endwin();

    return 0;
}

#endif
