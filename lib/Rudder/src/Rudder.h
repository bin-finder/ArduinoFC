#pragma once
#include "IServoMotor.h"
#include "IRudder.h"
#include "OTWmath.h"

class Rudder : public IRudder{

  private:
    IServoMotor* servos;
    int number;

  public:
    Rudder(IServoMotor* motors, int numberOfMotors);
    void start();
    void write(double percentage);
};