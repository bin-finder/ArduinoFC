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
        virtual int update() = 0;
        virtual void reset() = 0;
};