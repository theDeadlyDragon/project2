// Importing necessary libraries
#include "MyServer.h"

MyServer myServer = MyServer();

void setup(){
  Serial.begin(115200);
  //setup and starting of the server
  myServer.setupServer();
 
}

void loop(){
}