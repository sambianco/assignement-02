#include "Timer.h"
#include <Arduino.h>

Timer::Timer() : period(0), lastTime(0) {}

void Timer::setupPeriod(int periodMs) {
    this->period = periodMs;
    this->lastTime = millis();
}

void Timer::waitForNextTick() {
    while (millis() - this->lastTime < this->period) {
    }
    this->lastTime += this->period;
}