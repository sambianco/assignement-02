#include "CommTask.h"

CommTask::CommTask(Context* context) {
    this->context = context;
    this->inputBuffer = "";
    this->lastDistSendTime = 0;
}

void CommTask::init(int period) {
    Task::init(period);
    this->inputBuffer = "";
    this->inputBuffer.reserve(32);
    this->lastDistSendTime = 0;
}

void CommTask::tick() {
    while (Serial.available() > 0) {
        char c = (char)Serial.read();
        if (c == '\n' || c == '\r') {
            if (this->inputBuffer.length() > 0) {
                this->processCommand(this->inputBuffer);
                this->inputBuffer = "";
            }
        } else {
            this->inputBuffer += c;
        }
    }

    if (this->context == nullptr) {
        return;
    }

    // Alarm notification if needed
    if (this->context->alarmNotificationNeeded) {
        Serial.println("ALARM");
        this->context->alarmNotificationNeeded = false;
    }
     
    // Send current distance if it's greater than 0 and at least 200 ms have passed since the last send
    if (this->context->currentDistance > 0.0f && (millis() - this->lastDistSendTime >= 200)) {
        this->lastDistSendTime = millis();
        Serial.print("DIST:");
        Serial.println(this->context->currentDistance, 1);
    }
}

void CommTask::processCommand(const String& cmd) {
    if (this->context == nullptr) {
        return;
    }

    String cleanCmd = cmd;
    cleanCmd.trim();

    // Process commands for takeoff and landing
    if (cleanCmd.equalsIgnoreCase("CMD:TAKEOFF") || cleanCmd.equalsIgnoreCase("TAKEOFF") || cleanCmd.equalsIgnoreCase("CMD_TAKEOFF")) {
        this->context->requestCommand = Context::CMD_TAKEOFF;
    } else if (cleanCmd.equalsIgnoreCase("CMD:LAND") || cleanCmd.equalsIgnoreCase("LAND") || cleanCmd.equalsIgnoreCase("CMD_LAND")) {
        this->context->requestCommand = Context::CMD_LAND;
    }
}