#pragma once

class IRudder{
    public:
        virtual ~IRudder() = default;
        virtual void start() = 0;
        virtual void write(double percentage) = 0;
};