#pragma once
#include "Elevons.h"
#include "RCreciever.h"
#include "config.h"
#include "IflightMode.h"
#include <Arduino.h>

class manualControl : public IflightMode{
    private:
        Elevons* elevons = nullptr;
        RCreciever* controlIn = nullptr;
    public:
        manualControl(Elevons* elevons, RCreciever* controlIn) : 
        elevons(elevons), 
        controlIn(controlIn)
        {}

        int update(unsigned int dt){
            digitalWrite(13, LOW);
            float value[numChannels];
            controlIn->getLatest(value);
            airplane->setPitchPercent(value[chanElevator]);
            airplane->setRollPercent(value[chanAileron]);
            airplane->setYawPercent(value[chanRudder]);
            airplane->setThrottlePercent(value[chanThrottle]);
            return 1;
        }

        void reset(){}
};