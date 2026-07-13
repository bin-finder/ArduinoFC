#pragma once
#include "IServoMotor.h"
#include "IElevons.h"

class Elevons : public IElevons{
	private:
		IServoMotor* servosLeft;
		IServoMotor* servosRight;
		int numLeft;
		int numRight;
	public:
		Elevons(IServoMotor* servosLeft, IServoMotor* servosRight, int numLeft, int numRight);

		void write(double percentPitch, double percentRoll) override;

		void start() override;
};
