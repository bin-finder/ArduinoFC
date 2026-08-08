#include "IflightMode.h"
#include <math.h>
#include "pid.h"
#include "OTWmath.h"
#include "IAirplane.h"
#include "IMPU6050.h"
#include "iirFilter.h"

class selfLeveling : public IflightMode{
    private:
        RCreciever* control = nullptr;
        IMPU6050* sense = nullptr;
        IAirplane* airplane = nullptr;
        unsigned long prevTime;
        pid pitch{0.08,0.0,0.001};
        pid roll{0.1,0.0,0.001};

        //This is to smooth out the positioning data so its not so jittery.
        iirFilter<double> valFilter{0.2};

    public:
        selfLeveling(IAirplane* airplane, IMPU6050* sense, RCreciever* control) :
            control(control),
            sense(sense),
            airplane(airplane)
        {}

        int update(double dt){
            //digitalWrite(13, HIGH);
            float controlTgt[numChannels];
            control->getLatest(controlTgt);
            Quaternoin<float> curState;
            sense->getWorldOrientation(&curState);
            float curPitch = asin(2*curState.w*curState.y - 2*curState.z*curState.x);
            float curBank = atan2(2.0f * (curState.w * curState.x + curState.y * curState.z),1.0f - 2.0f * (curState.x * curState.x + curState.y * curState.y));

            //if(isnan(curPitch)) return 0;

            // Serial.print(curPitch*180/PI);
            // Serial.println();
            // Serial.print(",");
            //TODO add extrainous cases, as in https://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToEuler/
            //Implement PI controlers.
            // Serial.println(fmap(controlTgt[chanElevator],-1,1,-45,45));
            // Serial.print(",");
            airplane->setPitchPercent( 
                pitch.update(
                    valFilter(
                        -fmap(controlTgt[chanElevator],-1,1,-45,45),
                        curPitch*180/PI,
                        dt
                    )
                )
            );
            
            airplane->setRollPercent(
                roll.update(
                    valFilter(
                        fmap(controlTgt[chanAileron],-1,1,-45,45),
                        -curBank*180/PI,
                        dt
                    )
                )
            );
            
            airplane->setYawPercent(
                controlTgt[chanRudder]
            );

            airplane->setThrottlePercent(controlTgt[chanThrottle]);

            return 1;
        }

        void reset(){

        }
};