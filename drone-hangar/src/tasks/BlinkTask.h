#ifndef __BLINKTASK_H__
#define __BLINKTASK_H__

#include "../devices/Light.h"
#include "../scheduler/Task.h"
#include "../model/Context.h"

class BlinkTask : public Task {

    public:
        enum State { IDLE, ON, OFF };
        
    private:
        Light* led;
        Context* context;
        State state;
        

    public:
        BlinkTask(Light* led, Context* context);
        void init(int period) override;
        void tick() override;
};

#endif