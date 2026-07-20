#pragma once
#include <ServoMotor.h>
#include "IElevons.h"

class Elevons : public IElevons{
	public:
		ServoMotor* servosLeft;
		ServoMotor* servosRight;
		int numLeft;
		int numRight;
	public:
		Elevons(ServoMotor* servosLeft, ServoMotor* servosRight, int numLeft, int numRight);

		void write(double percentPitch, double percentRoll);

		void start();
};
