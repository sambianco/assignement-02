#ifndef __TEMP_TASKS_H__
#define __TEMP_TASKS_H__

#include "../scheduler/Task.h"
#include "../devices/TempSensor.h"
#include "../model/Context.h"

enum State { NORMAL, PRE_ALARM_CHECK, PRE_ALARM, ALARM_CHECK, ALARM };

class TempTask : public Task {
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

};

#endif

