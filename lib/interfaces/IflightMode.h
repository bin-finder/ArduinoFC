#pragma once
class IflightMode{
    public:
        virtual ~IflightMode() = default;
        virtual int update() = 0;
        virtual void reset() = 0;
};