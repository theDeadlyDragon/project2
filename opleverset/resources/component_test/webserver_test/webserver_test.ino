// Importing necessary libraries
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
//#include "webPage.h"

// Setting network credentials
const char* ssid = "";
const char* password = "";

const int ledLeft = 17;
const int ledRight = 16;

AsyncWebServer server(80);

void setup(){

  Serial.begin(115200);

  pinMode(ledLeft, OUTPUT);
  digitalWrite(ledLeft, LOW);
  
  pinMode(ledRight, OUTPUT);
  digitalWrite(ledRight, LOW);

  if(!SPIFFS.begin()){
     Serial.println("An Error has occurred while mounting SPIFFS");
     return;
}

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
  });

  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });

  server.on("/scripts.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/scripts.js", "text/javascript");
  });

  // Send a POST request to <ESP_IP>/...
  server.on("/left", HTTP_POST, [] (AsyncWebServerRequest *request) {
    digitalWrite(ledLeft, HIGH);
  });
  server.on("/right", HTTP_POST, [] (AsyncWebServerRequest *request) {
    digitalWrite(ledRight, HIGH);
  });
  server.on("/stopL", HTTP_POST, [] (AsyncWebServerRequest *request) {
    digitalWrite(ledLeft, LOW);
  });
  server.on("/stopR", HTTP_POST, [] (AsyncWebServerRequest *request) {
    digitalWrite(ledRight, LOW);
  });

  // Start server
  server.begin();
}

void loop(){
}
