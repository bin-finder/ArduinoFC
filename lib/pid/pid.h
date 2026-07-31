#pragma once


/**
 * This is just a simple PID class. Nothing to see here. Move along...
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * Do as your told!
 */

class pid{
    private:
        double integral=0;
        double diritive = 0;

    public:
        double kp;
        double ki;
        double kd;
        double prevErr = 0;

        /**
         * Constructor.
         */
        pid(double p, double i, double d) : kp(p), ki(i), kd(d)
        {}

        /**
         * This is the pid update function.
         * @param tgt The target value
         * @param curVal The current measurement of the system, in the same units as the target
         * @param dt The diffrence in time from the last update.
         */
        double update(double tgt, double curVal, double dt){
            if (dt <= 0.0f)
                return 0.0f;
            double err = (tgt - curVal);
            integral += dt*err;
            float rawD = (err - prevErr)/dt;
            double out = 
                kp*err +
                ki*integral +
                kd*(0.95*diritive+0.05*rawD);

            prevErr = curVal;
            return out;
        }
};