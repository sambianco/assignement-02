#ifndef __LED_H__
#define __LED_H__
    
#include "Light.h"

// In C++ la derivazione pubblica da un'interfaccia si scrive: public NomeClasseBase
class Led : public Light {
private:
    uint8_t pin; // Campo privato: il numero di pin a cui è connesso il LED

public:
    // Costruttore: riceve il pin hardware
    Led(uint8_t pin);

    // Override dei metodi virtuali puri definiti in Light.h
    void begin() override;
    void switchOn() override;
    void switchOff() override;
    
};

#endif