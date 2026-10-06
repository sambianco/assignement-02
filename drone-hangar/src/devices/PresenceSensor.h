#ifndef __PRESENCE_SENSOR_H__
#define __PRESENCE_SENSOR_H__

class PresenceSensor {
public:
    virtual ~PresenceSensor() {}
    virtual bool isDetected() = 0;
};

#endif