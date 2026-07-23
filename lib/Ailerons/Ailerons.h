#pragma once
#include "IServoMotor.h"
#include "OTWmath.h"

class Ailerons{
    public:
        IServoMotor* servoLeft;
        IServoMotor* servoRight;

        Ailerons(IServoMotor* servoLeft, IServoMotor* servoRight);

        void write(double percent);

        void start();
};