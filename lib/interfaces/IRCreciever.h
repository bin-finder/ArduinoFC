#pragma once

class IRCreciever{
    public:
        virtual ~IRCreciever() = default;
        virtual void getLatest(float* data) = 0;
};