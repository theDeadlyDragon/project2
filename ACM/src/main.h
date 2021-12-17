// Importing necessary libraries
#include "MyServer.h"
#include "DCMotor.h"
#include "SensorController.h"

//define states
#define IDLE 0
#define AUTOPILOT 1
#define OBJAVOID 2
#define TUNNEL 3

extern int state;