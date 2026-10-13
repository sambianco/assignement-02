#include "TouchButton.h"
#include <Arduino.h>

TouchButton::TouchButton(uint8_t pin) : pin(pin) {}

void TouchButton::begin() {
    pinMode(pin, INPUT);
}

bool TouchButton::isPressed() {
    return digitalRead(pin) == HIGH;
}