/** ***************************************** Includes ****************************************************************/

#include "unity.h"
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include "aoc_2015_day1.hpp"

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

    string inputStringsFloor0[2] = {"(())", "()()"};
    string inputStringsFloor3[3] = {"(((", "(()(()(", "))((((("};
    string inputStringsFloorMinus1[2] = {"())", "))("};
    string inputStringsFloorMinus3[2] = {")))", ")())())"};
    string inputStringInvalid = {"This is a string full of junk characters that will be ignored"};

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

    try {
        day1.findFloor(inputStringInvalid);
        TEST_ASSERT(false);
    } catch (InvalidCharacter& e){
        std::cout << "MyException caught" << std::endl;
        std::cout << e.what() << std::endl;

        TEST_ASSERT(aoc2015Day1ExceptionToString(INVALID_CHARACTER) == e.what());
    }
}

void test_aoc_day1_basic_input_basement() {

    //  ( is position 1 as the result should be 1 indexed and not 0 indexed.
    //  ()()) should be 5.

    AoC2015Day1 day1;

    int expectedBasementPos;
    int actualBasementPos;

    string inputBasementPos1 = {")"};
    string inputBasementPos5 = {"()())"};
    string inputBasementPos0 = {"("};

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

    expectedBasementPos = 0;
    day1.findFloor(inputBasementPos0);
    actualBasementPos = day1.getBasementPosition();
    TEST_ASSERT_EQUAL(expectedBasementPos, actualBasementPos);
    day1.reset();
}


void test_aoc_day1_input_file() {

    // Test using the original input file with expected correct answers for Day 1

    AoC2015Day1 day1;

    string inputString;

    ifstream inputFile;
    string inputFileName = {"./input_data/2015/day1_input.txt"};
    inputFile.open(inputFileName);

    int expectedFloor = 232;
    int actualFloor = 0;
    int expectedBasementPosition = 1783;
    int actualBasementPosition;

    if (inputFile.is_open()) {
        inputFile >> inputString;

        actualFloor = day1.findFloor(inputString);
    }
    actualBasementPosition = day1.getBasementPosition();

    inputFile.close();

    TEST_ASSERT_EQUAL(expectedFloor, actualFloor);
    TEST_ASSERT_EQUAL(expectedBasementPosition, actualBasementPosition);
}

/** ***************************************** Private Function Definitions *********************************************/

/** ***************************************** Amalgamation of Test Cases **********************************************/

void test_aoc2015_day1(bool printTest) {
    if (!printTest) {
        RUN_TEST(test_aoc_day1_basic_input_floor);
        RUN_TEST(test_aoc_day1_basic_input_basement);
        RUN_TEST(test_aoc_day1_input_file);
    } else {
        printf("%s\n", "test_aoc_day1_basic_input_floor");
        printf("%s\n", "test_aoc_day1_basic_input_basement");
        printf("%s\n", "test_aoc_day1_input_file");
    }
}

