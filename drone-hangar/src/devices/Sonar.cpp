#include "Sonar.h"
#include <Arduino.h>

#define SONAR_TIMEOUT_US 30000UL

Sonar::Sonar(uint8_t trigPin, uint8_t echoPin)
    : trigPin(trigPin), echoPin(echoPin) {}

void Sonar::begin() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    digitalWrite(trigPin, LOW);
}

float Sonar::getDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(3);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    unsigned long durationUs = pulseIn(echoPin, HIGH, SONAR_TIMEOUT_US);

    if (durationUs == 0) {
        return -1.0f;
    }
    
    const float vs = 331.5f + 0.6f * 20.0f; // m/s
    float timeSec = (durationUs / 1000000.0f) / 2.0f;
    return (timeSec * vs) * 100.0f;
}