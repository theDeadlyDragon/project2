#include "main.h"
#include "MyServer.h"

MyServer::MyServer() {

}

AsyncWebServer server(80);

IPAddress local_IP(192,168,0,1);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);

void MyServer::setupServer() {

    if(!SPIFFS.begin()){
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    WiFi.softAPConfig(local_IP, gateway, subnet);
    WiFi.softAP(ssid, password);

    // Print ESP Local IP Address
    Serial.println(WiFi.localIP());

    // Route for root / web page files: html, css, js
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        if(state == MANUAL){
            state = IDLE;
        }
        request->send(SPIFFS, "/index.html", "text/html");
    });

    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/style.css", "text/css");
    });

    server.on("/bootstrap.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/bootstrap.css", "text/css");
    });

    server.on("/scripts.js", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/scripts.js", "text/javascript");
    });

    server.on("/bootstrap.js", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/bootstrap.js", "text/javascript");
    });

    server.on("/popper.js", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/popper.js", "text/javascript");
    });

    server.on("/jquery.js", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/jquery.js", "text/javascript");
    });

    server.on("/control.html", HTTP_GET, [](AsyncWebServerRequest *request){
        state = MANUAL;
        request->send(SPIFFS, "/control.html", "text/html");
    });

    // Send a POST request to <ESP_IP>/... for motor control
    server.on("/left", HTTP_POST, [] (AsyncWebServerRequest *request) {
        myDCMotor.updateMotorSpeed(-250, 250);
    });
    server.on("/right", HTTP_POST, [] (AsyncWebServerRequest *request) {
        myDCMotor.updateMotorSpeed(250, -250);
    });
    server.on("/go", HTTP_POST, [] (AsyncWebServerRequest *request) {
        myDCMotor.updateMotorSpeed(250, 250);
    });
    server.on("/back", HTTP_POST, [] (AsyncWebServerRequest *request) {
        myDCMotor.updateMotorSpeed(-250, -250);
    });
    server.on("/stopM", HTTP_POST, [] (AsyncWebServerRequest *request) {
        myDCMotor.updateMotorSpeed(0, 0);
    });

    //GET request for monitor and state
    server.on("/state", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/plain", state.c_str());
    });

    server.on("/start", HTTP_GET, [](AsyncWebServerRequest *request){
        state = AUTOPILOT;
    });

    server.on("/stop", HTTP_GET, [](AsyncWebServerRequest *request){
        state = IDLE;
    });

    // Start server
    server.begin();
}