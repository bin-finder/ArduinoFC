#include "Ailerons.h"

Ailerons::Ailerons(IServoMotor* servoLeft, IServoMotor* servoRight) :
    servoLeft(servoLeft),
    servoRight(servoRight)
    {}

void Ailerons::write(double percent){
    int angle = fmap(percent, -1,1,-servoLeft->getRange()/2,servoLeft->getRange()/2);
    servoLeft->write(angle);
    servoRight->write(angle);
}

void Ailerons::start(){
    servoLeft->start();
    servoRight->start();
}