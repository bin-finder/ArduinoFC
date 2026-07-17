#pragma once

class IRCreciever{
    public:
        virtual ~IRCreciever() = default;
        virtual void getLatest(int* data) = 0;
};