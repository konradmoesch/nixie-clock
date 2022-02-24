#include <Arduino.h>
#include <unity.h>
#include "types.hpp"

// void setUp(void) {
// // set stuff up here
// }

// void tearDown(void) {
// // clean stuff up here
// }

BinaryCodedDecimal_t oldConversion(int digit) {
    BinaryCodedDecimal_t bcd;
    switch (digit) {
        case 0:
            bcd.a = 0;
            bcd.b = 0;
            bcd.c = 0;
            bcd.d = 0;
            break;
        case 1:
            bcd.a = 1;
            bcd.b = 0;
            bcd.c = 0;
            bcd.d = 0;
            break;
        case 2:
            bcd.a = 0;
            bcd.b = 1;
            bcd.c = 0;
            bcd.d = 0;
            break;
        case 3:
            bcd.a = 1;
            bcd.b = 1;
            bcd.c = 0;
            bcd.d = 0;
            break;
        case 4:
            bcd.a = 0;
            bcd.b = 0;
            bcd.c = 1;
            bcd.d = 0;
            break;
        case 5:
            bcd.a = 1;
            bcd.b = 0;
            bcd.c = 1;
            bcd.d = 0;
            break;
        case 6:
            bcd.a = 0;
            bcd.b = 1;
            bcd.c = 1;
            bcd.d = 0;
            break;
        case 7:
            bcd.a = 1;
            bcd.b = 1;
            bcd.c = 1;
            bcd.d = 0;
            break;
        case 8:
            bcd.a = 0;
            bcd.b = 0;
            bcd.c = 0;
            bcd.d = 1;
            break;
        case 9:
            bcd.a = 1;
            bcd.b = 0;
            bcd.c = 0;
            bcd.d = 1;
            break;
        default:
            bcd.a = 1;
            bcd.b = 1;
            bcd.c = 1;
            bcd.d = 1;
            break;
    }
    return bcd;
}

BinaryCodedDecimal_t decimalTo4BitBinary(int decimal_number) {
    BinaryCodedDecimal_t binaryCodedDecimal;
    if (decimal_number > 9) {
        //Log.errorln("error in decimal conversion: number too big");
        binaryCodedDecimal.a = true;
        binaryCodedDecimal.b = true;
        binaryCodedDecimal.c = true;
        binaryCodedDecimal.d = true;
        return binaryCodedDecimal;
    }
    int binaryNumber[4];
    binaryNumber[0] = 0;
    binaryNumber[1] = 0;
    binaryNumber[2] = 0;
    binaryNumber[3] = 0;
    int i = 0;
    while (decimal_number > 0) {
        binaryNumber[i] = decimal_number % 2;
        decimal_number = decimal_number / 2;
        i++;
    }
    binaryCodedDecimal.a = binaryNumber[0];
    binaryCodedDecimal.b = binaryNumber[1];
    binaryCodedDecimal.c = binaryNumber[2];
    binaryCodedDecimal.d = binaryNumber[3];
    return binaryCodedDecimal;
}

void test_old_conversion() {
    BinaryCodedDecimal_t bcd;
    bcd.a = false;
    bcd.b = false;
    bcd.c = false;
    bcd.d = false;
    BinaryCodedDecimal_t computed = oldConversion(0);
    TEST_ASSERT_EQUAL(bcd.a, computed.a);
    TEST_ASSERT_EQUAL(bcd.b, computed.b);
    TEST_ASSERT_EQUAL(bcd.c, computed.c);
    TEST_ASSERT_EQUAL(bcd.d, computed.d);

    bcd.a = true;
    bcd.b = false;
    bcd.c = false;
    bcd.d = false;
    computed = oldConversion(1);
    TEST_ASSERT_EQUAL(bcd.a, computed.a);
    TEST_ASSERT_EQUAL(bcd.b, computed.b);
    TEST_ASSERT_EQUAL(bcd.c, computed.c);
    TEST_ASSERT_EQUAL(bcd.d, computed.d);

    bcd.a = true;
    bcd.b = false;
    bcd.c = false;
    bcd.d = true;
    computed = oldConversion(9);
    TEST_ASSERT_EQUAL(bcd.a, computed.a);
    TEST_ASSERT_EQUAL(bcd.b, computed.b);
    TEST_ASSERT_EQUAL(bcd.c, computed.c);
    TEST_ASSERT_EQUAL(bcd.d, computed.d);

    bcd.a = true;
    bcd.b = true;
    bcd.c = true;
    bcd.d = true;
    computed = oldConversion(10);
    TEST_ASSERT_EQUAL(bcd.a, computed.a);
    TEST_ASSERT_EQUAL(bcd.b, computed.b);
    TEST_ASSERT_EQUAL(bcd.c, computed.c);
    TEST_ASSERT_EQUAL(bcd.d, computed.d);
    computed = oldConversion(15);
    TEST_ASSERT_EQUAL(bcd.a, computed.a);
    TEST_ASSERT_EQUAL(bcd.b, computed.b);
    TEST_ASSERT_EQUAL(bcd.c, computed.c);
    TEST_ASSERT_EQUAL(bcd.d, computed.d);
}

void test_new_conversion() {
    BinaryCodedDecimal_t bcd;
    bcd.a = false;
    bcd.b = false;
    bcd.c = false;
    bcd.d = false;
    BinaryCodedDecimal_t computed = decimalTo4BitBinary(0);
    TEST_ASSERT_EQUAL(bcd.a, computed.a);
    TEST_ASSERT_EQUAL(bcd.b, computed.b);
    TEST_ASSERT_EQUAL(bcd.c, computed.c);
    TEST_ASSERT_EQUAL(bcd.d, computed.d);

    bcd.a = true;
    bcd.b = false;
    bcd.c = false;
    bcd.d = false;
    computed = decimalTo4BitBinary(1);
    TEST_ASSERT_EQUAL(bcd.a, computed.a);
    TEST_ASSERT_EQUAL(bcd.b, computed.b);
    TEST_ASSERT_EQUAL(bcd.c, computed.c);
    TEST_ASSERT_EQUAL(bcd.d, computed.d);

    bcd.a = true;
    bcd.b = false;
    bcd.c = false;
    bcd.d = true;
    computed = decimalTo4BitBinary(9);
    TEST_ASSERT_EQUAL(bcd.a, computed.a);
    TEST_ASSERT_EQUAL(bcd.b, computed.b);
    TEST_ASSERT_EQUAL(bcd.c, computed.c);
    TEST_ASSERT_EQUAL(bcd.d, computed.d);

    bcd.a = true;
    bcd.b = true;
    bcd.c = true;
    bcd.d = true;
    computed = decimalTo4BitBinary(10);
    TEST_ASSERT_EQUAL(bcd.a, computed.a);
    TEST_ASSERT_EQUAL(bcd.b, computed.b);
    TEST_ASSERT_EQUAL(bcd.c, computed.c);
    TEST_ASSERT_EQUAL(bcd.d, computed.d);
    computed = decimalTo4BitBinary(15);
    TEST_ASSERT_EQUAL(bcd.a, computed.a);
    TEST_ASSERT_EQUAL(bcd.b, computed.b);
    TEST_ASSERT_EQUAL(bcd.c, computed.c);
    TEST_ASSERT_EQUAL(bcd.d, computed.d);
}

void test_both_conversions(){
    for (int digit = 0; digit < 17; digit++) {
        BinaryCodedDecimal_t old_value = oldConversion(digit);
        BinaryCodedDecimal_t new_value = oldConversion(digit);
        TEST_ASSERT_EQUAL(old_value.a, new_value.a);
        TEST_ASSERT_EQUAL(old_value.b, new_value.b);
        TEST_ASSERT_EQUAL(old_value.c, new_value.c);
        TEST_ASSERT_EQUAL(old_value.d, new_value.d);
    }
}

void setup() {
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();    // IMPORTANT LINE!
    RUN_TEST(test_old_conversion);
    RUN_TEST(test_new_conversion);
    RUN_TEST(test_both_conversions);

    UNITY_END();
}

void loop() {

}