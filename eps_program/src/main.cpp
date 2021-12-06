/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// Load Wi-Fi library
#include <WiFi.h>


class acmData{
  int mLForwardPin = 21;
  int mRForwardPin = 18;
  int mLBackwardPin = 19;
  int mRBackwardPin = 5;
  int freq = 5000;

  int ir=0;
  

  
  int mRPin = 0;
  int motorLPWM;
  int motorRPWM;

public:
  void setup(){
    pinMode(mLForwardPin,OUTPUT);
    pinMode(mRForwardPin,OUTPUT);
    pinMode(mLBackwardPin,OUTPUT);
    pinMode(mRBackwardPin,OUTPUT);
    ledcSetup(0,freq,8);
    ledcSetup(1,freq,8);
    ledcSetup(2,freq,8);
    ledcSetup(3,freq,8);
    ledcAttachPin(mLForwardPin,0);
    ledcAttachPin(mRForwardPin,1);
    ledcAttachPin(mLBackwardPin,2);
    ledcAttachPin(mRBackwardPin,3);


  }

  void updateMotorSpeed(int lPwm, int rPWM){
    Serial.printf("updated with %d and %d \n", lPwm,rPWM);
    motorLPWM = lPwm;
    motorRPWM = rPWM;

    if(motorLPWM > 0){
      ledcWrite(0,motorLPWM);
      ledcWrite(2,0);
    }else if (motorLPWM < 0)
    {
      ledcWrite(2,-motorLPWM);
      ledcWrite(0,0);
    }
    else{
      ledcWrite(0,0);
      ledcWrite(2,0);
    }

    if(motorRPWM > 0){
      ledcWrite(1,motorRPWM);
      ledcWrite(3,0);
    }else if (motorRPWM < 0)
    {
      ledcWrite(3,-motorRPWM);
      ledcWrite(1,0);
    }
    else{
      ledcWrite(1,0);
      ledcWrite(3,0);
    }
  }
};


class Wireless{
  const char* _ssid     = "ESP32-Access-Point";
  const char* _password = "123456789";
  char clientMessage[256];
  int _port = 8888;
  IPAddress _IP;
  public:
  acmData *acm;
  WiFiClient client;
  boolean available = false;

public:
  Wireless(){

  }
  void setupAP(){
    WiFi.softAP(_ssid, _password);
    _IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(_IP);
    available = true;
  }
  
  
  int clientAvailble(){
    return client.available();
  }
  char *clientGetMessagge(){
    int i = 0;
     while(clientAvailble()>0){
        // read data from the connected client
        clientMessage[i] = client.read();

        switch (clientMessage[i])
        {
        case 0x57:
          Serial.println("forward");
          acm->updateMotorSpeed(client.read()*10,client.read()*10);
          break;
        case 0x58:
          Serial.println("forward");
          acm->updateMotorSpeed(client.read()*-10,client.read()*-10);
          break;
        case 0x59:
          Serial.println("forward");
          acm->updateMotorSpeed(client.read()*-10,client.read()*10);
          break;
        case 0x60:
          Serial.println("forward");
          acm->updateMotorSpeed(client.read()*10,client.read()*-10);
          break;
        
        default:
          break;
        }
        Serial.println(clientMessage[i],HEX); 
        Serial.printf("%d Serial\n",client.available());
        i++;
        if(client.available()==0 )
        {

        client.write("ok");
        Serial.println("send data1");   
        }
      }
      return clientMessage;
  }
  
};

// Replace with your network credentials





// Assign output variables to GPIO pins
const int output26 = 26;
const int output27 = 27;

  Wireless wifi;
  acmData acm;

  
  WiFiServer server(8888);

 
void setup() {
  Serial.begin(115200);
  wifi.setupAP();
  acm.setup();
  wifi.acm = &acm;
  server.begin();
acm.updateMotorSpeed(200,-100);
}

void loop(){
  wifi.client = server.available();

  
    
  

  if (wifi.client) {
    if(wifi.client.connected())
    {
      Serial.println("Client Connected");
    }
    

    while(wifi.available == true){     
        wifi.clientGetMessagge();
      
    }
    wifi.client.stop();
    Serial.println("Client disconnected");    
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
  
}
