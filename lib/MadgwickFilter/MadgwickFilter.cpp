#include "MadgwickFilter.h"
#include "Quaternoin.h"

MadgwicFilter::MadgwicFilter(float beta) : beta(beta) {}

void MadgwicFilter::update(Quaternoin<float> gyroRates, Quaternoin<float> accel, float dt){
  accel.normalize();
  Matrix<float, 4, 1> temp3 = jacopian(curAttitude) * f(curAttitude, accel);
  Quaternoin<float> temp;
  temp.w = temp3.data[0][0];
  temp.x = temp3.data[1][0];
  temp.y = temp3.data[2][0];
  temp.z = temp3.data[3][0];
  Quaternoin<float> gradient = temp / temp.norm();
  Quaternoin<float> qDot =
      0.5f * (curAttitude * gyroRates)
      - beta * gradient;
  curAttitude += qDot * dt; 
  curAttitude.normalize();
}

Quaternoin<float> MadgwicFilter::getAttitude(){
  return curAttitude;
}

Matrix<float,3,1> MadgwicFilter::f(Quaternoin<float> prevq, Quaternoin<float> sensorAcc){
  Matrix<float,3,1> result; 
  result.data[0][0] = 2*(prevq.x*prevq.z-prevq.w*prevq.y)-sensorAcc.x;
  result.data[1][0] = 2*(prevq.w*prevq.x+prevq.y*prevq.z)-sensorAcc.y;
  result.data[2][0] = 2*(0.5-prevq.x*prevq.x-prevq.y*prevq.y)-sensorAcc.z;
  return result;
}

Matrix<float,4,3> MadgwicFilter::jacopian(Quaternoin<float> q){
  Matrix<float, 4, 3> JT;

  JT.data[0][0] = -2*q.y;
  JT.data[0][1] =  2*q.x;
  JT.data[0][2] =  0.0f;

  JT.data[1][0] =  2*q.z;
  JT.data[1][1] =  2*q.w;
  JT.data[1][2] = -4*q.x;

  JT.data[2][0] = -2*q.w;
  JT.data[2][1] =  2*q.z;
  JT.data[2][2] = -4*q.y;

  JT.data[3][0] =  2*q.x;
  JT.data[3][1] =  2*q.y;
  JT.data[3][2] =  0.0f;

  return JT;
}