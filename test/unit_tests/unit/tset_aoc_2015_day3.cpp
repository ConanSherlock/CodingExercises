/** ***************************************** Includes ****************************************************************/

#include "unity.h"
#include <fstream>
#include <string>
#include "aoc_2015_day3.hpp"

using namespace std;

/** ***************************************** Global Variables ********************************************************/

/** ***************************************** Private Function Declarations *******************************************/

/** ***************************************** Test Cases **************************************************************/

void test_aoc_day3_basic_input() {

    //  Present Delivery to unique houses
    //  > => 2 deliveries to 2 houses
    //  ^>v< => 5 deliveries to 4 houses
    //  ^v^v^v^v^v => 11 deliveries to 2 houses

    AoC2015Day3 day3;

    string inputString1 = ">";
    string inputString2 = "^>v<";
    string inputString3 = "^v^v^v^v^v";
    string inputStringBadInput = "Bad Input";

    unsigned int expectedHousesVisited;
    unsigned int actualHousesVisited;
    unsigned int expectedPresentsDelivered;
    unsigned int actualPresentsDelivered;

    // No input, no calc Check
    expectedHousesVisited = 1;
    expectedPresentsDelivered = 1;

    actualHousesVisited = day3.getTotalHousesVisited();
    actualPresentsDelivered = day3.getTotalDeliveries();

    TEST_ASSERT_EQUAL(expectedHousesVisited, actualHousesVisited);
    TEST_ASSERT_EQUAL(expectedPresentsDelivered, actualPresentsDelivered);

    // Good input Check
    expectedHousesVisited = 2;
    expectedPresentsDelivered = 2;

    day3.deliveryDirections(inputString1);

    actualHousesVisited = day3.getTotalHousesVisited();
    actualPresentsDelivered = day3.getTotalDeliveries();

    day3.reset();

    TEST_ASSERT_EQUAL(expectedHousesVisited, actualHousesVisited);
    TEST_ASSERT_EQUAL(expectedPresentsDelivered, actualPresentsDelivered);

    expectedHousesVisited = 4;
    expectedPresentsDelivered = 5;

    day3.deliveryDirections(inputString2);

    actualHousesVisited = day3.getTotalHousesVisited();
    actualPresentsDelivered = day3.getTotalDeliveries();

    day3.reset();

    TEST_ASSERT_EQUAL(expectedHousesVisited, actualHousesVisited);
    TEST_ASSERT_EQUAL(expectedPresentsDelivered, actualPresentsDelivered);

    expectedHousesVisited = 2;
    expectedPresentsDelivered = 11;

    day3.deliveryDirections(inputString3);

    actualHousesVisited = day3.getTotalHousesVisited();
    actualPresentsDelivered = day3.getTotalDeliveries();

    day3.reset();

    TEST_ASSERT_EQUAL(expectedHousesVisited, actualHousesVisited);
    TEST_ASSERT_EQUAL(expectedPresentsDelivered, actualPresentsDelivered);


    // Bad input Check

    expectedHousesVisited = 1;
    expectedPresentsDelivered = 1;

    day3.deliveryDirections(inputStringBadInput);

    actualHousesVisited = day3.getTotalHousesVisited();
    actualPresentsDelivered = day3.getTotalDeliveries();

    TEST_ASSERT_EQUAL(expectedHousesVisited, actualHousesVisited);
    TEST_ASSERT_EQUAL(expectedPresentsDelivered, actualPresentsDelivered);


}

void test_aoc_day3_input_file() {

    // Test using the original input file with expected correct answers for Day 3

    AoC2015Day3 day3;

    string inputString;

    ifstream inputFile;
    string inputFileName = {"./input_data/2015/day3_input.txt"};
    inputFile.open(inputFileName);

    if (inputFile.is_open()) {
        while (getline(inputFile, inputString)) {

        }
    }

    inputFile.close();
}

/** ***************************************** Private Function Definitions *********************************************/

/** ***************************************** Amalgamation of Test Cases **********************************************/

void test_aoc2015_day3(bool printTest) {
    if (!printTest) {
        RUN_TEST(test_aoc_day3_basic_input);
        RUN_TEST(test_aoc_day3_input_file);
    } else {
        printf("%s\n", "test_aoc_day3_basic_input");
        printf("%s\n", "test_aoc_day3_input_file");
    }
}

