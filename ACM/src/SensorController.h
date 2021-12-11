#ifndef SENSORCONTROLLER
#define SENSORCONTROLLER
#include "Arduino.h"

    //state variables 
    extern bool irStateLeft;
    extern bool irStateRight; 

    extern int ultraSoonDistance;

    extern bool reedState;

class SensorController {
  public:
    //initialise pins
    const int irLeft = 16;
    const int irRight = 17;

    const int ultraSoonFrontTrig = 4;
    const int ultraSoonFrontEcho = 15;
    long duration = 0;

    const int reed = 12;

  SensorController();
  void setupSensor();
  void readSensor();
};
#endif