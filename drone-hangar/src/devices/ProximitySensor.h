#ifndef PROXIMITYSENSOR_H
#define PROXIMITYSENSOR_H

class ProximitySensor {
    public:
        virtual ~ProximitySensor() {}
        virtual float getDistance() = 0;
};

#endif