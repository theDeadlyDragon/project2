#ifndef SENSORCONTROLLER
#define SENSORCONTROLLER
#include "Arduino.h"

class SensorController {
  public:
    //initialise pins
    int irLeft = 16;
    int irRight = 17;

    int ultraSoonFrontTrig = 4;
    int ultraSoonFrontEcho = 15;

    int reed = 12;

    //state variables 
    bool irStateLeft = false;
    bool irStateRight = false; 

    int ultraSoonDistance = 0;

    bool reedState = false;


  SensorController();
  void setupSensorController();
  void readSensor();
};
#endif