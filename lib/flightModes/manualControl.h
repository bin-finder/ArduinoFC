#pragma once
#include "IElevons.h"
#include "RCreciever.h"
#include "config.h"
#include "IflightMode.h"

class manualControl : public IflightMode{
    private:
        IElevons* elevons = nullptr;
        RCreciever* controlIn = nullptr;
    public:
        manualControl(IElevons* elevons, RCreciever* controlIn) : 
        elevons(elevons), 
        controlIn(controlIn)
        {}

        int udpate(){
                int value[numChannels];
                controlIn->getLatest(value);
                for(int i = 0; i < numChannels; i++){
                    value[i] = value[i]/(controlIn->maxChannelValue - controlIn->minChannelValue);
                }
                elevons->write(value[1],value[2]);
        }

        void reset(){}
};