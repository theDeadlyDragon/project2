// Importing necessary libraries
#include "MyServer.h"
#include "acmData.h"
#include "SensorController.h"

MyServer myServer = MyServer();
acmData myAcmData = acmData();
SensorController sensorController = SensorController();

void setup(){
  Serial.begin(115200);
  //setup and starting of the server
  myServer.setupServer();
  //setup dc motor
  myAcmData.setupacmData();
  //setup sensors
  sensorController.setupSensor();
}

void loop(){
  // sensorController.readSensor();
  // Serial.println(sensorController.ultraSoonDistance);
  // if(sensorController.ultraSoonDistance < 10){
  //   myAcmData.updateMotorSpeed(255, 255);
  // }
  // else{
  //   myAcmData.updateMotorSpeed(0, 0);
  // }
  
}