#include "Elevators.h"

Elevators::Elevators(IServoMotor* servo, int numServos) :
    servo(servo),
    numServos(numServos)
    {}

void Elevators::write(double percent){
    for(int i = 0; i < numServos; i++){
        servo[i].write(percent);
    }
}

void Elevators::start(){
    for(int i = 0; i < numServos; i++){
        servo[i].start();
    }
}