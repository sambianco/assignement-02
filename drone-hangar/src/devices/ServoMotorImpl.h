#ifndef __SERVO_MOTOR_IMPL_H__
#define __SERVO_MOTOR_IMPL_H__

#include "ServoMotor.h"
#include <Servo.h>

class ServoMotorImpl : public ServoMotor {
private:
    uint8_t pin;
    uint8_t minAngle;
    uint8_t maxAngle;
    Servo servo;

public:
    ServoMotorImpl(uint8_t pin, uint8_t minAngle = 0, uint8_t maxAngle = 180);
    void attach() override;
    void detach() override;
    void setPosition(uint8_t angle) override;
};

#endif