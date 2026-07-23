#pragma once
#include "Ailerons.h"
#include "Rudder.h"
#include "Elevators.h"
#include "IAirplane.h"
#include "OTWmath.h"

class standard : public IAirplane{
    public:
        Ailerons* ailerons;
        Elevators* elevators;
        Rudder* rudder;
        ServoMotor* throttle;

        standard(Ailerons* ailerons, Elevators* elevators, Rudder* rudder, ServoMotor* throttle) :
            ailerons(ailerons),
            elevators(elevators),
            rudder(rudder),
            throttle(throttle)
            {}

        void setRollPercent(double percent){
            ailerons->write(percent);
        }

        void setPitchPercent(double percent){
            elevators->write(percent);
        }

        void setYawPercent(double percent){
            ;
        }

        void setThrottle(double percent){
            throttle->write(fmap(percent, 0,1,0,180));
        }
};