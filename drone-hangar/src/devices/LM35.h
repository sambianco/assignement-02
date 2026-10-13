#ifndef __LM35_H__
#define __LM35_H__

#include "TempSensor.h"

class LM35 : public TempSensor {
private:
    uint8_t pin;

public:
    explicit LM35(uint8_t pin);
    float getTemperature() override;
};

#endif