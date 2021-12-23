#include "MyServer.h"

MyServer::MyServer() {

}

// AsyncWebServer server(80);
WiFiClient espClient;
PubSubClient client(espClient);

char msg[50];
int value = 0;

// IPAddress local_IP(192,168,0,1);
// IPAddress gateway(192,168,0,1);
// IPAddress subnet(255,255,255,0);

void callback(char* topic, byte* message, unsigned int length) {
    Serial.print("Message arrived on topic: ");
    Serial.print(topic);
    Serial.print(". Message: ");
    String messageTemp;
  
    if((char)message[0] == 's'){
        if((char)message[1] == '0'){
            state = IDLE;
            myDCMotor.updateMotorSpeed(0,0);
            Serial.println("state changed to IDLE");            
        }
        else if((char)message[1] == '1'){
            state = AUTOPILOT;
            Serial.println("state changed to AUTOPILOT");
        }
    }
    else if((char)message[0] == 'm'){
        switch ((char)message[1]){
            case 'g':
                myDCMotor.updateMotorSpeed(250,250);
                Serial.println("GO");
                break;
            case 'b':
                myDCMotor.updateMotorSpeed(-250,-250);
                Serial.println("BACK");
                break;
            case 'l':
                myDCMotor.updateMotorSpeed(-250,250);
                Serial.println("LEFT");
                break;
            case 'r':
                myDCMotor.updateMotorSpeed(250,-250);
                Serial.println("RIGHT");
                break;
            case 's':
                myDCMotor.updateMotorSpeed(0,0);
                Serial.println("STOP");
                break;
        }
    }

//   for (int i = 0; i < length; i++) {
//     Serial.print((char)message[i]);
//     messageTemp += (char)message[i];
//   }
//     Serial.println();

}

void MyServer::setupServer() {
    // connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("ACM/29/esp");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 3 seconds");
      // Wait 3 seconds before retrying
      delay(3000);
    }
  }
}