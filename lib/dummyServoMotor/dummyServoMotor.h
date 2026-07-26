#include "IServoMotor.h"


class dummyServoMotor : public IServoMotor{
  public:
  dummyServoMotor(int pin,int range){};
  void start(){}
  void stop(){}
  int getPin(){}
  int read(){}
  int getRange(){return 60;}
  void write(int angle){
    Serial.println(angle);
  }
};