#include "MPU6050.h"
#include "Quaternoin.h"
#define DEG_TO_RAD (3.14159265358979323846f / 180.0f)

MPU6050::MPU6050(float beta, int gyroMode, int accelMode, uint8_t address) : 
address(address),
gyroMode(gyroMode), 
accelMode(accelMode),
filter(beta) 
{}

bool MPU6050::begin(){
  Wire.begin();
  i2cTrans(0x6B,0x00); //wake up the IMU.
  //TODO: look through how to verify startup / what needs to be written to.
  //i2cTrans({})
  setGyroRange(gyroMode);
  setAccelRange(accelMode);
  return true;
}

void MPU6050::resetOrientation(){
  ;
}

void MPU6050::i2cTrans(uint8_t addr, uint8_t val){
  uint8_t cmds[] = {addr, val};
  i2cTrans(cmds,sizeof(cmds));
}

void MPU6050::i2cTrans(uint8_t *cmds, int len){
  Wire.beginTransmission(address);
  Wire.write(cmds, len);
  Wire.endTransmission();
}

void MPU6050::setGyroRange(int num){
  if(num < 4 && num >= 0){
    //TODO: verify that num+10 is within even the ballpark of what works.
    i2cTrans(0x1B,static_cast<uint8_t>(num << 3));
    gyroMode = num;
  }
}

void MPU6050::setAccelRange(int num){
  if(num < 4 && num >= 0){
    //TODO: verify that num+10 is within even the ballpark of what works.
    i2cTrans(0x1C,static_cast<uint8_t>(num << 3));
    accelMode = num;
  }
}

void MPU6050::getRotVel(Quaternoin<float>* data){
  uint8_t commands[] = {0x43};
  i2cTrans(commands,sizeof(commands));
  Wire.requestFrom(static_cast<uint8_t>(address), static_cast<uint8_t>(0x06));
  data->w = 0;
  data->x = ((int16_t)((Wire.read() << 8) | Wire.read()) / static_cast<float>(gyroScalers[gyroMode])) * DEG_TO_RAD;
  data->y = ((int16_t)((Wire.read() << 8) | Wire.read()) / static_cast<float>(gyroScalers[gyroMode])) * DEG_TO_RAD;
  data->z = ((int16_t)((Wire.read() << 8) | Wire.read()) / static_cast<float>(gyroScalers[gyroMode])) * DEG_TO_RAD;
}

void MPU6050::getLinearAccel(Quaternoin<float>* data){
  uint8_t commands[] = {0x3B};
  i2cTrans(commands, sizeof(commands));
  Wire.requestFrom(static_cast<uint8_t>(address), static_cast<uint8_t>(0x06));
  data->w = 0;
  data->x = ((int16_t)((Wire.read() << 8) | Wire.read()) / static_cast<float>(accelScalers[accelMode]));
  data->y = ((int16_t)((Wire.read() << 8) | Wire.read()) / static_cast<float>(accelScalers[accelMode]));
  data->z = ((int16_t)((Wire.read() << 8) | Wire.read()) / static_cast<float>(accelScalers[accelMode]));
}

void MPU6050::getWorldOrientation(Quaternoin<float>* data){
  *data = filter.getAttitude();
}

void MPU6050::update(float dt){
  Quaternoin<float> gyro;
  Quaternoin<float> linear;
  getRotVel(&gyro);
  getLinearAccel(&linear);
  filter.update(gyro,linear,dt);
}