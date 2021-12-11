#include "main.h"

MyServer myServer = MyServer();
DCMotor myDCMotor = DCMotor();
SensorController sensorController = SensorController();

int state;

void setup(){
  Serial.begin(115200);
  //setup and starting of the server
  myServer.setupServer();
  //setup dc motor
  myDCMotor.setupDCMotor();
  //setup sensors
  sensorController.setupSensor();
  //initial state
  state = IDLE;
  Serial.println("setup complete");
}

void loop(){
  sensorController.readSensor();

  if(state == AUTOPILOT){

  }
  else if(state == OBJAVOID){

  }
  else{

  }  
}