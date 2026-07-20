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

        int update(){
            float value[numChannels];
            controlIn->getLatest(value);
            // for(int i = 0; i < numChannels; i++){
            //     scaled[i] = map(value[i], 1000,2000,-1,1);
            // }
            elevons->write(value[0],value[1]);
            //elevons->servosLeft->write(fmap(value[0], -1,1,-90,90));
            return 1;
        }

        void reset(){}
};