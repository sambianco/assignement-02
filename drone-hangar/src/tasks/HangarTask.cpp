#include "HangarTask.h"
#include <Arduino.h>

HangarTask::HangarTask(Context* context, ServoMotor* servo, Button* resetButton, PresenceSensor* pir, ProximitySensor* proximity, Light* ledOne, Light* ledThree) {
    this->context = context;
    this->servo = servo;
    this->resetButton = resetButton;
    this-> pir = pir;
    this->proximity = proximity;
    this->ledOne = ledOne;
    this->ledThree = ledThree;
}

void HangarTask::init(int period) {
    Task::init(period);
    this->state = CLOSED;
    this->ledOne->switchOff();
    this->ledThree->switchOff();
    this->servo->attach();
    this->servo->setPosition(0);
}

void HangarTask::tick(){
    if (state != ALARM_STATE && this->context != nullptr && this->context->isInAlarm) {
        state = ALARM_STATE;
    }
    
    switch (state)
    {
    case CLOSED:
        break;
    case OPENING:
        break;
    case OPEN:
        break;
    case CLOSING:
        break;
    case ALARM_STATE:
        this->servo->detach();
        this->ledThree->switchOn();
        if (this->resetButton->isPressed()) {
            this->context->isInAlarm = false;
            this->context->isInPreAlarm = false;
            this->ledThree->switchOff();
            this->servo->attach();
            this->servo->setPosition(0);
            this->state = CLOSED;
        }
        break;
    }
}