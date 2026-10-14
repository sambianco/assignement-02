#include "TempTask.h"
#include <Arduino.h>
#include "../Config.h" 

TempTask::TempTask(TempSensor* sensor, Context* context){
    this->sensor = sensor;
    this->context = context;
}

void TempTask::init(int period){
    Task::init(period);
    state = NORMAL;
    context->isInPreAlarm = false;
}

void TempTask::tick() {
    currentTemp = sensor->getTemperature();

    switch (state) {
        case NORMAL:
            if(currentTemp > TEMP1_PREALARM) {
                state = PRE_ALARM_CHECK;
            }
            break;

        case PRE_ALARM_CHECK:
            break;

        case PRE_ALARM:
            if(currentTemp > TEMP2_ALARM){
                state = ALARM_CHECK;
            }
            break;

        case ALARM_CHECK:
            break;

        case ALARM:
            break;
    }
}
}