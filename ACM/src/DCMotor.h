#ifndef DCMOTOR
#define DCMOTOR
#include <Arduino.h>
#include<cmath> 
#include "main.h"

class DCMotor {
  public:
  

    int mLForwardPin = 23;
    int mRForwardPin = 18;
    int mLBackwardPin = 19;
    int mRBackwardPin = 5;
    int freq = 5000;
    int brakeLights = 33;

      int forwardCount;

    int ir=0;
    
    int mRPin = 0;
    int motorLPWM;
    int motorRPWM;
    int time = 0;

  DCMotor();
  void setupDCMotor();
  void updateMotorSpeed(int lPwm, int rPWM);
  void autoPilot();
  void objAvoid();
  void tunnel();
};

extern DCMotor myDCMotor;
#endif