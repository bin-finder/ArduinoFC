#pragma once
#include "Elevons.h"
#include "IAirplane.h"

class flyingWing : public IAirplane{
    private:
        Elevons* elevons;
        double percentPitch = 0;
        double percentRoll = 0;

    public:
        flyingWing(Elevons* elevons) : elevons(elevons) {}

        void setPitchPercent(double percent){
            percentPitch = percent;
            elevons->write(percentPitch, percentRoll);
        }

        void setRollPercent(double percent){
            percentRoll = percent;
            elevons->write(percentPitch, percentRoll);
        }

        void setYawPercent(double percent){
            ;
        }
};