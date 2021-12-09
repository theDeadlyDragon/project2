// Importing necessary libraries
#include "MyServer.h"
#include "acmData.h"

MyServer myServer = MyServer();
acmData myAcmData = acmData();

void setup(){
  Serial.begin(115200);
  //setup and starting of the server
  myServer.setupServer();
  //setup dc motor
  myAcmData.setupacmData();
 
}

void loop(){
}