#include "Led.h"
#include <Arduino.h>

Led::Led(uint8_t pin) : pin(pin) {}

void Led::begin() {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}

void Led::switchOn() {
    digitalWrite(pin, HIGH);
}

void Led::switchOff() {
    digitalWrite(pin, LOW);
}