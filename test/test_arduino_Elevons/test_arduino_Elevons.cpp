#include "Elevons.h"
#include "ServoMotor.h"
#include <Arduino.h>
#include <unity.h>
#include "config.h"

void flash(){
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    delay(1000);
}

void test(){
    pinMode(13, OUTPUT);
    ServoMotor left(elevonLeftPin);
    ServoMotor right(elevonRightPin);

    Elevons elev(&left, &right, 1,1);

    left.write(90);
    flash();
    left.write(-90);
    flash();
    left.write(0);
    right.write(90);
    flash();
    right.write(-90);
    flash();
    right.write(0);
    flash();

    // elev.write(0,0);
    // delay(1000);
    // elev.write(1,0);
    // delay(1000);
    // elev.write(-1,0);
    // delay(1000);
    // elev.write(0,1);
    // delay(1000);
    // elev.write(0,-1);
    // delay(1000);
}

void setup(){
    Serial.begin(11520);
    delay(2000);
    test();
}

void loop(){}