#pragma once

#include <Wire.h>
#include "MadgwickFilter.h"
#include "Quaternoin.h"
#include "Vec3D.h"
#include "interfaces/IMPU6050.h"

/*
Simple MPU6050 driver.
Loads o' info here:
https://cdn.sparkfun.com/datasheets/Sensors/Accelerometers/RM-MPU-6000A.pdf
*/
class IMPU6050 : public IMPU6050{
  private:
    uint8_t address;
    int accRange;
    int gyroMode;
    int gyroRanges[4] = {250,500,1000,2000};
    int accelMode;
    int accelRanges[4] = {2,4,8,16};
    int accelScalers[4] = {16384,8192,4096,2048};

    void i2cTrans(uint8_t addr, uint8_t val);
    void i2cTrans(uint8_t *cmds, int len);

    MadgwicFilter filter = MadgwicFilter(0.2);

  public:
    /*
    Initiliser.
    @param address The address of the MPU6050
    @param beta The tuning var for the MadgwicFilter.
    */
    IMPU6050(float beta, uint8_t address = 0x68);
    bool begin();
    void update();

    /*
    Sets the scale of the gyroscope.
    @param num the number that corrosponds to the requested rate.
    0 ± 250 °/s
    1 ± 500 °/s
    2 ± 1000 °/s
    3 ± 2000 °/s*/
    void setGyroRange(int num);

    /*
    Sets the scale of the accellerometer
    @param num the number of the selection.
    0 ±2g
    1 ±4g
    2 ±8g
    3 ±16g*/
    void setAccelRange(int num);

    /*Sets the Orientation Biases to make the sensor read level.*/
    void resetOrientation();

    /*Returns the orientation of the IMU */
    Quaternoin<float> getWorldOrientation();

    /*Returns the World Centric Accelleration*/
    void getLinearAccel(Quaternoin<float>* data);

    /*Returns the IMU centric accelleration*/
    void getRotAccel(Quaternoin<float>* data);
};