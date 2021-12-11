/** ***************************************** Includes ****************************************************************/

#include "unity.h"
#include <fstream>
#include <string>
#include "aoc_2015_day3.hpp"

using namespace std;

/** ***************************************** Global Variables ********************************************************/

/** ***************************************** Private Function Declarations *******************************************/

/** ***************************************** Test Cases **************************************************************/

void test_aoc_day3_basic_input_solo_santa() {

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

void test_aoc_day3_basic_input_with_robo_santa() {

    //  Present Delivery to unique houses
    //  > => 2 deliveries to 2 houses
    //  ^>v< => 5 deliveries to 4 houses
    //  ^v^v^v^v^v => 11 deliveries to 2 houses

    AoC2015Day3 day3;

    string inputString1 = "^v";
    string inputString2 = "^>v<";
    string inputString3 = "^v^v^v^v^v";
    string inputStringBadInput = "Bad Input";

    unsigned int expectedHousesVisited;
    unsigned int actualHousesVisited;
    unsigned int expectedPresentsDelivered;
    unsigned int actualPresentsDelivered;

    // No input, no calc Check
    expectedHousesVisited = 1;
    expectedPresentsDelivered = 2;

    day3.activateRobot();
    actualHousesVisited = day3.getTotalHousesVisited();
    actualPresentsDelivered = day3.getTotalDeliveries();

    TEST_ASSERT_EQUAL(expectedHousesVisited, actualHousesVisited);
    TEST_ASSERT_EQUAL(expectedPresentsDelivered, actualPresentsDelivered);

    // Good input Check
    expectedHousesVisited = 3;
    expectedPresentsDelivered = 4;

    day3.deliveryDirections(inputString1);

    actualHousesVisited = day3.getTotalHousesVisited();
    actualPresentsDelivered = day3.getTotalDeliveries();

    day3.reset();
    day3.activateRobot();

    TEST_ASSERT_EQUAL(expectedHousesVisited, actualHousesVisited);
    TEST_ASSERT_EQUAL(expectedPresentsDelivered, actualPresentsDelivered);

    expectedHousesVisited = 3;
    expectedPresentsDelivered = 6;

    day3.deliveryDirections(inputString2);

    actualHousesVisited = day3.getTotalHousesVisited();
    actualPresentsDelivered = day3.getTotalDeliveries();

    day3.reset();
    day3.activateRobot();

    TEST_ASSERT_EQUAL(expectedHousesVisited, actualHousesVisited);
    TEST_ASSERT_EQUAL(expectedPresentsDelivered, actualPresentsDelivered);

    expectedHousesVisited = 11;
    expectedPresentsDelivered = 12;

    day3.deliveryDirections(inputString3);

    actualHousesVisited = day3.getTotalHousesVisited();
    actualPresentsDelivered = day3.getTotalDeliveries();

    day3.reset();
    day3.activateRobot();

    TEST_ASSERT_EQUAL(expectedHousesVisited, actualHousesVisited);
    TEST_ASSERT_EQUAL(expectedPresentsDelivered, actualPresentsDelivered);


    // Bad input Check

    expectedHousesVisited = 1;
    expectedPresentsDelivered = 2;

    day3.deliveryDirections(inputStringBadInput);

    actualHousesVisited = day3.getTotalHousesVisited();
    actualPresentsDelivered = day3.getTotalDeliveries();

    TEST_ASSERT_EQUAL(expectedHousesVisited, actualHousesVisited);
    TEST_ASSERT_EQUAL(expectedPresentsDelivered, actualPresentsDelivered);

    // Test robo activation and deactivation

    day3.reset();

    expectedHousesVisited = 1;
    expectedPresentsDelivered = 1;

    actualHousesVisited = day3.getTotalHousesVisited();
    actualPresentsDelivered = day3.getTotalDeliveries();

    TEST_ASSERT_EQUAL(expectedHousesVisited, actualHousesVisited);
    TEST_ASSERT_EQUAL(expectedPresentsDelivered, actualPresentsDelivered);

    expectedPresentsDelivered = 2;

    day3.activateRobot();

    actualHousesVisited = day3.getTotalHousesVisited();
    actualPresentsDelivered = day3.getTotalDeliveries();

    TEST_ASSERT_EQUAL(expectedHousesVisited, actualHousesVisited);
    TEST_ASSERT_EQUAL(expectedPresentsDelivered, actualPresentsDelivered);

    day3.deactivateRobot();

    actualHousesVisited = day3.getTotalHousesVisited();
    actualPresentsDelivered = day3.getTotalDeliveries();

    TEST_ASSERT_EQUAL(expectedHousesVisited, actualHousesVisited);
    TEST_ASSERT_EQUAL(expectedPresentsDelivered, actualPresentsDelivered);

    day3.activateRobot();

    expectedPresentsDelivered = 3;

    actualHousesVisited = day3.getTotalHousesVisited();
    actualPresentsDelivered = day3.getTotalDeliveries();

    TEST_ASSERT_EQUAL(expectedHousesVisited, actualHousesVisited);
    TEST_ASSERT_EQUAL(expectedPresentsDelivered, actualPresentsDelivered);
}

void test_aoc_day3_input_file_solo_santa() {

    // Test using the original input file with expected correct answers for Day 3

    AoC2015Day3 day3;

    string inputString;

    unsigned int expectedHousesVisited = 2081;
    unsigned int actualHousesVisited = -1;
    unsigned int expectedPresentsDelivered = 8193;
    unsigned int actualPresentsDelivered = -1;


    ifstream inputFile;
    string inputFileName = {"./input_data/2015/day3_input.txt"};
    inputFile.open(inputFileName);

    if (inputFile.is_open()) {
        while (getline(inputFile, inputString)) {
            day3.deliveryDirections(inputString);
        }

        actualHousesVisited = day3.getTotalHousesVisited();
        actualPresentsDelivered = day3.getTotalDeliveries();
    }

    inputFile.close();

    TEST_ASSERT_EQUAL(expectedHousesVisited, actualHousesVisited);
    TEST_ASSERT_EQUAL(expectedPresentsDelivered, actualPresentsDelivered);
}

void test_aoc_day3_input_file_with_robo_santa() {

    // Test using the original input file with expected correct answers for Day 3

    AoC2015Day3 day3;

    string inputString;

    unsigned int expectedHousesVisited = 2341;
    unsigned int actualHousesVisited = -1;
    unsigned int expectedPresentsDelivered = 8194;
    unsigned int actualPresentsDelivered = -1;


    ifstream inputFile;
    string inputFileName = {"./input_data/2015/day3_input.txt"};
    inputFile.open(inputFileName);

    day3.activateRobot();

    if (inputFile.is_open()) {
        while (getline(inputFile, inputString)) {
            day3.deliveryDirections(inputString);
        }

        actualHousesVisited = day3.getTotalHousesVisited();
        actualPresentsDelivered = day3.getTotalDeliveries();
    }

    inputFile.close();

    TEST_ASSERT_EQUAL(expectedHousesVisited, actualHousesVisited);
    TEST_ASSERT_EQUAL(expectedPresentsDelivered, actualPresentsDelivered);
}

/** ***************************************** Private Function Definitions *********************************************/

/** ***************************************** Amalgamation of Test Cases **********************************************/

void test_aoc2015_day3(bool printTest) {
    if (!printTest) {
        RUN_TEST(test_aoc_day3_basic_input_solo_santa);
        RUN_TEST(test_aoc_day3_basic_input_with_robo_santa);
        RUN_TEST(test_aoc_day3_input_file_solo_santa);
        RUN_TEST(test_aoc_day3_input_file_with_robo_santa);
    } else {
        printf("%s\n", "test_aoc_day3_basic_input_solo_santa");
        printf("%s\n", "test_aoc_day3_basic_input_with_robo_santa");
        printf("%s\n", "test_aoc_day3_input_file_solo_santa");
        printf("%s\n", "test_aoc_day3_input_file_with_robo_santa");
    }
}

