#include "IflightMode.h"
#include <math.h>
#include "pid.h"
#include "OTWmath.h"
#include "IAirplane.h"

class selfLeveling : public IflightMode{
    private:
        RCreciever* control = nullptr;
        MPU6050* sense = nullptr;
        IAirplane* airplane = nullptr;
        unsigned long prevTime;
        pid pitch = pid(0.1,0.0,0.1);
        pid roll = pid(0.1,0.0,0.1);

    public:
        selfLeveling(IAirplane* airplane, RCreciever* control) :
            control(control),
            airplane(airplane)
        {
            sense->begin();
            prevTime = micros();
            sense->update(0);
        }

        int update(unsigned int dt){
            digitalWrite(13, HIGH);
            float controlTgt[numChannels];
            control->getLatest(controlTgt);
            unsigned int dt = micros() - prevTime;
            sense->update(dt);
            prevTime = micros();
            Quaternoin<float> curState;
            sense->getWorldOrientation(&curState);
            float curPitch = asin(2*curState.x*curState.y + 2*curState.z*curState.w);
            float curBank = acos(curState->w)*2;
            //TODO add extrainous cases, as in https://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToEuler/
            //Implement PI controlers.

            airplane->setPitchPercent(
                pitch.update(
                    fmap(controlTgt[0],-1,1,-45,45),
                    curPitch*180/PI,
                    dt
                )
            );

            airplane->setRollPercent(
                roll.update(
                    fmap(controlTgt[1],-1,1,-45,45),
                    curBank*180/PI,
                    dt
                )
            );
            
            airplane->setYawPercent(
                controlTgt[4]
            );

            airplane->setThrottlePercent(controlTgt[chanThrottle]);

            return 1;
        }

        void reset(){

        }
};