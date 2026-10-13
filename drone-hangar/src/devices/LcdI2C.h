#ifndef __LCDI2C_H__
#define __LCDI2C_H__

#include "Lcd.h"
#include <LiquidCrystal_I2C.h>
#include <stdint.h>

class LcdI2C : public Lcd {
    private:
        LiquidCrystal_I2C lcd;

    public:
        LcdI2C(uint8_t addr, uint8_t cols, uint8_t rows);
        void init() override;
        void clear() override;
        void write(const char* msg, uint8_t col, uint8_t row) override;
};

#endif