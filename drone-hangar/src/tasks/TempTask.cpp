#include "TempTask.h"
#include "../Config.h"
#include <Arduino.h>

TempTask::TempTask(TempSensor* sensor, Context* context) {
    this->sensor = sensor;
    this->context = context;
    this->state = NORMAL;
    this->stateTimestamp = 0;
    this->currentTemp = 0.0f;
}

void TempTask::init(int period) {

    Task::init(period);
    this->state = NORMAL;
    this->stateTimestamp = 0;
    this->currentTemp = 0.0f;

    if (this->context != nullptr) {
        this->context->isInPreAlarm = false;
        this->context->isInAlarm = false;
    }
}

void TempTask::tick() {

    this->currentTemp = this->sensor->getTemperature();

    switch (this->state) {

        case NORMAL:
            if (this->currentTemp >= TEMP1_PREALARM) {
                this->stateTimestamp = millis();
                this->state = PRE_ALARM_CHECK;
            }
            break;

        case PRE_ALARM_CHECK:
            if (this->currentTemp < TEMP1_PREALARM) {
                this->state = NORMAL;
            } 
            else if (millis() - this->stateTimestamp >= T3_PREALARM_TIME) {
                this->context->isInPreAlarm = true;
                this->state = PRE_ALARM;
            }
            break;

        case PRE_ALARM:
            if (this->currentTemp < TEMP1_PREALARM) {
                this->context->isInPreAlarm = false;
                this->state = NORMAL;
            } 
            else if (this->currentTemp >= TEMP2_ALARM) {
                this->stateTimestamp = millis();
                this->state = ALARM_CHECK;
            }
            break;

        case ALARM_CHECK:
            if (this->currentTemp < TEMP2_ALARM) {
                this->state = PRE_ALARM;
            } 
            else if (millis() - this->stateTimestamp >= T4_ALARM_TIME) {
                this->context->isInPreAlarm = false;
                this->context->isInAlarm = true;
                this->state = ALARM;
            }
            break;

        case ALARM:
            if (!this->context->isInAlarm) {
                if (this->currentTemp < TEMP1_PREALARM) {
                    this->state = NORMAL;
                } else {
                    this->state = PRE_ALARM;
                    this->context->isInPreAlarm = true;
                }
            }
            break;
    }
}