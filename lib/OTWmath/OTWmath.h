#pragma once

/*
Off The Wall Math is just a collection of math functions
I need in a project. Nothing special, no cool organization
or anything, just a junkyard of cool math functions.
*/

/**
 * Implementation of the map() function from Arduino just for doubles.
 * @param val The input val
 * @param frmLow The bottom of the from range
 * @param frmHigh The top of the from range
 * @param toLow The low end of the range that it is being converted to
 * @param toHigh The high end of the range being converted to
 */
inline double fmap(double val, double frmLow, double frmHigh, double toLow, double toHigh){
    return (val - frmLow)
                /
            (frmHigh - frmLow) * (toHigh - toLow) + toLow;
}

/**
 * This function will force a value to be within a range
 * @param value The input value
 * @param min The minimum allowable value
 * @param max The maximum allow value
 * @return The value that is now within the range
 */

template <typename T>
inline T coerceIn(T value, T min, T max){
    if(value > max) return max;
    else if (value < min) return min;
    else return value; 
}