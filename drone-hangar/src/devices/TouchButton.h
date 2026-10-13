#ifndef __TOUCHBUTTON_H__
#define __TOUCHBUTTON_H__

#include "Button.h"

class TouchButton : public Button {

    private:
        uint8_t pin;

    public:
        TouchButton(uint8_t pin);
        void begin() override;
        bool isPressed() override;
};

#endif