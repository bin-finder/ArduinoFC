#include <Arduino.h>
#include "Rudder.h"
#include "flyingWing.h"
#include "Ailerons.h"
#include "Elevators.h"
#include "ServoMotor.h"
#include "RCreciever.h"
#include "manualControl.h"
#include "MPU6050.h"
#include "selfLeveling.h"
#include "standard.h"
#include "Throttle.h"
#include "dummyServoMotor.h" 

/*
* This is the software for the Arduino Fixed Wing Flight Controler.
* It probibly wount work.
* Well see.
* 
* Refrance is the back of the plaine, right roll is positive because
* right handed people are superior.
* (in essence for no good reason)
*/

ServoMotor SleftAler(elevonLeftPin, 60);
ServoMotor SrightAler(elevonRightPin, 60);
ServoMotor Selevator(elevatorPin, 120);
ServoMotor Srudder(rudderPin, 120);

ServoMotor Sthrottle(throttlePin,180,0,true,1000,2000);

Ailerons alerons(&SleftAler, &SrightAler);
Elevators elevators(&Selevator, 1);
Rudder rudder(&Srudder, 1);
Throttle throttle(&Sthrottle);

standard airplane(&alerons, &elevators, &rudder, &throttle);

byte interruptPin = 2;
byte channelAmount = 6;

RCreciever reciever(interruptPin, channelAmount);

MPU6050 sense(0.9,1,1);

manualControl manualMode = manualControl(&airplane, &reciever);
selfLeveling angleMode = selfLeveling(&airplane,&sense,&reciever);

IflightMode* control = &manualMode;

bool mode = false;

int loopTime = 13000; //13ms

unsigned long prevTime = micros();

void err(){
  while(true) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(250);
    digitalWrite(LED_BUILTIN, LOW);
    delay(250);
  }
}

void alternate(){
  if(mode){
    digitalWrite(LED_BUILTIN, HIGH);
    mode = false;
  }
  else{
    digitalWrite(LED_BUILTIN, LOW);
    mode = true;
  }
}

void setup(){
  //Serial.begin(115200);
  bool goodToGo = true;

  pinMode(LED_BUILTIN, OUTPUT);
  //starting ther servos.

  sense.begin();

  alerons.start();
  elevators.start();
  throttle.start();
  rudder.start();
  //elevons.start();

  float values[channelAmount];
  reciever.getLatest(values);

  //if(values[0] > 10) goodToGo = false;

  if(!goodToGo){
    while(true) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
    }
  }
  else digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Starting...");
}

void loop(){

  float value[numChannels];
  reciever.getLatest(value);
  if(value[chanGear] > 0) control = &angleMode;
  else control = &manualMode;

  unsigned long curTime = micros();
  unsigned long dt = curTime - prevTime;
  prevTime = curTime;
  float dtSec = dt/1000000.0f;
  sense.update(dtSec);
  if(control->update(dtSec) != 1){
    err();
  }
  //Timeing logic:
  // if(++count == 50){
  //   alternate();
  //   count = 0;
  // }
}