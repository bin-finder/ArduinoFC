#pragma once
#include "PPMReader.h"
#include "IRCreciever.h"

class RCreciever : public IRCreciever{

    private:
        int interruptPin;
        int numChannels;
        PPMReader* ppm = nullptr;

    public:
        RCreciever(int interruptPin, int numChannels);
        void getLatest(unsigned* data);

};