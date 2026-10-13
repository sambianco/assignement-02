#ifndef __SERVO_MOTOR_H__
#define __SERVO_MOTOR_H__

#include <stdint.h>

class ServoMotor {
public:
    virtual ~ServoMotor() {}
    virtual void attach() = 0;
    virtual void detach() = 0;
    virtual void setPosition(uint8_t angle) = 0; // Usiamo uint8_t coerentemente (0-180 sta in 1 byte)
};

#endif