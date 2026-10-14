#ifndef __LED_H__
#define __LED_H__
    
#include "Light.h"

class Led : public Light {
private:
    uint8_t pin;

public:
    Led(uint8_t pin);
    void begin() override;
    void switchOn() override;
    void switchOff() override;
    
};

#endif