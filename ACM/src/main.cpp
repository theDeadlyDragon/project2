#include "main.h"

//MyServer myServer = MyServer();
DCMotor myDCMotor = DCMotor();
SensorController sensorController = SensorController();

int state;

void setup(){
  Serial.begin(115200);
  //setup and starting of the server
  //myServer.setupServer();
  //setup dc motor
  myDCMotor.setupDCMotor();
  //setup sensors
  sensorController.setupSensor();
  //initial state
  state = AUTOPILOT;
  Serial.println("setup complete");
}

void loop(){
  sensorController.readSensor();
  if(state == AUTOPILOT){
    Serial.println("loop");
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
  else if(state == OBJAVOID){
    myDCMotor.objAvoid();
  }
}