#include "main.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


MyServer myServer = MyServer();
DCMotor myDCMotor = DCMotor();
SensorController sensorController = SensorController();


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);



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
  Serial.println("setup complete");

  	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
 
	// Clear the buffer.
	display.clearDisplay();
 
	// Display Text
	display.setTextSize(2);
	display.setTextColor(WHITE);
	display.setCursor(0,0);
	display.println("Brrrr BOt");
	display.display();
	delay(2000);
	display.clearDisplay();
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
    client.publish("ACM/29/client/irFront", String(irStateFront).c_str());
    client.publish("ACM/29/client/ultrasoon", String(ultraSoonDistance).c_str());
    client.publish("ACM/29/client/ultrasoonLeft", String(ultraSoonDistanceLeft).c_str());
    client.publish("ACM/29/client/ultrasoonRight", String(ultraSoonDistanceRight).c_str());
    client.publish("ACM/29/client/reed", String(reedState).c_str());
    client.publish("ACM/29/client/ldr", String(ldrState).c_str());
    client.publish("ACM/29/client/state", String(state).c_str());
    client.publish("ACM/29/client/buffer", String(state).c_str());
  }
}