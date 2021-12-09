#include "MyServer.h"

MyServer::MyServer() {

}

AsyncWebServer server(80);
acmData motor = acmData();

void MyServer::setupServer() {

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

    server.on("/control.html", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/control.html", "text/html");
    });

    // Send a POST request to <ESP_IP>/...
    server.on("/left", HTTP_POST, [] (AsyncWebServerRequest *request) {
        motor.updateMotorSpeed(-250, 250);
    });
    server.on("/right", HTTP_POST, [] (AsyncWebServerRequest *request) {
        motor.updateMotorSpeed(250, -250);
    });
    server.on("/go", HTTP_POST, [] (AsyncWebServerRequest *request) {
        motor.updateMotorSpeed(250, 250);
    });
    server.on("/back", HTTP_POST, [] (AsyncWebServerRequest *request) {
        motor.updateMotorSpeed(-250, -250);
    });
    server.on("/stop", HTTP_POST, [] (AsyncWebServerRequest *request) {
        motor.updateMotorSpeed(0, 0);
    });

    // Start server
    server.begin();
}