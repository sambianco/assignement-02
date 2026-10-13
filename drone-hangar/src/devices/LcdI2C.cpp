#include "LcdI2C.h"
#include <Arduino.h>

LcdI2C::LcdI2C(uint8_t addr, uint8_t cols, uint8_t rows)
    : lcd(addr, cols, rows) {
}

void LcdI2C::init() {
    this->lcd.init();
    this->lcd.backlight();
    this->lcd.clear();
}

void LcdI2C::clear() {
    this->lcd.clear();
}

void LcdI2C::write(const char* msg, uint8_t col, uint8_t row) {
    this->lcd.setCursor(col, row);
    this->lcd.print(msg);
}