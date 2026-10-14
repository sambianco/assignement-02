#ifndef __CONTEXT_H__
#define __CONTEXT_H__

enum DroneCommand { NONE, CMD_TAKEOFF, CMD_LAND };

struct Context
{
    bool isInPreAlarm = false;
    bool isInAlarm = false;
    bool okBlink = false;
    DroneCommand requestCommand = NONE;
    float currentDistance = 0.0f;
};

#endif
