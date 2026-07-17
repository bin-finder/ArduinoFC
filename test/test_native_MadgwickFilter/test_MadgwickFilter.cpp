#include "MadgwickFilter.h"
#include <unity.h>
#include <fstream>
#include <string>
#include <iostream>
#include "Quaternoin.h"
#include "Vec3D.h"

using namespace std;

void test_filter(){
    const int numLoops = 576;
    const float dt = 0.1;

    Quaternoin<float> rotData[numLoops];
    Quaternoin<float> accelData[numLoops];

    //process data into arrays:
    string line;
    string filePath = "test/native/test_MadgwickFilter/testData.txt";
    ifstream data (filePath);

    if (!data.is_open()) {
        // print error message and return
        TEST_FAIL_MESSAGE("error: could not open data file.");
    
    }

    MadgwicFilter filter(0.5);
    for(int i = 0; i < numLoops; i++){
        getline(data,line);
        //prosess the line:
        int pos = 0;
        float lineData[6];
        while(line.length() > 0){
            int element = line.find(",");
            lineData[pos] = stof(line.substr(0,element));
            pos++;
            line.erase(0,element+1);
        }
        Quaternoin<float> accelData(0,lineData[0],lineData[1],lineData[2]);
        Quaternoin<float> rotData(0,lineData[3],lineData[4],lineData[5]);
        filter.update(rotData,accelData,dt);
    }
    //TEST_ASSERT(1==1);
}

int main(){
    UNITY_BEGIN();
    RUN_TEST(test_filter);
    UNITY_END();
}