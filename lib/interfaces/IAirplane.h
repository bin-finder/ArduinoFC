#pragma once

class IAirplane{
    public:
        virtual ~IAirplane() = default;
        virtual void setRollPercent(double percent) = 0;
        virtual void setPitchPercent(double percent) = 0;
        virtual void setYawPercent(double percent) = 0;
};