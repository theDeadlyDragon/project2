#include "SensorController.h"

SensorController::SensorController() {

}

void SensorController::setupSensor(){
    pinMode(irLeft, INPUT);
    pinMode(irRight, INPUT);
    pinMode(ultraSoonFrontTrig, OUTPUT);
    pinMode(ultraSoonFrontEcho, INPUT);
    pinMode(reed, INPUT);
}

void SensorController::readSensor(){
    

}
