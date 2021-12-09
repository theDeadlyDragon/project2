#ifndef MYSERVER
#define MYSERVER
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include "DCMotor.h"

class MyServer {
  public:
    // Setting network credentials
    const char* ssid = "ACM_pro1_v29";
    const char* password = "Welkom01";

  MyServer();
  void setupServer();
};
#endif