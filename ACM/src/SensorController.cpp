#include "SensorController.h"

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
    if(!digitalRead(irLeft)){
        irStateLeft = true;
    }
    else{
        irStateLeft = false;
    }

    if(!digitalRead(irRight)){
        irStateRight = true;
    }
    else{
        irStateRight = false;
    }

    //ultrasoon
    digitalWrite(ultraSoonFrontTrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(ultraSoonFrontTrig, LOW);

    duration = pulseIn(ultraSoonFrontEcho, HIGH);
    ultraSoonDistance = duration * 0.0343 / 2; //0.0343 speed of sound 

    //reed
    reedState = digitalRead(reed);
}
