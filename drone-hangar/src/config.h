#ifndef __CONFIG_H__
#define __CONFIG_H__

// PIN MAPPING
#define PIN_SONAR_TRIG     3
#define PIN_SONAR_ECHO     4
#define PIN_LED_1          6   // System ON
#define PIN_LED_2          7   // Drone Active (Blink)
#define PIN_LED_3          8   // Alarm
#define PIN_SERVO          9   // Hangar Door (HD)
#define PIN_PIR           10   // Drone Presence Detector (DPD)
#define PIN_RESET_BTN     12   // Tactile Reset Button
#define PIN_TEMP_SENSOR   A2   // Analog Temperature Sensor

// I2C LCD
#define LCD_I2C_ADDR    0x27
#define LCD_COLS          16
#define LCD_ROWS           2

// TEMPORAL PARAMETERS (ms)
#define BASE_PERIOD       50
#define PERIOD_COMM       50
#define PERIOD_HANGAR    100
#define PERIOD_TEMP      200
#define PERIOD_BLINK     250

// CONTROL PARAMETERS
#define D1_TAKEOFF_DIST   30.0f  // Distance of take-off  (cm)
#define D2_LANDING_DIST   10.0f  // Distance of landing (cm)
#define T1_TAKEOFF_TIME   3000   // Time confirmation exit (ms)
#define T2_LANDING_TIME   3000   // Time confirmation landing (ms)

#define TIME_DOOR_MOVE    2000   // Time of door opening/closing

#define TEMP1_PREALARM    30.0f  // Temperature threshold for pre-alarm (°C)
#define TEMP2_ALARM       40.0f  // Temperature threshold for alarm (°C)
#define T3_PREALARM_TIME  5000   // Duration of pre-alarm (ms)
#define T4_ALARM_TIME     3000   // Duration of alarm (ms)

// SERVO POSITIONS (°)
#define SERVO_DOOR_CLOSED   0
#define SERVO_DOOR_OPEN    90

#endif