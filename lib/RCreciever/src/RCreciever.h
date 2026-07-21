#pragma once
#include "PPMReader.h"
#include "IRCreciever.h"
#include "OTWmath.h"

class RCreciever : public IRCreciever{

    private:
        PPMReader ppm;
        int numChannels;

    public:
        RCreciever(int interruptPin, int numChannels);

        /**
         * Doc comment
         */

        void getLatest(float* data);

};