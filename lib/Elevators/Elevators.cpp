#include "Elevators.h"

Elevators::Elevators(IServoMotor* servo, int numServos) :
    servo(servo),
    numServos(numServos)
    {}

void Elevators::write(double percent){
    for(int i = 0; i < numServos; i++){
        servo[i].write(fmap(percent, -1, 1, -servo[i].getRange()/2, servo[i].getRange()/2));
    }
}

void Elevators::start(){
    for(int i = 0; i < numServos; i++){
        servo[i].start();
    }
}