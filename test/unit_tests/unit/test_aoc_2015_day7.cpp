/** ***************************************** Includes ****************************************************************/

#include "unity.h"
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include "aoc_2015_day7.hpp"

using namespace std;

/** ***************************************** Global Variables ********************************************************/

/** ***************************************** Private Function Declarations *******************************************/

/** ***************************************** Test Cases **************************************************************/

void test_aoc_day7_basic_input() {

    //  The following circuit
    //  123 -> x
    //  456 -> y
    //  x AND y -> d
    //  x OR y -> e
    //  x LSHIFT 2 -> f
    //  y RSHIFT 2 -> g
    //  NOT x -> h
    //  NOT y -> i
    //
    //  will the following values for the wires
    //
    //  d: 72
    //  e: 507
    //  f: 492
    //  g: 114
    //  h: 65412
    //  i: 65079
    //  x: 123
    //  y: 456

    AoC2015Day7 day7;

    istringstream inputString("123 -> x\n"
                              "456 -> y\n"
                              "x AND y -> d\n"
                              "x OR y -> e\n"
                              "x LSHIFT 2 -> f\n"
                              "y RSHIFT 2 -> g\n"
                              "NOT x -> h\n"
                              "NOT y -> i");
    string line;

    // Good input Check
    multimap<string, int> expectedValues;
    expectedValues.insert({"d", 72});
    expectedValues.insert({"e", 507});
    expectedValues.insert({"f", 492});
    expectedValues.insert({"g", 114});
    expectedValues.insert({"h", 65412});
    expectedValues.insert({"i", 65079});
    expectedValues.insert({"x", 123});
    expectedValues.insert({"y", 456});

    multimap<string, int> actualValues;

    while (std::getline(inputString, line)) {
        day7.buildCircuit(line);
    }

    day7.evaluateCircuit();
//    TEST_ASSERT_EQUAL(expectedIntCode, actualIntCode);
    day7.reset();
//
//    expectedIntCode = 1048970;
//    actualIntCode = day4.md5LeadingZeroes(inputString2, 5);
//    TEST_ASSERT_EQUAL(expectedIntCode, actualIntCode);

}

void test_aoc_day7_input_file() {

    // Test using the original input file with expected correct answers for Day 7

    AoC2015Day7 day7;

    string inputString;
    ifstream inputFile;

    string inputFileName = {"./input_data/2015/day7_input.txt"};
    inputFile.open(inputFileName);

    int expectedIntCode1 = 346386;
    int expectedIntCode2 = 9958218;
    int actualIntCode;

    stringstream fileContent;

    if (inputFile.is_open()) {
        while (getline(inputFile, inputString)) {
            day7.buildCircuit(inputString);
        }
        day7.evaluateCircuit();
    }

    inputFile.close();
}

/** ***************************************** Private Function Definitions *********************************************/

/** ***************************************** Amalgamation of Test Cases **********************************************/

void test_aoc2015_day7(bool printTest) {
    if (!printTest) {
        RUN_TEST(test_aoc_day7_basic_input);
        RUN_TEST(test_aoc_day7_input_file);
    } else {
        printf("%s\n", "test_aoc_day7_basic_input");
        printf("%s\n", "test_aoc_day7_input_file");
    }
}

