#include "LM35.h"
#include <Arduino.h>

LM35::LM35(uint8_t pin) : pin(pin) {}

float LM35::getTemperature() {
    int rawValue = analogRead(pin);
    return (rawValue * 500.0f) / 1024.0f;
}