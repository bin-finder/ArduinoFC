#pragma once
#include "OTWmath.h"
#include "ServoMotor.h"

class Throttle{
    public:
        ServoMotor* thrott = nullptr;

        Throttle(ServoMotor* servo) : thrott(servo) {}
        void start(){
            thrott->start();
        }
        void write(double percent){
            thrott->write(fmap(percent,-1,1,-90,90));
        }
};