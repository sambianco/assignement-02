#ifndef __LCD_H__
#define __LCD_H__

class Lcd {
public:
    virtual ~Lcd() {}
    virtual void setCursor(int col, int row) = 0;
    virtual void clear() = 0;
    virtual void write(const char* msg) = 0;
};

#endif