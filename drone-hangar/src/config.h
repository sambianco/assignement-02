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
#define D1_TAKEOFF_DIST   30.0f  // Distanza uscita drone (cm)
#define D2_LANDING_DIST   10.0f  // Distanza drone a terra (cm)
#define T1_TAKEOFF_TIME   3000   // Tempo conferma uscita (ms)
#define T2_LANDING_TIME   3000   // Tempo conferma atterraggio (ms)

#define TEMP1_PREALARM    30.0f  // Soglia pre-allarme (°C)
#define TEMP2_ALARM       40.0f  // Soglia allarme bloccante (°C)
#define T3_PREALARM_TIME  5000   // Durata per pre-allarme (ms)
#define T4_ALARM_TIME     3000   // Durata per allarme (ms)

// SERVO POSITIONS (°)
#define SERVO_DOOR_CLOSED   0
#define SERVO_DOOR_OPEN    90

#endif