#pragma once

class IServoMotor{
    public:
        virtual ~IServoMotor() = default;
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual void write(int angle) = 0;
        virtual int read() = 0;
        virtual int getPin() = 0;
};