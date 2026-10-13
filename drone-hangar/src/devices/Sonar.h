#ifndef __SONAR_H__
#define __SONAR_H__

#include "ProximitySensor.h"

class Sonar : public ProximitySensor {
    private:
        uint8_t trigPin;
        uint8_t echoPin;

    public:
        Sonar(uint8_t trigPin, uint8_t echoPin);
        void begin() override;
        float getDistance() override;
};

#endif