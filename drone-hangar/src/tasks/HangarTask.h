#ifndef __HANGARTASK_H__
#define __HANGARTASK_H__

#include "../scheduler/Task.h"
#include "../model/Context.h"
#include "../Config.h"
#include "../devices/ServoMotor.h"
#include "../devices/Button.h"
#include "../devices/PresenceSensor.h"
#include "../devices/ProximitySensor.h"
#include "../devices/Light.h"
#include "../devices/Lcd.h"

class HangarTask : public Task {

    public: 
        enum State {DRONE_INSIDE, TAKE_OFF_OPENING, TAKE_OFF_WAITING, TAKE_OFF_CLOSING, DRONE_OUT, LANDING_OPENING, LANDING_WAITING, LANDING_CLOSING, ALARM_STATE};

    private:
        unsigned long stateTimestamp;   // Timestamp per le transizioni meccaniche della porta
        bool isTrackingDistance;            // True se il cronometro di uscita è in corso
        unsigned long exitTimestamp;    // Istante in cui il drone ha superato D1
        State state;
        Context* context;
        ServoMotor* servo;
        Button* resetButton;
        PresenceSensor* pir;
        ProximitySensor* proximity;
        Light* ledOne;
        Light* ledThree;
        Lcd* lcd;
        bool inside;
    
    public:
        HangarTask(Context* context, ServoMotor* servo, Button* resetButton, PresenceSensor* pir, ProximitySensor* proximity, Light* led, Light* ledThree, Lcd* lcd);
        void init(int period) override;
        void tick() override;

};

#endif