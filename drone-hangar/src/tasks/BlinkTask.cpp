#include "BlinkTask.h"
#include <Arduino.h>

BlinkTask::BlinkTask(Light* led, Context* context) {
    this->led = led;
    this->context = context;
}

void BlinkTask::init(int period) {
    Task::init(period);
    this->state = IDLE;
    if (this->led != nullptr) {
        this->led->switchOff();
    }
}

void BlinkTask::tick() {
    switch (this->state) {

        case IDLE:
            if (this->context != nullptr && this->context->okBlink) {
                this->led->switchOn();
                this->state = ON;
            }
            break;

        case ON:
            if (this->context == nullptr || !this->context->okBlink) {
                this->led->switchOff();
                this->state = IDLE;
            } else {
                this->led->switchOff();
                this->state = OFF;
            }
            break;

        case OFF:
            if (this->context != nullptr && this->context->okBlink) {
                this->led->switchOn();
                this->state = ON;
            } else {
                this->state = IDLE;
            }
            break;
    }
}