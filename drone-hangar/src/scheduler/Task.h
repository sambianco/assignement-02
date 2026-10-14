#ifndef __TASK_H__
#define __TASK_H__

class Task {
private:
    int myPeriod;
    int timeElapsed;

public:
    virtual ~Task() {}

    virtual void init(int period) {
        this->myPeriod = period;
        this->timeElapsed = 0;
    }

    virtual void tick() = 0;

    bool updateAndCheckTime(int basePeriod) {
        timeElapsed += basePeriod;
        if (timeElapsed >= myPeriod) {
            timeElapsed = 0;
            return true;
        }
        return false;
    }
};

#endif