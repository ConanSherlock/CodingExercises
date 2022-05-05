/** ***************************************** Includes ****************************************************************/

#include "unity.h"
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include "aoc_2015_day8.hpp"

using namespace std;



/** ***************************************** Global Variables ********************************************************/

/** ***************************************** Private Function Declarations *******************************************/

/** ***************************************** Test Cases **************************************************************/

void test_aoc_day8_basic_input() {

//    Inputs
//    "" is 2 characters of code (the two double quotes), but the string contains zero characters.
//    "abc" is 5 characters of code, but 3 characters in the string data.
//    "aaa\"aaa" is 10 characters of code, but the string itself contains six "a" characters and a single, escaped quote character, for a total of 7 characters in the string data.
//    "\x27" is 6 characters of code, but the string itself contains just one - an apostrophe ('), escaped using hexadecimal notation.

//    Given the four strings above,
//    the total number of characters of string code (2 + 5 + 10 + 6 = 23) minus the
//    total number of characters in memory for string values (0 + 3 + 7 + 1 = 11) is 23 - 11 = 12.


    AoC2015Day8 day8;

    string goodInputStrings[4] = {R"("")", R"("abc")", R"("aaa\"aaa")", R"("\x27")"};
    uint32_t expectedCharsInString[4] = {2,5,10,6};
    uint32_t expectedCharsInMem[4] = {0,3,7,1};
    uint32_t actualCharsInMem;
    uint32_t actualCharsInString;
    uint32_t sumCharsInMem = 0;
    uint32_t sumCharsInString = 0;
    uint32_t expectedSumCharsInString = 23;
    uint32_t expectedSumCharsInMem = 11;

    string line;

    // Good input Check
    for (unsigned int i=0; i<sizeof(goodInputStrings)/sizeof(string); ++i) {
        day8.evaluateString(goodInputStrings[i]);
        actualCharsInString = day8.getCharsStringCode();
        actualCharsInMem = day8.getCharsInMem();
        TEST_ASSERT_EQUAL(expectedCharsInMem[i], actualCharsInMem);
        TEST_ASSERT_EQUAL(expectedCharsInString[i], actualCharsInString);
        sumCharsInMem += actualCharsInMem;
        sumCharsInString += actualCharsInString;
    }

    TEST_ASSERT_EQUAL(expectedSumCharsInMem, sumCharsInMem);
    TEST_ASSERT_EQUAL(expectedSumCharsInString, sumCharsInString);
}

void test_aoc_day8_basic_input_p2() {

//    Inputs
//    "" is 2 characters of code (the two double quotes), but the string contains zero characters.
//    "abc" is 5 characters of code, but 3 characters in the string data.
//    "aaa\"aaa" is 10 characters of code, but the string itself contains six "a" characters and a single, escaped quote character, for a total of 7 characters in the string data.
//    "\x27" is 6 characters of code, but the string itself contains just one - an apostrophe ('), escaped using hexadecimal notation.

//    Given the four strings above,
//    the total number of characters of string code (2 + 5 + 10 + 6 = 23) minus the
//    total number of characters in memory for string values (0 + 3 + 7 + 1 = 11) is 23 - 11 = 12.


    AoC2015Day8 day8;

    string goodInputStrings[4] = {R"("")", R"("abc")", R"("aaa\"aaa")", R"("\x27")"};
    uint32_t expectedCharsInString[4] = {6,9,16,11};
    uint32_t expectedCharsInMem[4] = {0,3,7,1};
    uint32_t actualCharsInMem;
    uint32_t actualCharsInString;
    uint32_t sumCharsInMem = 0;
    uint32_t sumCharsInString = 0;
    uint32_t expectedSumCharsInString = 42;
    uint32_t expectedSumCharsInMem = 11;

    string line;

    // Good input Check
    for (unsigned int i=0; i<sizeof(goodInputStrings)/sizeof(string); ++i) {
        day8.reset();
        day8.evaluateEncodedString(goodInputStrings[i]);
        actualCharsInString = day8.getCharsStringCode();
        actualCharsInMem = day8.getCharsInMem();
        TEST_ASSERT_EQUAL(expectedCharsInMem[i], actualCharsInMem);
        TEST_ASSERT_EQUAL(expectedCharsInString[i], actualCharsInString);
        sumCharsInMem += actualCharsInMem;
        sumCharsInString += actualCharsInString;
    }

    TEST_ASSERT_EQUAL(expectedSumCharsInMem, sumCharsInMem);
    TEST_ASSERT_EQUAL(expectedSumCharsInString, sumCharsInString);
}

void test_aoc_day8_input_file() {

    // Test using the original input file with expected correct answers for Day 8
    string inputString;

    ifstream inputFile;
    string inputFileName = {"./input_data/2015/day8_input.txt"};
    inputFile.open(inputFileName);
    uint32_t charsInMem;
    uint32_t charsInString;
    uint32_t sumCharsInMem = 0;
    uint32_t sumCharsInStringCode = 0;
    uint32_t actualDiffCharsTotal;
    uint32_t expectedDiffCharsTotal = 1350;

    AoC2015Day8 day8;

    if (inputFile.is_open()) {
        while (getline(inputFile, inputString)) {
            day8.evaluateString(inputString);
            charsInString = day8.getCharsStringCode();
            charsInMem = day8.getCharsInMem();
            sumCharsInMem += charsInMem;
            sumCharsInStringCode += charsInString;
        }
    }

    actualDiffCharsTotal = sumCharsInStringCode - sumCharsInMem;

    TEST_ASSERT_EQUAL(expectedDiffCharsTotal, actualDiffCharsTotal);

    inputFile.close();

}

void test_aoc_day8_input_file_p2() {

    // Test using the original input file with expected correct answers for Day 8
    string inputString;

    ifstream inputFile;
    string inputFileName = {"./input_data/2015/day8_input.txt"};
    inputFile.open(inputFileName);
    uint32_t charsInString;
    uint32_t charsInEncodedString;
    uint32_t sumCharsInStringCode = 0;
    uint32_t sumCharsInEncodedStringCode = 0;
    uint32_t actualDiffCharsTotal;
    uint32_t expectedDiffCharsTotal = 2085;

    AoC2015Day8 day8;

    if (inputFile.is_open()) {
        while (getline(inputFile, inputString)) {
            day8.evaluateString(inputString);
            charsInString = day8.getCharsStringCode();
            sumCharsInStringCode += charsInString;

            day8.reset();

            day8.evaluateEncodedString(inputString);
            charsInEncodedString = day8.getCharsStringCode();
            sumCharsInEncodedStringCode += charsInEncodedString;
        }
    }

    actualDiffCharsTotal = sumCharsInEncodedStringCode - sumCharsInStringCode;

    TEST_ASSERT_EQUAL(expectedDiffCharsTotal, actualDiffCharsTotal);

    inputFile.close();

}

/** ***************************************** Private Function Definitions *********************************************/

/** ***************************************** Amalgamation of Test Cases **********************************************/

void test_aoc2015_day8(bool printTest) {
    if (!printTest) {
        RUN_TEST(test_aoc_day8_basic_input);
        RUN_TEST(test_aoc_day8_basic_input_p2);
        RUN_TEST(test_aoc_day8_input_file);
        RUN_TEST(test_aoc_day8_input_file_p2);
    } else {
        printf("%s\n", "test_aoc_day8_basic_input");
        printf("%s\n", "test_aoc_day8_basic_input_p2");
        printf("%s\n", "test_aoc_day8_input_file");
        printf("%s\n", "test_aoc_day8_input_file_p2");
    }
}

