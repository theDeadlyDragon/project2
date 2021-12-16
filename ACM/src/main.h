// Importing necessary libraries
//#include "MyServer.h"
#include "DCMotor.h"
#include "SensorController.h"

//define states
#define IDLE 0
#define MANUAL 1
#define AUTOPILOT 2
#define OBJAVOID 3

//extern MyServer myServer;
extern DCMotor myDCMotor;
extern SensorController sensorController;

extern int state;