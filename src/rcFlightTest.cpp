#include <Arduino.h>
#include "sim/Elevons.h"
#include "sim/Rudder.h"
#include <PPMReader.h>
#include <sim/ServoMotor.h>
#include "sim/MPU6050.h"
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

//Setup the control surfaces
Elevons elevons = Elevons(leftAler, rightAler, 1, 1);

MPU6050 sense;

//The target angles for the pids
double tgtAngles[2]; //x, y

//Setup the PPM reciever for getting target positions.
byte interruptPin = 3;
byte channelAmount = 6;
PPMReader ppm(interruptPin, channelAmount);

void setup(){
  Serial.begin(9600);
  bool goodToGo = true;

  pinMode(LED_BUILTIN, OUTPUT);
  //starting ther servos.
  elevons.start();

  if(!sense.begin()) goodToGo = false;

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
//TODO: write PID loop.
  for (byte channel = 1; channel < 3; ++channel) {
    unsigned value = ppm.latestValidChannelValue(channel, 0);
    tgtAngles[channel - 1] = map(value, 1920, 1100, -45, 45);
  }

  //roll pid:


}