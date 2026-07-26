#pragma once
#include "IServoMotor.h"
#include "OTWmath.h"

class Elevators{
    public:
        IServoMotor* servo;
        int numServos;

        Elevators(IServoMotor* servo, int numServos);

        void write(double percent);

        void start();
};