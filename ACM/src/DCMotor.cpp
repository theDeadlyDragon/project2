#include "DCMotor.h"

DCMotor::DCMotor() {

}

void DCMotor::setupDCMotor(){
    pinMode(mLForwardPin,OUTPUT);
    pinMode(mRForwardPin,OUTPUT);
    pinMode(mLBackwardPin,OUTPUT);
    pinMode(mRBackwardPin,OUTPUT);
    ledcSetup(0,freq,8);
    ledcSetup(1,freq,8);
    ledcSetup(2,freq,8);
    ledcSetup(3,freq,8);
    ledcAttachPin(mLForwardPin,0);
    ledcAttachPin(mRForwardPin,1);
    ledcAttachPin(mLBackwardPin,2);
    ledcAttachPin(mRBackwardPin,3);
}

void DCMotor::updateMotorSpeed(int lPwm, int rPWM){
    Serial.printf("updated with %d and %d \n", lPwm,rPWM);
    motorLPWM = lPwm;
    motorRPWM = rPWM;

    if(motorLPWM > 0){
      ledcWrite(0,motorLPWM);
      ledcWrite(2,0);
    }else if (motorLPWM < 0)
    {
      ledcWrite(2,-motorLPWM);
      ledcWrite(0,0);
    }
    else{
      ledcWrite(0,0);
      ledcWrite(2,0);
    }

    if(motorRPWM > 0){
      ledcWrite(1,motorRPWM);
      ledcWrite(3,0);
    }else if (motorRPWM < 0)
    {
      ledcWrite(3,-motorRPWM);
      ledcWrite(1,0);
    }
    else{
      ledcWrite(1,0);
      ledcWrite(3,0);
    }
}

void DCMotor::autoPilot(){
  Serial.println(ultraSoonDistance);
    if(ultraSoonDistance < 15){
        myDCMotor.updateMotorSpeed(0, 0);
    }
    else if(!(irStateLeft || irStateRight)){
      myDCMotor.updateMotorSpeed(250, 180);
    }
    else if(irStateLeft && irStateRight){
      if(irLastSeen == 1){
        myDCMotor.updateMotorSpeed(200, -200);
        vTaskDelay(1500 / portTICK_RATE_MS);
      }
    else if(irLastSeen == 2){    
        myDCMotor.updateMotorSpeed(-200, 200);
        vTaskDelay(1500 / portTICK_RATE_MS);
      }
    }
    else if(irStateLeft && !irStateRight){
      irLastSeen = 1;
      myDCMotor.updateMotorSpeed(230, -150);
    }
    else if(irStateRight && !irStateLeft){
      irLastSeen = 2;
      myDCMotor.updateMotorSpeed(-150, 230);
    }
}

void DCMotor::objAvoid(){

}