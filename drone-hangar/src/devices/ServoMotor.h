#ifndef __SERVO_MOTOR_H__
#define __SERVO_MOTOR_H__

#include <stdint.h>

class ServoMotor {
public:
    virtual ~ServoMotor() {}
    virtual void attach() = 0;
    virtual void detach() = 0;
    virtual void setPosition(uint8_t angle) = 0;
};

#endif