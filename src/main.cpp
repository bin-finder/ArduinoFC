#include <Arduino.h>
#include "Elevons.h"
#include "Rudder.h"
#include "ServoMotor.h"
#include "RCreciever.h"
#include "IflightMode.h"
#include "manualControl.h"
/*
* This is the software for the Arduino Fixed Wing Flight Controler.
* It probibly wount work.
* Well see.
* 
* Refrance is the back of the plaine, right roll is positive because
* right handed people are superior.
* (in essence for no good reason)
*/

//TODO get correct pin nums
ServoMotor leftAler[] = {{9}};
ServoMotor rightAler[] = {{11}};

ServoMotor rud[] = {{12}};

//Setup the control surfaces
Rudder rudder = Rudder(rud, 1);
Elevons elevons = Elevons(leftAler, rightAler, 1, 1);

byte interruptPin = 3;
byte channelAmount = 6;

RCreciever reciever(interruptPin, channelAmount);

IflightMode control = manualControl(&elevons, &reciever);

void setup(){
  bool goodToGo = true;

  pinMode(LED_BUILTIN, OUTPUT);
  //starting ther servos.
  rudder.start();
  elevons.start();

  int values[channelAmount];
  reciever.getLatest(values);

  if(values[0] > 10) goodToGo = false;

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

  control.update();

}