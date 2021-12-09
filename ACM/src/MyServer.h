#ifndef MYSERVER
#define MYSERVER
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include "acmData.h"

class MyServer {
  public:
    // Setting network credentials
    const char* ssid = "MiPhone";
    const char* password = "2bde27176";

    // AsyncWebServer server(80);

  MyServer();
  void setupServer();
};
#endif