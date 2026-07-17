#include <unity.h>
#include <Arduino.h>
#include "RCreciever.h"

/*
* Heads up, I didnt put a lot of work into this because
* PWMReader doesnt give a really easy way of diagnoseing
* if there is a signal.
*/

void test_rec(){
    RCreciever rec(2,6);
    int dt = 2000;
    //print data for one sec, then ask the usr 
    unsigned long start = millis();
    int data[6];
    while(start+dt > millis()){
        rec.getLatest(data);
        for(int i : data){
            Serial.print(i);
            Serial.print(",");
        }
        Serial.println();
    }
    Serial.println("Does the data look correct?");
    start = millis();
    while(start+1000>millis() && !Serial.available()) delay(1);

    if(millis() < start+1000){
        char out = Serial.read();
        TEST_ASSERT_EQUAL_CHAR('\n',out);
    }
    TEST_IGNORE_MESSAGE("No user input");
}

void setup(){
    Serial.begin(9600);
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(test_rec);
    UNITY_END();
}

void loop(){
;
}