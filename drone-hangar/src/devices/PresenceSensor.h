#ifndef __PRESENCE_SENSOR_H__
#define __PRESENCE_SENSOR_H__

#include <stdint.h>

class PresenceSensor {
public:
    virtual ~PresenceSensor() {}
    virtual void begin() = 0;
    virtual bool isDetected() = 0;
};

#endif