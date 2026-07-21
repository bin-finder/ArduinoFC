#include "RCreciever.h"

RCreciever::RCreciever(int interruptPin, int numChannels) : numChannels(numChannels), ppm(interruptPin, numChannels)
{}

/**
 * Returns the percentage value of the control interface.
 * @param data Pointer to where the data will be written.
 */

void RCreciever::getLatest(float* data){
  for (byte channel = 1; channel < numChannels; ++channel) {
    unsigned value = ppm.latestValidChannelValue(channel, 0);
    data[channel - 1] = fmap(value, 1920, 1100, -1, 1);
  }
}
