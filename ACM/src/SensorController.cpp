#include "SensorController.h"

//initial values
bool irStateLeft = false;
bool irStateRight = false;
bool irStateFront = false;
//0 -> left, 1 -> right
int irLastSeen = 0;
int ultraSoonDistance = 20;
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
    irStateFront = digitalRead(irFront);

    // //ultrasoon
    // digitalWrite(ultraSoonFrontTrig, HIGH);
    // delayMicroseconds(10);
    // digitalWrite(ultraSoonFrontTrig, LOW);

    // duration = pulseIn(ultraSoonFrontEcho, HIGH);
    // ultraSoonDistance = duration * 0.0343 / 2; //0.0343 speed of sound 

    //reed
    reedState = digitalRead(reed);
}
