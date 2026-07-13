#include "RCreciever.h"

RCreciever::RCreciever(int interruptPin, int numChannels) : interruptPin(interruptPin), numChannels(numChannels){
    ppm = new PPMReader(interruptPin, numChannels);
}

void RCreciever::getLatest(unsigned* data){
  for (byte channel = 1; channel < numChannels; ++channel) {
    unsigned value = ppm->latestValidChannelValue(channel, 0);
    data[channel - 1] = map(value, 1920, 1100, -45, 45);
  }
}
