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
        double numPoints;
        double integral=0;
        double slope;

    public:
        double kp;
        double ki;
        double kd;
        double prpevVal = 0;

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
            double dTgt = (tgt - curVal);
            integral += dt*dTgt;
            double out = 
                kp*dTgt +
                ki*integral +
                kd*(prpevVal - curVal)/dt;

            prpevVal = curVal;
            return out;
        }
};