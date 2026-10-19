#ifndef __CONTEXT_H__
#define __CONTEXT_H__



struct Context
{
    enum DroneCommand { NONE, CMD_TAKEOFF, CMD_LAND };
    bool isInPreAlarm = false;
    bool isInAlarm = false;
    bool okBlink = false;
    DroneCommand requestCommand = NONE;
    float currentDistance = 0.0f;
    bool alarmNotificationNeeded = false;
};

#endif
