#pragma once

template <typename T>
class iirFilter{

    private:
        bool first = true;

    public:
        T prevVal;
        T smothedVal;
        double percentPresent;

        /**
         * Default constructor
         * @param presentPercent The value that will be applied to new values.
         */

        iirFilter(double presentPercent) : percentPresent(presentPercent) {}

        /**
         * Takes in a new value for the filter to smooth.
         * @param nextVal The newest value to update the filter.
         */

        T update(T nextVal){
            if(!first) smothedVal = (1-percentPresent)*prevVal + percentPresent*nextVal;
            else{
                first = false;
                return nextVal;
            }
            prevVal = nextVal;
            return smothedVal;
        }
};