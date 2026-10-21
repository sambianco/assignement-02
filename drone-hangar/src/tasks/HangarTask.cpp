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
    this->isTrackingDistance = false;
    this->exitTimestamp = 0;
    this->stateTimestamp = 0;
    this->distance = 0.0f;
    this->wasDroneOutside = false;
}

void HangarTask::init(int period) {
    Task::init(period);
    this->state = DRONE_INSIDE;
    lcd->clear();
    lcd->write("DRONE INSIDE", 0, 0);
    this->ledOne->switchOn();
    this->ledThree->switchOff();
    this->servo->attach();
    this->servo->setPosition(SERVO_DOOR_CLOSED);
    this->isTrackingDistance = false;
    this->wasDroneOutside = false;

}

void HangarTask::tick(){
    if (this->state != ALARM_STATE && this->context != nullptr && this->context->isInAlarm) {
        
        // A) Salviamo dove si trovava il drone prima di cambiare stato
        this->wasDroneOutside = (this->state == TAKE_OFF_CLOSING || 
                                 this->state == DRONE_OUT || 
                                 this->state == LANDING_OPENING || 
                                 this->state == LANDING_WAITING);

        // B) Se il drone è fuori, notifichiamo la DRU via seriale (tramite flag nel context)
        if (this->wasDroneOutside) {
            this->context->alarmNotificationNeeded = true;
        }

        // C) Azioni fisiche immediate richieste dalla specifica
        this->servo->setPosition(SERVO_DOOR_CLOSED); // Chiude la porta (se era aperta)
        this->context->okBlink = false;              // Spegne il lampeggio di L2
        this->ledOne->switchOff();                   // Spegne L1
        this->ledThree->switchOn();                  // Accende L3 (LED rosso di allarme)
        
        if (this->lcd != nullptr) {
            this->lcd->clear();
            this->lcd->write("ALARM", 0, 0);         // Mostra ALARM sul display LCD
        }

        // D) Entriamo formalmente in ALARM_STATE
        this->state = ALARM_STATE;
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
            this->isTrackingDistance = false;
            this->state = TAKE_OFF_WAITING;
        }
        break;
    case TAKE_OFF_WAITING:
            distance = this->proximity->getDistance();
            context->currentDistance = distance;
            if (distance > D1_TAKEOFF_DIST) {
                if (!this->isTrackingDistance) {
                    this->isTrackingDistance = true;
                    this->exitTimestamp = millis();
                } else if (millis() - this->exitTimestamp >= T1_TAKEOFF_TIME) {
                    this->isTrackingDistance = false;
                    this->servo->setPosition(SERVO_DOOR_CLOSED);
                    this->stateTimestamp = millis();
                    this->state = TAKE_OFF_CLOSING;
                }
            } else {
                this->isTrackingDistance = false;
            }
        break;
    case TAKE_OFF_CLOSING:
        if (millis() - stateTimestamp >= TIME_DOOR_MOVE) {
            lcd->clear();
            lcd->write("DRONE OUT", 0, 0);
            context->okBlink = false;
            this->state = DRONE_OUT;
            this->context->isDroneInside = false;
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
        if (millis() - stateTimestamp >= TIME_DOOR_MOVE) {
            this->isTrackingDistance = false;
            this->state = LANDING_WAITING;
        }
        break;
    case LANDING_WAITING:
        distance = this->proximity->getDistance();
        this->context->currentDistance = distance;
        if (distance < D2_LANDING_DIST) {
            if (!this->isTrackingDistance) {
                this->isTrackingDistance = true;
                this->exitTimestamp = millis();
            } else if (millis() - this->exitTimestamp >= T2_LANDING_TIME) {
                this->isTrackingDistance = false;
                this->servo->setPosition(SERVO_DOOR_CLOSED);
                this->stateTimestamp = millis();
                this->state = LANDING_CLOSING;
            }
        } else {
            this->isTrackingDistance = false;
        }
        break;
    case LANDING_CLOSING:
        if (millis() - stateTimestamp >= TIME_DOOR_MOVE) {
            lcd->clear();
            lcd->write("DRONE INSIDE", 0, 0);
            context->okBlink = false;
            this->ledOne->switchOn();
            this->state = DRONE_INSIDE;
            this->context->isDroneInside = true;
        }
        break;
    case ALARM_STATE:
        if (this->resetButton->isPressed()) {
                this->context->isInAlarm = false;
                this->context->isInPreAlarm = false;
                
                this->ledThree->switchOff();
                this->servo->setPosition(SERVO_DOOR_CLOSED);
                this->isTrackingDistance = false;

                if (this->wasDroneOutside) {
                    this->lcd->clear();
                    this->lcd->write("DRONE OUT", 0, 0);
                    this->ledOne->switchOff();
                    this->state = DRONE_OUT;
                } else {
                    this->lcd->clear();
                    this->lcd->write("DRONE INSIDE", 0, 0);
                    this->ledOne->switchOn();
                    this->state = DRONE_INSIDE;
                }
            }
            break;
    }
}