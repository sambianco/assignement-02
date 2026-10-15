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

class HangarTask : public Task {

    public: 
        enum State {CLOSED, OPENING, OPEN, CLOSING, ALARM_STATE};

    private:
        unsigned long stateTimestamp;
        State state;
        Context* context;
        ServoMotor* servo;
        Button* resetButton;
        PresenceSensor* pir;
        ProximitySensor* proximity;
        Light* ledOne;
        Light* ledThree;
        bool inside;
    
    public:
        HangarTask(Context* context, ServoMotor* servo, Button* resetButton, PresenceSensor* pir, ProximitySensor* proximity, Light* led, Light* ledThree);
        void init(int period) override;
        void tick() override;

};

#endif