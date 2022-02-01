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

    istringstream goodInputString("123 -> x\n"
                                  "456 -> y\n"
                                  "x AND y -> d\n"
                                  "x OR y -> e\n"
                                  "x LSHIFT 2 -> f\n"
                                  "y RSHIFT 2 -> g\n"
                                  "NOT x -> h\n"
                                  "NOT y -> i");

    istringstream badInputString("0 -> x\n"
                                 "0 -> x\n"
                                 "x jhlk -> d\n"
                                 "x asd -> e\n"
                                 "asdsaf -> f\n"
                                 "asdsaf asdasfasf asdasfsaf -> k\n"
                                 "y RSHIFT 2 g\n"
                                 "NOT y i");
    string line;

    // Good input Check
    multimap<string, int> expectedValues;
    expectedValues.insert({"d", (uint16_t)72});
    expectedValues.insert({"e", (uint16_t)507});
    expectedValues.insert({"f", (uint16_t)492});
    expectedValues.insert({"g", (uint16_t)114});
    expectedValues.insert({"h", (uint16_t)65412});
    expectedValues.insert({"i", (uint16_t)65079});
    expectedValues.insert({"x", (uint16_t)123});
    expectedValues.insert({"y", (uint16_t)456});

    multimap<string, wireInfo> actualMap;
    multimap<string, wireInfo> actualBadMap;

    multimap<string, int> actualValues;

    while (std::getline(goodInputString, line)) {
        day7.buildCircuit(line);
    }

    day7.evaluateCircuit();
    actualMap = day7.getCircuitMap();

    auto expectedIter = expectedValues.begin();

    for (auto iter = actualMap.begin(); iter != actualMap.end(); iter++){
        TEST_ASSERT_EQUAL(expectedIter->second, iter->second.value);
        expectedIter++;
    }

    day7.reset();

    // Bad input Check

    multimap<string, int> badExpectedValues;
    badExpectedValues.insert({"d", (uint16_t)0});
    badExpectedValues.insert({"e", (uint16_t)0});
    badExpectedValues.insert({"f", (uint16_t)0});
    badExpectedValues.insert({"k", (uint16_t)0});
    badExpectedValues.insert({"x", (uint16_t)0});

    while (std::getline(badInputString, line)) {
        day7.buildCircuit(line);
    }

    day7.evaluateCircuit();
    actualBadMap = day7.getCircuitMap();

    expectedIter = badExpectedValues.begin();

    for (auto iter = actualBadMap.begin(); iter != actualBadMap.end(); iter++){
        TEST_ASSERT_EQUAL(expectedIter->second, iter->second.value);
        expectedIter++;
    }

}

void test_aoc_day7_input_file() {

    // Test using the original input file with expected correct answers for Day 7

    AoC2015Day7 day7;

    string inputString;
    ifstream inputFile;
    multimap<string, wireInfo> circuitMap1;
    multimap<string, wireInfo> circuitMap2;
    string expectedKey = "a";
    uint16_t expectedValue1 = 16076;
    uint16_t expectedValue2 = 2797;
    uint16_t actualValue = 0;
    string keyToChange = "b";
    wireInfo newInfo;
    newInfo.equation = to_string(16076);
    newInfo.evaluated = false;
    newInfo.value = 0;

    string inputFileName = {"./input_data/2015/day7_input.txt"};
    inputFile.open(inputFileName);

    if (inputFile.is_open()) {
        while (getline(inputFile, inputString)) {
            day7.buildCircuit(inputString);
        }
        day7.evaluateCircuit();
    }

    circuitMap1 = day7.getCircuitMap();

    for (auto & entry : circuitMap1) {
        if(expectedKey == entry.first){
            actualValue = entry.second.value;
            break;
        }
    }

    TEST_ASSERT_EQUAL(expectedValue1, actualValue);

    day7.reset();

    inputFile.clear();
    inputFile.seekg(0, std::ifstream::beg);

    if (inputFile.is_open()) {
        while (getline(inputFile, inputString)) {
            day7.buildCircuit(inputString);
        }
    }

    day7.changeWireInfo(keyToChange, newInfo);

    day7.evaluateCircuit();

    circuitMap2 = day7.getCircuitMap();

    actualValue = 0;

    for (auto & entry : circuitMap2) {
        if(expectedKey == entry.first){
            actualValue = entry.second.value;
            break;
        }
    }

    TEST_ASSERT_EQUAL(expectedValue2, actualValue);

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

