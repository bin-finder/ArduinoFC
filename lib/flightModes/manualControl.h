#pragma once
#include "IAirplane.h"
#include "IRCreciever.h"
#include "config.h"
#include "IflightMode.h"
#include <Arduino.h>

class manualControl : public IflightMode{
    private:
        IAirplane* airplane = nullptr;
        IRCreciever* controlIn = nullptr;
    public:
        manualControl(IAirplane* airplane, IRCreciever* controlIn) : 
        airplane(airplane), 
        controlIn(controlIn)
        {}

        int update(double dt){
            //digitalWrite(13, LOW);
            float value[numChannels];
            controlIn->getLatest(value);
            airplane->setPitchPercent(-value[chanElevator]);
            airplane->setRollPercent(value[chanAileron]);
            airplane->setYawPercent(value[chanRudder]);
            airplane->setThrottlePercent(value[chanThrottle]);
            return 1;
        }

        void reset(){}
};