#ifndef MYSERVER
#define MYSERVER
#include <WiFi.h>
#include <PubSubClient.h>
// #include <AsyncTCP.h>
// #include <ESPAsyncWebServer.h>
// #include <SPIFFS.h>
#include "main.h"

extern PubSubClient client;
void reconnect();

class MyServer {
  public:
    // Setting network credentials
    const char* ssid = "Tesla IoT";
    const char* password = "fsL6HgjN";

    const char* mqtt_server = "broker.mqttdashboard.com";

  MyServer();
  void setupServer();
};

extern MyServer myServer;
#endif