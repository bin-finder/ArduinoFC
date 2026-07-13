#pragma once
#include "IElevons.h"
#include "IMPU6050.h"
#include "IPPMReader.h"

class manualControl{
    private:
        IElevons* elevons = nullptr;
        IMPU6050* sense = nullptr;
        IPPMReader* controlIn = nullptr;
    public:
        manualControl(IElevons* elevons, IMPU6050* sense, IPPMReader* controlIn) : 
        elevons(elevons), 
        sense(sense), 
        controlIn(controlIn)
        {}

        

};