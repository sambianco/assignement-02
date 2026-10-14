#ifndef __TEMP_TASK_H__
#define __TEMP_TASK_H__

#include "../scheduler/Task.h"
#include "../devices/TempSensor.h"
#include "../model/Context.h"

class TempTask : public Task {

public:
    enum State { 
        NORMAL, 
        PRE_ALARM_CHECK, 
        PRE_ALARM, 
        ALARM_CHECK, 
        ALARM 
    };

private:
    TempSensor* sensor;
    Context* context;
    State state;
    unsigned long stateTimestamp;
    float currentTemp;

public:
    TempTask(TempSensor* sensor, Context* context);
    void init(int period) override;
    void tick() override;
    float getTemperature() {
        return currentTemp;
    }
    State getState() { 
        return state; 
    }
};

#endif

