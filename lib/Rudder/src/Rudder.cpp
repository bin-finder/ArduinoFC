#include "Rudder.h"

Rudder::Rudder(IServoMotor* motors, int numberOfMotors)
  :servos(motors), number(numberOfMotors)
{}

void Rudder::start(){
  for(int i = 0; i < number; i++){
    servos[i].start();
  }
}

void Rudder::write(double percentage){
  for(int i = 0; i < number; i++){
    servos[i].write(fmap(percentage, -1,1,-servos[i].getRange()/2, servos[i].getRange())/2);
  }
}