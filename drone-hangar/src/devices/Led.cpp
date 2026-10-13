#include "Led.h"
#include <Arduino.h> // Serve per avere accesso a pinMode, digitalWrite, HIGH, LOW, OUTPUT

Led::Led(uint8_t pin) : pin(pin) {
    // Vuoto: niente comandi hardware qui dentro
}

void Led::begin() {
    pinMode(pin, OUTPUT);   // Configura il pin come uscita hardware
    digitalWrite(pin, LOW); // Assicura che parta spento
}

void Led::switchOn() {
    digitalWrite(pin, HIGH); // Porta la linea a 5V
}

void Led::switchOff() {
    digitalWrite(pin, LOW);  // Porta la linea a 0V
}