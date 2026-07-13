#pragma once 

class IElevons{
    public:
        virtual ~IElevons() = default;
        virtual void write(double percentPitch, double percentRoll) = 0;
        virtual void start() = 0;
};