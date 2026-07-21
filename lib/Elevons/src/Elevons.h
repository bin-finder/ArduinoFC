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

		/**
		 * Writes the percentage of the range of the servoMotor
		 * to the respective servos.
		 * @param percentPitch The pitch, in percent of range
		 * @param percentRoll The roll, I hope you got that its a percentatge by now
		 */

		void write(double percentPitch, double percentRoll); 

		void start();
};
