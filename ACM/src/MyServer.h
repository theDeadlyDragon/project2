#ifndef MYSERVER
#define MYSERVER
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

class MyServer {
  public:
    // Setting network credentials
    const char* ssid = "Free Wifi 2.4GHz";
    const char* password = "0615100678";

    // AsyncWebServer server(80);

  MyServer();
  void setupServer();
};
#endif