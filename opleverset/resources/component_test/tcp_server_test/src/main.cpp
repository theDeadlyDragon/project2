/*
 WiFi Web Server LED Blink

 A simple web server that lets you blink an LED via the web.
 This sketch will print the IP address of your WiFi Shield (once connected)
 to the Serial monitor. From there, you can open that address in a web browser
 to turn on and off the LED on pin 5.

 If the IP address of your shield is yourAddress:
 http://yourAddress/H turns the LED on
 http://yourAddress/L turns it off

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.

 Circuit:
 * WiFi shield attached
 * LED attached to pin 5

 created for arduino 25 Nov 2012
 by Tom Igoe

ported for sparkfun esp32 
31.01.2017 by Jan Hendrik Berlin
 
 */

#include <WiFi.h>



const char* ssid     = "**********";
const char* password = "bxjght+$t\"bmV7[&";

#include "Arduino.h"
#define SendKey 0  //Button to send data Flash BTN on NodeMCU

int port = 8888;  //Port number
WiFiServer server(port);
int pinSetup[40];

int count=0;
//=======================================================================
//                    Power on setup
//=======================================================================
void setup() 
{
  
  Serial.begin(115200);
  pinMode(SendKey,INPUT_PULLUP);  //Btn to send data
  Serial.println();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); //Connect to wifi
 
  // Wait for connection  
  Serial.println("Connecting to Wifi");
  while (WiFi.status() != WL_CONNECTED) {   
    delay(500);
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  
  server.begin();
  Serial.print("Open Telnet and connect to IP:");
  Serial.print(WiFi.localIP());
  Serial.print(" on port ");
  Serial.println(port);

  pinSetup[0] = 15;
  pinSetup[1] = 2;

  ledcAttachPin(15,0);
  ledcAttachPin(2,0);
  ledcSetup(0,5000,8);
  ledcWrite(0,255);

}
//=======================================================================
//                    Loop
//=======================================================================

void readPins(){
  
      Serial.println(ledcRead(2),HEX);

}

void loop() 
{
  WiFiClient client = server.available();
  

  if (client) {
    if(client.connected())
    {
      Serial.println("Client Connected");
    }
    
    
  int c[256];
    while(client.connected()){     
      int i = 0; 
      while(client.available()>0){
        // read data from the connected client
       c[i] = client.read();
        Serial.println(c[i],HEX); 
        Serial.println(i);
        i++;
        if(Serial.available()==0 )
        {
          readPins();
        client.write("ok");
        Serial.println("send data1");   
        }
      }
     
      //Send Data to connected client
      
    }
    client.stop();
    Serial.println("Client disconnected");    
    delay(1000);
  }
  
}
//=======================================================================d