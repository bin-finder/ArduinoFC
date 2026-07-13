#include "Rudder.h"

Rudder::Rudder(IServoMotor* motors, int numberOfMotors)
  :servos(motors), number(numberOfMotors)
{
  for(int i = 0; i < numberOfMotors; i++){
    servos[i].start();
  }
}

void Rudder::start(){
  for(int i = 0; i < number; i++){
    servos[i].start();
  }
}

void Rudder::write(double percentage){
  int travel = 180; //TODO get max travel from servos themselves
  for(int i = 0; i < number; i++){
    servos[i].write(travel/2*percentage);
  }
}