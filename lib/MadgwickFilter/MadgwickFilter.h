#pragma once
#include "Quaternoin.h"
#include "Matrix.h"

class MadgwicFilter{
  private:

    //tunable variable for this filter
    float beta;

    //The current calculated attitude of the IMU
    Quaternoin<float> curAttitude;

    Matrix<float,3,1> f(Quaternoin<float> prevq, Quaternoin<float> sensorAcc);

    Matrix<float,4,3> jacopian(Quaternoin<float> prevq);

  public:
    MadgwicFilter(float beta);
    void update(Quaternoin<float> gyroRates, Quaternoin<float> accel, float dt);
    Quaternoin<float> getAttitude();
};