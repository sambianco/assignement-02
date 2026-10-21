#include <Arduino.h>
#include "Config.h"
#include "model/Context.h"
#include "scheduler/Scheduler.h"

// Hardware Devices
#include "devices/Led.h"
#include "devices/TouchButton.h"
#include "devices/Pir.h"
#include "devices/Sonar.h"
#include "devices/LM35.h"
#include "devices/ServoMotorImpl.h"
#include "devices/LcdI2C.h"

// Tasks
#include "tasks/BlinkTask.h"
#include "tasks/HangarTask.h"
#include "tasks/TempTask.h"
#include "tasks/CommTask.h"

// Global components
Scheduler sched;
Context context;

// Hardware devices
Light* ledOne;
Light* ledTwo;
Light* ledThree;
Button* resetBtn;
PresenceSensor* pir;
ProximitySensor* sonar;
TempSensor* tempSensor;
ServoMotor* servo;
Lcd* lcd;

// Periodic tasks
HangarTask* hangarTask;
BlinkTask* blinkTask;
TempTask* tempTask;
CommTask* commTask;

void setup() {
    // 9600 baud rate for serial communication with the PC
    Serial.begin(9600);

    // Creation and initialization of hardware devices
    ledOne = new Led(PIN_LED_1);
    ledTwo = new Led(PIN_LED_2);
    ledThree = new Led(PIN_LED_3);
    
    ledOne->begin();
    ledTwo->begin();
    ledThree->begin();

    resetBtn = new TouchButton(PIN_RESET_BTN);
    resetBtn->begin();

    pir = new Pir(PIN_PIR);
    pir->begin();

    sonar = new Sonar(PIN_SONAR_TRIG, PIN_SONAR_ECHO);
    sonar->begin();

    tempSensor = new LM35(PIN_TEMP_SENSOR);
    tempSensor->begin();

    servo = new ServoMotorImpl(PIN_SERVO, SERVO_DOOR_CLOSED, SERVO_DOOR_OPEN);

    lcd = new LcdI2C(LCD_I2C_ADDR, LCD_COLS, LCD_ROWS);
    lcd->init();

    // Creation of periodic tasks
    hangarTask = new HangarTask(&context, servo, resetBtn, pir, sonar, ledOne, ledThree, lcd);
    blinkTask  = new BlinkTask(ledTwo, &context);
    tempTask   = new TempTask(tempSensor, &context);
    commTask   = new CommTask(&context);

    // Initialization of periodic tasks with their respective periods
    hangarTask->init(PERIOD_HANGAR); // 100 ms
    blinkTask->init(PERIOD_BLINK);   // 250 ms
    tempTask->init(PERIOD_TEMP);     // 200 ms
    commTask->init(PERIOD_COMM);     // 50 ms

    // Initialization of the scheduler with the base period
    sched.init(BASE_PERIOD);         // 50 ms
    
    // Adding tasks to the scheduler
    sched.addTask(commTask);
    sched.addTask(hangarTask);
    sched.addTask(blinkTask);
    sched.addTask(tempTask);
}

void loop() {
    // Scheduling of tasks
    sched.schedule();
}