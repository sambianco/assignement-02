#include "ServoMotorImpl.h"
#include <Arduino.h>

ServoMotorImpl::ServoMotorImpl(uint8_t pin, uint8_t minAngle, uint8_t maxAngle)
    : pin(pin), minAngle(minAngle), maxAngle(maxAngle) {
}

void ServoMotorImpl::attach() {
    servo.attach(pin);
}

void ServoMotorImpl::detach() {
    servo.detach();
}

void ServoMotorImpl::setPosition(uint8_t angle) {
    uint8_t targetAngle = constrain(angle, minAngle, maxAngle);
    servo.write(targetAngle);
}