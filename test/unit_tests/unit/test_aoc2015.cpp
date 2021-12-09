/** ***************************************** Includes ****************************************************************/

#include "unity.h"
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include "aoc15day1.hpp"

using namespace std;

/** ***************************************** Global Variables ********************************************************/

/** ***************************************** Private Function Declarations *******************************************/

/** ***************************************** Test Cases **************************************************************/

void test_aoc_day1_basic_input_floor() {

    //  (()) and ()() both result in floor 0.
    //  ((( and (()(()( both result in floor 3.
    //  ))((((( also results in floor 3.
    //  ()) and ))( both result in floor -1 (the first basement level).
    //  ))) and )())()) both result in floor -3.

    AoC2015Day1 day1;

    int expectedFloor;
    int actualFloor;

    std::string inputStringsFloor0[2] = {"(())", "()()"};
    std::string inputStringsFloor3[3] = {"(((", "(()(()(", "))((((("};
    std::string inputStringsFloorMinus1[2] = {"())", "))("};
    std::string inputStringsFloorMinus3[2] = {")))", ")())())"};

    expectedFloor = 0;
    for (auto &i: inputStringsFloor0) {
        actualFloor = day1.findFloor(i);
        TEST_ASSERT_EQUAL(expectedFloor, actualFloor);
        day1.reset();
    }

    expectedFloor = 3;
    for (auto &i: inputStringsFloor3) {
        actualFloor = day1.findFloor(i);
        TEST_ASSERT_EQUAL(expectedFloor, actualFloor);
        day1.reset();
    }

    expectedFloor = -1;
    for (auto &i: inputStringsFloorMinus1) {
        actualFloor = day1.findFloor(i);
        TEST_ASSERT_EQUAL(expectedFloor, actualFloor);
        day1.reset();
    }

    expectedFloor = -3;
    for (auto &i: inputStringsFloorMinus3) {
        actualFloor = day1.findFloor(i);
        TEST_ASSERT_EQUAL(expectedFloor, actualFloor);
        day1.reset();
    }
}

void test_aoc_day1_basic_input_basement() {

    //  ( is position 1 as the result should be 1 indexed and not 0 indexed.
    //  ()()) should be 5.

    AoC2015Day1 day1;

    int expectedBasementPos;
    int actualBasementPos;

    std::string inputBasementPos1 = {")"};
    std::string inputBasementPos5 = {"()())"};

    expectedBasementPos = 1;

    day1.findFloor(inputBasementPos1);
    actualBasementPos = day1.getBasementPosition();
    TEST_ASSERT_EQUAL(expectedBasementPos, actualBasementPos);
    day1.reset();

    expectedBasementPos = 5;
    day1.findFloor(inputBasementPos5);
    actualBasementPos = day1.getBasementPosition();
    TEST_ASSERT_EQUAL(expectedBasementPos, actualBasementPos);
    day1.reset();
}


void test_aoc_day1_input_file() {
    //

    AoC2015Day1 day1;

    std::string inputString;
    std::ifstream inputFile;
    inputFile.open(R"(..\test\input_data\2015\day1_input.txt)");

    int expectedFloor = 232;
    int actualFloor = 0;
    int expectedBasementPosition = 1783;
    int actualBasementPosition;

    if (inputFile.is_open()) {
        inputFile >> inputString;

        actualFloor = day1.findFloor(inputString);
    }

    cout << "Floor: " << actualFloor << "\n";

    actualBasementPosition = day1.getBasementPosition();

    cout << "Basement Position: " << actualBasementPosition << "\n";

    TEST_ASSERT_EQUAL(expectedFloor, actualFloor);
    TEST_ASSERT_EQUAL(expectedBasementPosition, actualBasementPosition);
}

/** ***************************************** Private Function Definitions *********************************************/

/** ***************************************** Amalgamation of Test Cases **********************************************/

void test_aoc2015(bool printTest) {
    if (!printTest) {
        RUN_TEST(test_aoc_day1_basic_input_floor);
        RUN_TEST(test_aoc_day1_input_file);
        RUN_TEST(test_aoc_day1_basic_input_basement);
    } else {
        printf("%s\n", "test_aoc_day1_basic_input_floor");
        printf("%s\n", "test_aoc_day1_input_file");
        printf("%s\n", "test_aoc_day1_basic_input_basement");
    }
}

