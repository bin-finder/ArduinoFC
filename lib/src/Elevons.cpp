#include "Elevons.h"

Elevons::Elevons(IServoMotor* servosLeft, IServoMotor* servosRight, int numLeft, int numRight)
:servosLeft(servosLeft), servosRight(servosRight), numLeft(numLeft), numRight(numRight)
{}

void Elevons::write(double percentPitch, double percentRoll){
	int travel = 180; //TODO get max travel from servos themselves
	for(int i = 0; i < numLeft; i++){
		servosLeft[i].write( -1 * travel/2*(percentPitch + percentRoll));
	}
	for(int i = 0; i < numRight; i++){
		servosRight[i].write(travel/2*(percentPitch + percentRoll));
	}
}

void Elevons::start(){
	for(int i = 0; i < numLeft; i++){
		servosLeft[i].start();
	}

	for(int i = 0; i < numRight; i++){
		servosRight[i].start();
	}
}
