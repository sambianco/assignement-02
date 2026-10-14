#ifndef __TIMER_H__
#define __TIMER_H__

class Timer {
private:
    unsigned long period;
    unsigned long lastTime;

public:
    Timer();
    void setupPeriod(int periodMs);
    void waitForNextTick();
};

#endif