#include "DCMotor.h"

long lastRecord = 0;
int objLast = 0;

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
  
    if(ultraSoonDistance < 15){
      if(irLastSeen == 0 && (millis() - irLastSeenTime < 3000)){
        myDCMotor.updateMotorSpeed(-250, 250);
      }
      else if(irLastSeen == 1 && (millis() - irLastSeenTime < 3000)){
        myDCMotor.updateMotorSpeed(250, -250);
      }
      vTaskDelay(600);
    }
    else if(!(irStateLeft || irStateRight || irStateFront)){
      if(irLastSeen == 0 && (millis() - irLastSeenTime > 3000))
        myDCMotor.updateMotorSpeed(230 , 230);
      else if(irLastSeen == 1 && (millis() - irLastSeenTime > 3000))
        myDCMotor.updateMotorSpeed(210 , 250);
      else 
        myDCMotor.updateMotorSpeed(230 , 250);
    }
    else if(irStateLeft && irStateRight && !irStateFront){
      myDCMotor.updateMotorSpeed(-250,-250);
      vTaskDelay(280);
    }
    else if(irStateLeft && irStateFront && !irStateRight){
      irLastSeen = 0;
      myDCMotor.updateMotorSpeed(-250,250);
      
    }
    else if(irStateRight && irStateFront && !irStateLeft){
      irLastSeen = 1;
      myDCMotor.updateMotorSpeed(250,-250);
    }
    else if(irStateFront){
      Serial.println(millis() - irLastSeenTime);
      // myDCMotor.updateMotorSpeed(-250,-250);
      // vTaskDelay(200);
      if(irLastSeen == 0 && (millis() - irLastSeenTime < 3000)){
        myDCMotor.updateMotorSpeed(-250,250);
      }
      else if(irLastSeen == 1 && (millis() - irLastSeenTime < 3000)){
        myDCMotor.updateMotorSpeed(250,-250);
      }
      else{
        if(irLastSeen == 0){
          myDCMotor.updateMotorSpeed(250,-250);
        }
        else{
          myDCMotor.updateMotorSpeed(-250,250);
        }
        vTaskDelay(1000);
      }
      irLastSeenTime = millis();
      vTaskDelay(200);
    }
    else if(irStateLeft){
      irLastSeen = 0;
      irLastSeenTime = millis();
      myDCMotor.updateMotorSpeed(-250,250);
    }
    else if(irStateRight){
      irLastSeen = 1;
      irLastSeenTime = millis();
      myDCMotor.updateMotorSpeed(250,-250);
    }
}

void DCMotor::objAvoid(){
}

void DCMotor::tunnel(){
  Serial.println(ultraSoonDistanceLeft);
  Serial.println(ultraSoonDistanceRight);

  if(ultraSoonDistanceLeft < 8){
    updateMotorSpeed(0, 250);
  }
  else if(ultraSoonDistanceRight < 8){
    updateMotorSpeed(250, 180);
  }
  else{
    updateMotorSpeed(230, 250);
  }
}