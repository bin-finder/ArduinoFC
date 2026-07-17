#include <unity.h>
#include <Arduino.h>
#include "MPU6050.h"
#include "Quaternoin.h"

void test_MPU6050(){
    MPU6050 sense(0.2);
    bool out = sense.begin();
    TEST_ASSERT(out);
    sense.setAccelRange(2);
    sense.setGyroRange(2);
    sense.resetOrientation();
    Quaternoin<float> accel;
    Quaternoin<float> rot;
    sense.getLinearAccel(&accel);
    sense.getRotVel(&rot);
    TEST_ASSERT_FLOAT_WITHIN(0.2, 1.0, accel.norm());
    TEST_ASSERT_FLOAT_WITHIN(0.2, 0.0, rot.norm());
}

void setup(){
    Serial.begin(9600);
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(test_MPU6050);
    UNITY_END();
}
void loop(){

}