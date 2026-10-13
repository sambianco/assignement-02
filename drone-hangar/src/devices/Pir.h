#ifndef __PIR_H__
#define __PIR_H__

#include "PresenceSensor.h"

class Pir : public PresenceSensor {
    private:
        uint8_t pin;

    public:
        Pir(uint8_t pin);
        void begin() override;
        bool isDetected() override;
};

#endif