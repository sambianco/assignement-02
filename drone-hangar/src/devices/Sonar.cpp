#include "Sonar.h"
#include <Arduino.h>

#define SONAR_TIMEOUT_US 30000UL

Sonar::Sonar(uint8_t trigPin, uint8_t echoPin)
    : trigPin(trigPin), echoPin(echoPin) {}

void Sonar::begin() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    digitalWrite(trigPin, LOW); // Assicura che il trigger parta a riposo
}

float Sonar::getDistance() {
    // Genera l'impulso di trigger da 10 microsecondi
    digitalWrite(trigPin, LOW);
    delayMicroseconds(3);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    unsigned long durationUs = pulseIn(echoPin, HIGH, SONAR_TIMEOUT_US);

    // Se durationUs è 0 significa che non c'è eco (timeout / fuori portata)
    if (durationUs == 0) {
        return -1.0f; // Codice di errore / nessun ostacolo rilevato
    }

    // vs = 343.5 m/s a 20°C
    // Calcolo compatto: distanza in cm = (durata in us * 0.03435) / 2
    const float vs = 331.5f + 0.6f * 20.0f; // m/s
    float timeSec = (durationUs / 1000000.0f) / 2.0f;
    return (timeSec * vs) * 100.0f;
}