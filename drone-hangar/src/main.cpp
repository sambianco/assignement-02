#include <Arduino.h>
#include "scheduler/Scheduler.h"
#include "Config.h"

Scheduler sched;

void setup() {
  sched.init(BASE_PERIOD);
}

void loop() {
  sched.schedule();
}