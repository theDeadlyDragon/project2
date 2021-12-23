#include "main.h"

MyServer myServer = MyServer();
DCMotor myDCMotor = DCMotor();
SensorController sensorController = SensorController();

int state;
long lastMsg = 0;

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
  memset(lastIrSeen, 0, 20);
  Serial.println("setup complete");
}

void loop(){
  long now = millis();
  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  sensorController.readSensor();
  if(state == AUTOPILOT){
    myDCMotor.autoPilot();
  }
  else if(state == OBJAVOID){
    myDCMotor.objAvoid();
  }

  if (now - lastMsg > 1000) {
    lastMsg = now;
    
    client.publish("ACM/29/client/irLeft", String(irStateLeft).c_str());
    client.publish("ACM/29/client/irRight", String(irStateRight).c_str());
    client.publish("ACM/29/client/ultrasoon", String(ultraSoonDistance).c_str());
    client.publish("ACM/29/client/reed", String(reedState).c_str());
    client.publish("ACM/29/client/state", String(state).c_str());
    client.publish("ACM/29/client/buffer", String(state).c_str());
  }
}