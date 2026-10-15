#include "HangarTask.h"
#include <Arduino.h>

HangarTask::HangarTask(Context* context, ServoMotor* servo, Button* resetButton, PresenceSensor* pir, ProximitySensor* proximity, Light* ledOne, Light* ledThree, Lcd* lcd) {
    this->context = context;
    this->servo = servo;
    this->resetButton = resetButton;
    this-> pir = pir;
    this->proximity = proximity;
    this->ledOne = ledOne;
    this->ledThree = ledThree;
    this->lcd = lcd;
    this->isTrackingExit = false;
    this->exitTimestamp = 0;
    this->stateTimestamp = 0;
}

void HangarTask::init(int period) {
    Task::init(period);
    this->state = DRONE_INSIDE;
    lcd->clear();
    lcd->write("DRONE INSIDE", 0, 0);
    this->ledOne->switchOn();
    this->ledThree->switchOff();
    this->servo->attach();
    this->servo->setPosition(0);
    this->isTrackingExit = false;

}

void HangarTask::tick(){
    if (state != ALARM_STATE && this->context != nullptr && this->context->isInAlarm) {
        state = ALARM_STATE;
    }
    
    switch (state)
    {
    case DRONE_INSIDE:
        if(context->requestCommand == context->CMD_TAKEOFF && context->isInPreAlarm != true) {
            context->requestCommand = context->NONE;
            context->okBlink = true;
            ledOne->switchOff();
            lcd->clear();
            lcd->write("TAKE OFF", 0, 0);
            servo->setPosition(SERVO_DOOR_OPEN);
            stateTimestamp = millis();
            this->state = TAKE_OFF_OPENING;
        }
        break;
    case TAKE_OFF_OPENING:
        if (millis() - stateTimestamp >= TIME_DOOR_MOVE) {
            this->isTrackingExit = false;
            this->state = TAKE_OFF_WAITING;
        }
        break;
    case TAKE_OFF_WAITING: {
            float distance = this->proximity->getDistance();
            if (distance > D1_TAKEOFF_DIST) {
                if (!this->isTrackingExit) {
                    this->isTrackingExit = true;
                    this->exitTimestamp = millis();
                } else if (millis() - this->exitTimestamp >= T1_TAKEOFF_TIME) {
                    this->isTrackingExit = false;
                    this->servo->setPosition(SERVO_DOOR_CLOSED);
                    this->stateTimestamp = millis();
                    this->state = TAKE_OFF_CLOSING;
                }
            } else {
                this->isTrackingExit = false;
            }
        break;
        }
    case TAKE_OFF_CLOSING:
        if (millis() - stateTimestamp >= TIME_DOOR_MOVE) {
            lcd->clear();
            lcd->write("DRONE OUT", 0, 0);
            context->okBlink = false;
            this->state = DRONE_OUT;
        }
        break;
    case DRONE_OUT:
        if (context->requestCommand == Context::CMD_LAND && pir->isDetected() && !context->isInPreAlarm) {
            this->context->requestCommand = Context::NONE;  // Consumo evento
            context->okBlink = true;                        // Avvio lampeggio L2
            lcd->clear();                                   // Puliamo LCD
            lcd->write("LANDING", 0, 0);                    // Comunichiamo la posizione
            servo->setPosition(SERVO_DOOR_OPEN);            // Apriamo la porta
            stateTimestamp = millis();                      // Teniamo il tempo di apertura
            this->state = LANDING_OPENING;                  // Cambiamo stato
        }
        break;
    case LANDING_OPENING:
        break;
    case LANDING_WAITING:
        break;
    case LANDING_CLOSING:
        break;
    case ALARM_STATE:
        this->servo->detach();
        this->ledThree->switchOn();
        if (this->resetButton->isPressed()) {
            this->context->isInAlarm = false;
            this->context->isInPreAlarm = false;
            this->ledThree->switchOff();
        }
        break;
    }
}