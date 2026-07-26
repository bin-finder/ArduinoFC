#include "Elevons.h"

Elevons::Elevons(ServoMotor* servosLeft, ServoMotor* servosRight, int numLeft, int numRight)
:servosLeft(servosLeft), servosRight(servosRight), numLeft(numLeft), numRight(numRight)
{}

/**
 * Doc comment
 */

void Elevons::write(double percentPitch, double percentRoll){
	int travel = servosLeft[0].getRange(); //TODO get max travel from servos themselves
	for(int i = 0; i < numLeft; i++){
		servosLeft[i].write(travel/2*(percentPitch + -1 * percentRoll));
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
