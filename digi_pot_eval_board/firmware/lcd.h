#pragma once

#include "config.h"

enum {
    LCD_LINES = 2,
    LCD_COLUMNS = 16,
};

static SPI_1602 lcd;
static char lcd_buf[LCD_LINES][LCD_COLUMNS];

inline void
lcd_buf_clear()
{
    for (uint8_t i = 0; i < LCD_LINES; i++) {
        memset(lcd_buf[i], ' ', LCD_COLUMNS);
    }
}

inline void
lcd_buf_clear(uint8_t line)
{
    memset(lcd_buf[line], ' ', LCD_COLUMNS);
}

inline void
lcd_setup()
{
    lcd.begin();
}

inline void
lcd_update(uint8_t col, uint8_t row, uint8_t size)
{
    lcd.setCursor(col, row);
    lcd.write(lcd_buf[row] + col, size);
}

inline void
lcd_update(uint8_t col, uint8_t row)
{
    lcd.setCursor(col, row);
    lcd.write(lcd_buf[row][col]);
}

inline void
lcd_update()
{
    for (uint8_t i = 0; i < LCD_LINES; i++) {
        lcd_update(0, i, LCD_COLUMNS);
    }
}

inline void
lcd_write(uint8_t col, uint8_t row, uint8_t c)
{
    lcd.setCursor(col, row);
    lcd.write(c);
}

