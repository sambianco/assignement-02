#include "Led.h"
#include <Arduino.h> // Serve per avere accesso a pinMode, digitalWrite, HIGH, LOW, OUTPUT

Led::Led(int pin) {
    this->pin = pin;
    pinMode(pin, OUTPUT); // Inizializza il pin hardware come uscita
}

void Led::switchOn() {
    digitalWrite(pin, HIGH); // Porta la linea a 5V
}

void Led::switchOff() {
    digitalWrite(pin, LOW);  // Porta la linea a 0V
}