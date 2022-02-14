/** ***************************************** Includes ****************************************************************/

#include "unity.h"
#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include "aoc_2015_day5.hpp"

using namespace std;

/** ***************************************** Global Variables ********************************************************/

/** ***************************************** Private Function Declarations *******************************************/

/** ***************************************** Test Cases **************************************************************/

void test_aoc_day5_basic_input() {

    // ugknbfddgicrmopn is nice because it has at least three vowels (u...i...o...), a double letter (...dd...),
    //     and none of the disallowed substrings.
    // aaa is nice because it has at least three vowels and a double letter, even though the letters used by different
    //     rules overlap.
    // jchzalrnumimnmhp is naughty because it has no double letter.
    // haegwjzuvuyypxyu is naughty because it contains the string xy.
    // dvszwmarrgswjxmb is naughty because it contains only one vowel.


    AoC2015Day5 day5;

    pair<string, behaviour> inputStringsToExpectedBehaviours[5] = {{"ugknbfddgicrmopn", NICE},
                                                                   {"aaa", NICE},
                                                                   {"jchzalrnumimnmhp", NAUGHTY},
                                                                   {"haegwjzuvuyypxyu", NAUGHTY},
                                                                   {"dvszwmarrgswjxmb", NAUGHTY}};
    behaviour actualBehaviour;

    for(const pair<string, behaviour>& pInputOutputPair: inputStringsToExpectedBehaviours) {
        actualBehaviour = day5.checkNaughtyOrNiceV1(pInputOutputPair.first);
        day5.reset();
        TEST_ASSERT_EQUAL(pInputOutputPair.second, actualBehaviour);
    }
}

void test_aoc_day5_p2_basic_input() {
    // qjhvhtzxzqqjkmpb is nice because is has a pair that appears twice (qj) and a letter that repeats with exactly
    //     one letter between them (zxz).
    // xxyxx is nice because it has a pair that appears twice and a letter that repeats with one between, even though
    //     the letters used by each rule overlap.
    // uurcxstgmygtbstg is naughty because it has a pair (tg) but no repeat with a single letter between them.
    // ieodomkazucvgmuy is naughty because it has a repeating letter with one between (odo), but no pair that appears twice.


    AoC2015Day5 day5;

    pair<string, behaviour> inputStringsToExpectedBehaviours[4] = {{"qjhvhtzxzqqjkmpb", NICE},
                                                                   {"xxyxx", NICE},
                                                                   {"uurcxstgmygtbstg", NAUGHTY},
                                                                   {"ieodomkazucvgmuy", NAUGHTY}};
    behaviour actualBehaviour;

    for(const pair<string, behaviour>& pInputOutputPair: inputStringsToExpectedBehaviours) {
        actualBehaviour = day5.checkNaughtyOrNiceV2(pInputOutputPair.first);
        day5.reset();
        TEST_ASSERT_EQUAL(pInputOutputPair.second, actualBehaviour);
    }
}

void test_aoc_day5_input_file() {

    // Test using the original input file with expected correct answers for Day 5

    AoC2015Day5 day5;

    string inputString;
    ifstream inputFile;
    uint32_t expectedNiceCount = 238;
    uint32_t actualNiceCount;

    string inputFileName = {"./input_data/2015/day5_input.txt"};
    inputFile.open(inputFileName);

    if (inputFile.is_open()) {
        while (getline(inputFile, inputString)) {
            day5.checkNaughtyOrNiceV1(inputString);
        }
    }

    actualNiceCount = day5.getNiceCount();
    TEST_ASSERT_EQUAL(expectedNiceCount, actualNiceCount);

    inputFile.close();
}

void test_aoc_day5_p2_input_file() {

    // Test using the original input file with expected correct answers for Day 5

    AoC2015Day5 day5;

    string inputString;
    ifstream inputFile;
    uint32_t expectedNiceCount = 69;
    uint32_t actualNiceCount;

    string inputFileName = {"./input_data/2015/day5_input.txt"};
    inputFile.open(inputFileName);

    if (inputFile.is_open()) {
        while (getline(inputFile, inputString)) {
            day5.checkNaughtyOrNiceV2(inputString);
        }
    }

    actualNiceCount = day5.getNiceCount();
    TEST_ASSERT_EQUAL(expectedNiceCount, actualNiceCount);

    inputFile.close();
}


/** ***************************************** Private Function Definitions *********************************************/

/** ***************************************** Amalgamation of Test Cases **********************************************/

void test_aoc2015_day5(bool printTest) {
    if (!printTest) {
        RUN_TEST(test_aoc_day5_basic_input);
        RUN_TEST(test_aoc_day5_p2_basic_input);
        RUN_TEST(test_aoc_day5_input_file);
        RUN_TEST(test_aoc_day5_p2_input_file);
    } else {
        printf("%s\n", "test_aoc_day5_basic_input");
        printf("%s\n", "test_aoc_day5_p2_basic_input");
        printf("%s\n", "test_aoc_day5_input_file");
        printf("%s\n", "test_aoc_day5_p2_input_file");
    }
}

