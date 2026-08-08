#include "IServoMotor.h"


class dummyServoMotor : public IServoMotor{
  public:
  dummyServoMotor(int pin,int range, int other, bool reverse){};
  void start(){}
  void stop(){}
  int getPin(){return 0;}
  int read(){return 0;}
  int getRange(){return 60;}
  void write(int angle){
    Serial.println(angle);
  }
};