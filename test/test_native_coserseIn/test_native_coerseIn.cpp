#include "OTWmath.h"
#include <unity.h>


void testCoerse(){
    TEST_ASSERT_EQUAL(50,coerceIn(100,-50,50));
    TEST_ASSERT_EQUAL(-30,coerceIn(-90,-30,30));
}

int main(){
    UNITY_BEGIN();
    RUN_TEST(testCoerse);
    UNITY_END();
}