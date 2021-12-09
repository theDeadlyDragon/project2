#ifndef ACMDATA
#define ACMDATA
#include <Arduino.h>

class acmData {
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

  acmData();
  void setupacmData();
  void updateMotorSpeed(int lPwm, int rPWM);
};
#endif