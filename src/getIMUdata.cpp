#include <Arduino.h>
#include "MPU6050.h"
#include "Quaternoin.h"

MPU6050 sense(0.2);
int samples = 10000;
float dt = 0.1;

void setup(){
    Serial.begin(9600);
    sense.begin();

    int count = 0;

    sense.setAccelRange(0);
    sense.setGyroRange(0);

    while (count < samples){
        int time = micros();        
        Quaternoin<float> linearAccel;
        Quaternoin<float> rotAccel;
        sense.getLinearAccel(&linearAccel);
        sense.getRotVel(&rotAccel);
        float arr[] = {linearAccel.x, linearAccel.y, linearAccel.z, rotAccel.x, rotAccel.y, rotAccel.z};
        for(float i : arr){
            Serial.print(i);
            Serial.print(",");
        }
        Serial.println();
        count ++;
        while(micros() < time+dt*1000){}
    }
}

void loop(){}