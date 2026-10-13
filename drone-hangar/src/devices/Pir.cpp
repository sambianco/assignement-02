#include "Pir.h"
#include <Arduino.h>

Pir::Pir(uint8_t pin) : pin(pin) {}

void Pir::begin() {
    pinMode(pin, INPUT);
}

bool Pir::isDetected() {
    return digitalRead(pin) == HIGH;
}