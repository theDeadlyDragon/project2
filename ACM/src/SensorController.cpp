#include "SensorController.h"

//initial values
bool irStateLeft = false;
bool irStateRight = false;
bool irStateFront = false;
//0 -> left, 1 -> right
int irLastSeen = 0;
long irLastSeenTime = 0;
int ultraSoonDistance = 20;
int ultraSoonDistanceLeft = 20;
int ultraSoonDistanceRight = 20;
bool ldrState = false;
bool reedState = false;
float speedOfSound = 0.0343;

SensorController::SensorController() {

}

void SensorController::setupSensor(){
    pinMode(irLeft, INPUT);
    pinMode(irRight, INPUT);
    pinMode(irFront, INPUT);
    pinMode(ultraSoonFrontTrig, OUTPUT);
    pinMode(ultraSoonLeftTrig, OUTPUT);
    pinMode(ultraSoonRightTrig, OUTPUT);
    //clear trig pin
    digitalWrite(ultraSoonFrontTrig, LOW);
    digitalWrite(ultraSoonLeftTrig, LOW);
    digitalWrite(ultraSoonRightTrig, LOW);
    pinMode(ultraSoonFrontEcho, INPUT);
    pinMode(ultraSoonLeftEcho, INPUT);
    pinMode(ultraSoonRightEcho, INPUT);
    pinMode(reed, INPUT);
}

void SensorController::readSensor(){
    //read ir sensor
    irStateLeft = digitalRead(irLeft);
    irStateRight = digitalRead(irRight);
    irStateFront = digitalRead(irFront);

    //ultrasoon front
    digitalWrite(ultraSoonFrontTrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(ultraSoonFrontTrig, LOW);

    duration = pulseIn(ultraSoonFrontEcho, HIGH);
    ultraSoonDistance = duration * speedOfSound / 2; //2: back and forth

    //ultrasoon left
    digitalWrite(ultraSoonLeftTrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(ultraSoonLeftTrig, LOW);
    
    duration = pulseIn(ultraSoonLeftEcho, HIGH);
    ultraSoonDistanceLeft = duration * speedOfSound / 2; //2: back and forth

    //ultrasoon right
    digitalWrite(ultraSoonRightTrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(ultraSoonRightTrig, LOW);

    duration = pulseIn(ultraSoonRightEcho, HIGH);
    ultraSoonDistanceRight = duration * speedOfSound / 2; //2: back and forth

    //ldr
    ldrState = digitalRead(ldr);

    //reed
    reedState = digitalRead(reed);
}
