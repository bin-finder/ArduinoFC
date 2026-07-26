#pragma once
#include "Ailerons.h"
#include "Rudder.h"
#include "Elevators.h"
#include "IAirplane.h"
#include "OTWmath.h"
#include "Throttle.h"

class standard : public IAirplane{
    public:
        Ailerons* ailerons;
        Elevators* elevators;
        Rudder* rudder;
        Throttle* throttle;

        standard(Ailerons* ailerons, Elevators* elevators, Rudder* rudder, Throttle* throttle) :
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
            rudder->write(percent);
        }

        void setThrottlePercent(double percent){
            throttle->write(percent);
        }
};