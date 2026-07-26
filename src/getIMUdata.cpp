#include <Arduino.h>
#include "MPU6050.h"
#include "Quaternoin.h"

MPU6050 sense(0.8,0,0);

int samples = 10000;

void setup(){

    Serial.begin(115200);

    sense.begin();

    uint32_t lastTime = micros();

    for(int count = 0; count < samples; count++){

        uint32_t now = micros();

        float dt = (now - lastTime) * 1e-6f;
        lastTime = now;

        if(dt > 0.1f)
            dt = 0.1f;


        sense.update(dt);


        Quaternoin<float> pos;
        sense.getWorldOrientation(&pos);


        Serial.print(
    atan2(2.0f * (pos.w * pos.x + pos.y * pos.z),1.0f - 2.0f * (pos.x * pos.x + pos.y * pos.y)),4);
        Serial.print(",");
        // Serial.print(pos.w, 4);
        // Serial.print(",");
        // Serial.print(pos.x, 4);
        // Serial.print(",");
        // Serial.print(pos.y, 4);
        // Serial.print(",");
        // Serial.println(pos.z, 4);


        while(micros() - now < 10000){}
    }
}


void loop(){}