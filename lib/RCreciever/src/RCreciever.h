#pragma once
#include "PPMReader.h"
#include "IRCreciever.h"

class RCreciever : public IRCreciever{

    private:
        PPMReader ppm;
        int numChannels;

    public:
        RCreciever(int interruptPin, int numChannels);
        void getLatest(int* data);

};