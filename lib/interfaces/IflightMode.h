#pragma once
#include "Elevons.h"
#include "Rudder.h"
#include "RCreciever.h"
#include "config.h"
#include "MPU6050.h"
#include <Arduino.h>

class IflightMode{
    public:
        virtual ~IflightMode() = default;

        /**
         * This method is called on every control loop, allowing the
         * flight mode to carry out its behavior.
         */

        virtual int update(double dt) = 0;

        /**
         * This is here incase motor configs need reset inbetween flight
         * mode changes, or what ever else needs done. IDK
         */
        
        virtual void reset() = 0;
};