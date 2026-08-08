#pragma once
#include "Quaternoin.h"

class IMPU6050{
    public:
        virtual ~IMPU6050() = default;
        virtual int begin() = 0;
        virtual void setGyroRange(int num) = 0;
        virtual void setAccelRange(int num) = 0;
        virtual void resetOrientation() = 0;
        virtual void getWorldOrientation(Quaternoin<float>* data) = 0;
        virtual void getLinearAccel(Quaternoin<float>* data) = 0;
        virtual void getRotVel(Quaternoin<float>* data) = 0;
        virtual void update(double dt) = 0;
};