#ifndef __LCD_H__
#define __LCD_H__

class Lcd {
public:
    virtual ~Lcd() {}
    virtual void init() = 0;
    virtual void clear() = 0;
    virtual void write(const char* msg, uint8_t col, uint8_t row) = 0;
};

#endif