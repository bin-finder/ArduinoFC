#include <Arduino.h>
#include "Rudder.h"
#include "Ailerons.h"
#include "Elevators.h"
#include "ServoMotor.h"
#include "RCreciever.h"
#include "manualControl.h"
#include "MPU6050.h"
#include "selfLeveling.h"
#include "standard.h"

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
ServoMotor Selevator(elevatorPin, 60);
ServoMotor Srudder(rudderPin, 60);

ServoMotor Sthrottle(throttlePin,180,-90);

Ailerons alerons(&SleftAler, &SrightAler);
Elevators elevators(&Selevator, 1);
Rudder rudder(&Srudder, 1);

standard airplane(&alerons, &elevators, &rudder, &Sthrottle);

byte interruptPin = 2;
byte channelAmount = 6;

RCreciever reciever(interruptPin, channelAmount);

MPU6050 sense(0.8,0,0);

//manualControl control = manualControl(&elevons, &reciever);
selfLeveling angleMode = selfLeveling(&airplane,&sense,&reciever);
manualControl manual = manualControl(&airplane,&reciever);

IflightMode* control = &manual;

unsigned long prevTime = micros();

void setup(){
  bool goodToGo = true;

  pinMode(LED_BUILTIN, OUTPUT);
  //starting ther servos.

  alerons.start();
  elevators.start();
  Sthrottle.start();
  rudder.start();

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
}

void loop(){

  // float value[numChannels];
  // reciever.getLatest(value);
  // if(value[chanGear] > 0) control = &angleMode;
  // else control = &manual;

  unsigned int dt = micros() - prevTime;
  sense.update(dt);
  prevTime = micros();
  control->update(dt);
}