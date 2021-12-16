#include "SensorController.h"

//initial values
bool irStateLeft = false;
bool irStateRight = false;
int irLastSeen = 0;
int ultraSoonDistance = 0;
bool reedState = false;

SensorController::SensorController() {

}

void SensorController::setupSensor(){
    pinMode(irLeft, INPUT);
    pinMode(irRight, INPUT);
    pinMode(ultraSoonFrontTrig, OUTPUT);
    //clear trig pin
    digitalWrite(ultraSoonFrontTrig, LOW);
    pinMode(ultraSoonFrontEcho, INPUT);
    pinMode(reed, INPUT);
}

void SensorController::readSensor(){
    //read ir sensor
    irStateLeft = digitalRead(irLeft);
    irStateRight = digitalRead(irRight);

    //ultrasoon
    digitalWrite(ultraSoonFrontTrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(ultraSoonFrontTrig, LOW);

    duration = pulseIn(ultraSoonFrontEcho, HIGH);
    ultraSoonDistance = duration * 0.0343 / 2; //0.0343 speed of sound 

    //reed
    reedState = digitalRead(reed);
}
