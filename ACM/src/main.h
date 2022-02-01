// Importing necessary libraries
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "MyServer.h"
#include "DCMotor.h"
#include "SensorController.h"
#include<iostream>

//define states
#define IDLE 0
#define AUTOPILOT 1
//#define OBJAVOID 2
#define TUNNEL 2
#define MANUAL 3

//define screen size
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

//display address
#define I2C_DISPLAY_ADDRESS 0x3C

//time intervals
#define MQTT_INTERVAL 1000
#define DISPLAY_INTERVAL 3000
#define TIMER_INTERVAL 5000

extern int state;
extern long startTimer;
extern long timeCompleted;

void setupDisplay();
void setDisplay(String output);