#include "ServoMotorImpl.h"
#include <Arduino.h>

ServoMotorImpl::ServoMotorImpl(uint8_t pin, uint8_t minAngle, uint8_t maxAngle)
    : pin(pin), minAngle(minAngle), maxAngle(maxAngle) {
    // Il costruttore memorizza solo i dati di configurazione
}

void ServoMotorImpl::attach() {
    servo.attach(pin); // Il timer PWM e il pin partono qui (chiamato in setup())
}

void ServoMotorImpl::detach() {
    servo.detach(); // Utile per togliere alimentazione al motore quando è fermo
}

void ServoMotorImpl::setPosition(uint8_t angle) {
    uint8_t targetAngle = constrain(angle, minAngle, maxAngle);
    servo.write(targetAngle);
}