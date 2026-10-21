#ifndef __COMM_TASK_H__
#define __COMM_TASK_H__

#include "../scheduler/Task.h"
#include "../model/Context.h"
#include <Arduino.h>

class CommTask : public Task {
private:
    Context* context;
    String inputBuffer;
    unsigned long lastDistSendTime;

public:
    CommTask(Context* context);
    void init(int period) override;
    void tick() override;

private:
    void processCommand(const String& cmd);
};

#endif