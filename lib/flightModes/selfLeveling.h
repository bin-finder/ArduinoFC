#include "IflightMode.h"
#include <math.h>
#include "pid.h"
#include "OTWmath.h"

class selfLeveling : public IflightMode{
    private:
        Elevons* elevons = nullptr;
        RCreciever* control = nullptr;
        Rudder* rudder = nullptr;
        MPU6050* sense = nullptr;
        unsigned long prevTime;
        pid pitch = pid(0.1,0.0,0.1);
        pid roll = pid(0.1,0.0,0.1);

    public:
        selfLeveling(Elevons* elevons, Rudder* rudder, RCreciever* control) :
            elevons(elevons),
            rudder(rudder),
            control(control)
        {
            sense->begin();
            prevTime = micros();
            sense->update(0);
        }

        int update(){
            float controlTgt[numChannels];
            control->getLatest(controlTgt);
            unsigned int dt = micros() - prevTime;
            sense->update(dt);
            prevTime = micros();
            Quaternoin<float> curState;
            sense->getWorldOrientation(&curState);
            float curPitch = asin(2*curState.x*curState.y + 2*curState.z*curState.w);
            float curBank = atan2(2*curState.x*curState.w - 2*curState.y*curState.z, 1 - 2*curState.x*curState.x - 2*curState.z*curState.z);
            //TODO add extrainous cases, as in https://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToEuler/
            //Implement PI controlers.
            elevons->write(
                    pitch.update(
                        fmap(controlTgt[0],-1,1,-45,45),
                        curPitch*180/PI,
                        dt
                    ),
                    roll.update(
                        fmap(controlTgt[1],-1,1,-45,45),
                        curBank*180/PI,
                        dt
                    )
            );
            return 0.1;
        }

        void reset(){

        }
};