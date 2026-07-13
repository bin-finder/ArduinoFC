#include "Quaternoin.h"
#include <unity.h>

void test_quaternion() {
    Quaternoin<int> q1(1,2,3,4);
    Quaternoin<int> q2(5,6,7,8);

    Quaternoin<int> result = q1 * q2;

    TEST_ASSERT_EQUAL(-60, result.w);
    TEST_ASSERT_EQUAL(12, result.x);
    TEST_ASSERT_EQUAL(30, result.y);
    TEST_ASSERT_EQUAL(24, result.z);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_quaternion);
    UNITY_END();
}