#include "main.h"

MyServer myServer = MyServer();
DCMotor myDCMotor = DCMotor();
SensorController sensorController = SensorController();
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int state;
long lastMsg = 0;
long lastDspChange = 0;

String name = "Brrrr Bot";
String displayState[] = {"IDLE","AUTOPILOT","TUNNEL"};
String currentDisplay = "";

void setup(){
  Serial.begin(115200);
  //setup and starting of the server
  myServer.setupServer();
  //setup display
  setupDisplay();
  //setup dc motor
  myDCMotor.setupDCMotor();
  //setup sensors
  sensorController.setupSensor();
  //initial state
  state = IDLE;
  Serial.println("setup complete");
}

void loop(){
  long now = millis();
  //check mqtt broker connection
  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  //update all sensors
  sensorController.readSensor();

  
  if(state == AUTOPILOT){
    myDCMotor.autoPilot();
  }
  else if(state == TUNNEL){
    myDCMotor.tunnel();
  }

  //send sensor data to mqtt broker every 1000 mili seconds
  if (now - lastMsg > MQTT_INTERVAL) {
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

  if(now - lastDspChange > DISPLAY_INTERVAL){
    lastDspChange = now;
    if(state != MANUAL){
      if(currentDisplay == name){
          setDisplay(displayState[state]);
          currentDisplay = displayState[state];
      }
      else{
          setDisplay(name);
          currentDisplay = name;
      }
    }
  }
}
/*setup code for display*/
void setupDisplay(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
	display.clearDisplay();
}
/*set text on display*/
void setDisplay(String output){
  display.clearDisplay();
  display.setTextSize(2);
	display.setTextColor(WHITE);
	display.setCursor(0,17);
	display.println(output);
	display.display();
}