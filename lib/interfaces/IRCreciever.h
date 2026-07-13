#pragma once

class IRCreciever{
    public:
        virtual ~IRCreciever() = default;
        virtual void getLatest(unsigned* data) = 0;
};