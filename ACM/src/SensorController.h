#ifndef SENSORCONTROLLER
#define SENSORCONTROLLER
#include <Arduino.h>

    //state variables 
    extern bool irStateLeft;
    extern bool irStateRight; 
    extern bool irStateFront;
    extern int irLastSeen;

    extern int ultraSoonDistance;
    extern int ultraSoonDistanceLeft;
    extern int ultraSoonDistanceRight;

    extern bool ldrState;

    extern bool reedState;

    extern int arraySize;
    extern int lastIrSeen[20];
    extern int irIndex;

class SensorController {
  public:
    //initialise pins
    const int irLeft = 16;
    const int irRight = 17;
    const int irFront = 4;

    const int ultraSoonFrontTrig = 2;
    const int ultraSoonFrontEcho = 15;

    const int ultraSoonLeftTrig = 26;
    const int ultraSoonLeftEcho = 27;

    const int ultraSoonRightTrig = 12;
    const int ultraSoonRightEcho = 14;

    const int ldr = 13;

    long duration = 0;

    const int reed = 25;

  SensorController();
  void setupSensor();
  void readSensor();
};

extern SensorController sensorController;
#endif