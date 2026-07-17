#pragma once
class IflightMode{
    public:
    virtual ~IflightMode() = default;
    virtual int update();
    virtual void reset();
};