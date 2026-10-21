#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <stdint.h>

class Button {
    public:
        virtual ~Button() {}
        virtual void begin() = 0;
        virtual bool isPressed() = 0;

};

#endif