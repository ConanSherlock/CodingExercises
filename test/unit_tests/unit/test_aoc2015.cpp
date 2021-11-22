/** ***************************************** Includes ****************************************************************/

#include "unity.h"
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include "aoc_2015.hpp"
#include "day1.hpp"

using namespace aoc_2015;
using namespace std;

/** ***************************************** Global Variables ********************************************************/

/** ***************************************** Private Function Declarations *******************************************/

/** ***************************************** Test Cases **************************************************************/

void test_aoc_day1_basic_input()
{

    //  (()) and ()() both result in floor 0.
    //  ((( and (()(()( both result in floor 3.
    //  ))((((( also results in floor 3.
    //  ()) and ))( both result in floor -1 (the first basement level).
    //  ))) and )())()) both result in floor -3.

    AoC2015Day1 day1;     // Create an object of MyClass

    int expectedFloor;
    int actualFloor;

    std::string inputStringsFloor0[2] = {"(())", "()()"};
    std::string inputStringsFloor3[3] = {"(((", "(()(()(", "))((((("};
    std::string inputStringsFloorMinus1[2] = {"())", "))("};
    std::string inputStringsFloorMinus3[2] = {")))", ")())())"};

    expectedFloor = 0;
    for(auto & i : inputStringsFloor0) {
        actualFloor = day1.findFloor(i);
        TEST_ASSERT_EQUAL(expectedFloor, actualFloor);
        day1.reset();
    }

    expectedFloor = 3;
    for(auto & i : inputStringsFloor3) {
        actualFloor = day1.findFloor(i);
        TEST_ASSERT_EQUAL(expectedFloor, actualFloor);
        day1.reset();
    }

    expectedFloor = -1;
    for(auto & i : inputStringsFloorMinus1) {
        actualFloor = day1.findFloor(i);
        TEST_ASSERT_EQUAL(expectedFloor, actualFloor);
        day1.reset();
    }

    expectedFloor = -3;
    for(auto & i : inputStringsFloorMinus3) {
        actualFloor = day1.findFloor(i);
        TEST_ASSERT_EQUAL(expectedFloor, actualFloor);
        day1.reset();
    }

}

void test_aoc_day1_input_file()
{
    AoC2015Day1 day1;     // Create an object of MyClass

    std::string inputString;
    std::ifstream inputFile;
    inputFile.open(R"(..\test\input_data\2015\day1_input.txt)");

    int expectedFloor = 232;
    int actualFloor = 0;

    if ( inputFile.is_open() ) {
        inputFile >> inputString;

        actualFloor = day1.findFloor(inputString);
    }

    TEST_ASSERT_EQUAL(expectedFloor, actualFloor);

}

/** ***************************************** Private Function Definitions *********************************************/

/** ***************************************** Amalgamation of Test Cases **********************************************/

void test_aoc2015(bool printTest){
  if(!printTest)
  {
    RUN_TEST(test_aoc_day1_basic_input);
    RUN_TEST(test_aoc_day1_input_file);
  } else {
    printf("%s\n", "test_aoc_day1_basic_input");
    printf("%s\n", "test_aoc_day1_input_file");
  }
}

