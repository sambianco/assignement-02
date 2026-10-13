#ifndef __TEMPSENSOR_H__
#define __TEMPSENSOR_H__

class TempSensor {
    public:
        virtual ~TempSensor() {}
        virtual void begin() {}
        virtual float getTemperature() = 0;
};

#endif