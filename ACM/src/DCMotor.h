#ifndef DCMOTOR
#define DCMOTOR
#include <Arduino.h>
#include "main.h"

class DCMotor {
  public:
    int mLForwardPin = 21;
    int mRForwardPin = 18;
    int mLBackwardPin = 19;
    int mRBackwardPin = 5;
    int freq = 5000;

    int ir=0;
    
    int mRPin = 0;
    int motorLPWM;
    int motorRPWM;

  DCMotor();
  void setupDCMotor();
  void updateMotorSpeed(int lPwm, int rPWM);
  void autoPilot();
  void objAvoid();
};

extern DCMotor myDCMotor;
#endif