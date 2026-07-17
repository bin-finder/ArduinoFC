#pragma once
#include "Quaternoin.h"

class IMPU6050{
    public:
        virtual ~IMPU6050() = default;
        virtual void setGyroRange(int num) = 0;
        virtual void setAccelRange(int num) = 0;
        virtual void resetOrientation() = 0;
        virtual Quaternoin<float> getWorldOrientation() = 0;
        virtual void getLinearAccel(Quaternoin<float>* data) = 0;
        virtual void getRotVel(Quaternoin<float>* data) = 0;
};