#ifndef __PROXIMITYSENSOR_H__
#define __PROXIMITYSENSOR_H__

class ProximitySensor {
    public:
        virtual ~ProximitySensor() {}
        virtual float getDistance() = 0;
};

#endif