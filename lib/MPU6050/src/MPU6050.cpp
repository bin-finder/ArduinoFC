#include "MPU6050.h"
#include "Quaternoin.h"
#define DEG_TO_RAD 3.14159265358979323846f / 180.0f;

IMPU6050::IMPU6050(float beta, uint8_t address) : address(address), filter(beta) {}

bool IMPU6050::begin(){
  Wire.begin();
  i2cTrans(0x6B,0x00); //wake up the IMU.
  //TODO: look through how to verify startup / what needs to be written to.
  //i2cTrans({})
  return true;
}

void IMPU6050::i2cTrans(uint8_t addr, uint8_t val){
  uint8_t cmds[] = {addr, val};
  i2cTrans(cmds,sizeof(cmds));
}

void IMPU6050::i2cTrans(uint8_t *cmds, int len){
  Wire.beginTransmission(address);
  Wire.write(cmds, len);
  Wire.endTransmission();
}

void IMPU6050::setGyroRange(int num){
  if(num < 4 && num >= 0){
    //TODO: verify that num+10 is within even the ballpark of what works.
    i2cTrans(0x1B,static_cast<uint8_t>(num << 3));
    gyroMode = num;
  }
}

void IMPU6050::setAccelRange(int num){
  if(num < 4 && num >= 0){
    //TODO: verify that num+10 is within even the ballpark of what works.
    i2cTrans(0x1C,static_cast<uint8_t>(num << 3));
    accelMode = num;
  }
}

void IMPU6050::getRotAccel(Quaternoin<float>* data){
  uint8_t commands[] = {0x3B};
  i2cTrans(commands,sizeof(commands));
  Wire.requestFrom(static_cast<uint8_t>(address), static_cast<uint8_t>(0x06));
  //accel x
  data->x = ((Wire.read() << 8 | Wire.read()) / static_cast<float>(accelRanges[accelMode])) * DEG_TO_RAD;
  data->y = ((Wire.read() << 8 | Wire.read()) / static_cast<float>(accelRanges[accelMode])) * DEG_TO_RAD;
  data->z = ((Wire.read() << 8 | Wire.read()) / static_cast<float>(accelRanges[accelMode])) * DEG_TO_RAD;
}

void IMPU6050::getLinearAccel(Quaternoin<float>* data){
  uint8_t commands[] = {0x43};
  i2cTrans(commands, sizeof(commands));
  Wire.requestFrom(static_cast<uint8_t>(address), static_cast<uint8_t>(0x06));
  //accel x
  data->x = ((Wire.read() << 8 | Wire.read()) / static_cast<float>(accelRanges[accelMode]));
  data->y = ((Wire.read() << 8 | Wire.read()) / static_cast<float>(accelRanges[accelMode]));
  data->z = ((Wire.read() << 8 | Wire.read()) / static_cast<float>(accelRanges[accelMode]));
}

Quaternoin<float> IMPU6050::getWorldOrientation(){
  return filter.getAttitude();
}