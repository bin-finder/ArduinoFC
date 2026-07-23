#include "IflightMode.h"
#include <math.h>
#include "pid.h"
#include "OTWmath.h"
#include "IAirplane.h"
#include "IMPU6050.h"

class selfLeveling : public IflightMode{
    private:
        RCreciever* control = nullptr;
        IMPU6050* sense = nullptr;
        IAirplane* airplane = nullptr;
        unsigned long prevTime;
        pid pitch = pid(0.1,0.0,0.1);
        pid roll = pid(0.1,0.0,0.1);

    public:
        selfLeveling(IAirplane* airplane, IMPU6050* sense, RCreciever* control) :
            control(control),
            sense(sense),
            airplane(airplane)
        {}

        int update(unsigned int dt){
            float controlTgt[numChannels];
            control->getLatest(controlTgt);
            Quaternoin<float> curState;
            sense->getWorldOrientation(&curState);
            float curPitch = asin(2*curState.x*curState.y + 2*curState.z*curState.w);
            float curBank = atan2(2*curState.x*curState.w - 2*curState.y*curState.z, 1 - 2*curState.x*curState.x - 2*curState.z*curState.z);
            //TODO add extrainous cases, as in https://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToEuler/
            //Implement PI controlers.

            airplane->setPitchPercent(
                pitch.update(
                    fmap(controlTgt[chanElevator],-1,1,-45,45),
                    curPitch*180/PI,
                    dt
                )
            );

            airplane->setRollPercent(
                roll.update(
                    fmap(controlTgt[chanAileron],-1,1,-45,45),
                    curBank*180/PI,
                    dt
                )
            );
            
            airplane->setYawPercent(
                controlTgt[chanRudder]
            );

            return 1;
        }

        void reset(){

        }
};