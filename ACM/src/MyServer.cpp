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

    server.on("/monitor.js", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/monitor.js", "text/javascript");
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

    server.on("/monitor.html", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/monitor.html", "text/html");
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
    server.on("/stop", HTTP_POST, [] (AsyncWebServerRequest *request) {
        myDCMotor.updateMotorSpeed(0, 0);
    });

    //GET request for monitor
    server.on("/state", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/plain", String(state).c_str());
    });

    server.on("/startStop", HTTP_GET, [](AsyncWebServerRequest *request){
        if(state == IDLE){
            state = AUTOPILOT;
            Serial.println("changed state to AUTOPILOT");
        }
        else{
            state = IDLE;
            Serial.println("changed state to IDLE");
        }
    });

    server.on("/sensor", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", "Ok");
    response->addHeader("state", String(state).c_str());
    response->addHeader("irLeft", String(irStateLeft).c_str());
    response->addHeader("irRight", String(irStateRight).c_str());
    response->addHeader("ultrasoon", String(ultraSoonDistance).c_str());
    response->addHeader("reed", String(reedState).c_str());
    request->send(response);
    });

    // Start server
    server.begin();
}