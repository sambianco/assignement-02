#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include "Timer.h"
#include "Task.h"

#define MAX_TASKS 10

class Scheduler {
private:
    int basePeriod;
    int nTasks;
    Task* taskList[MAX_TASKS];
    Timer timer;

public:
    void init(int basePeriod);
    bool addTask(Task* task);
    void schedule();
};

#endif