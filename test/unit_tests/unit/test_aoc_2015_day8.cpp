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

    string line;

    // Good input Check
    for (auto &i: goodInputStrings) {
        day8.evaluateString(i);

        // TODO check outputs of total characters and string characters for each string
    }

    // TODO check overall total characters and string characters for all strings

}

void test_aoc_day8_input_file() {

    // Test using the original input file with expected correct answers for Day 8
    string inputString;

    ifstream inputFile;
    string inputFileName = {"./input_data/2015/day8_input.txt"};
    inputFile.open(inputFileName);

    if (inputFile.is_open()) {
        while (getline(inputFile, inputString)) {
            printf("%s\n", inputString.c_str());
        }
    }

    // TODO check overall total characters and string characters for all strings in the file

    inputFile.close();

}

/** ***************************************** Private Function Definitions *********************************************/

/** ***************************************** Amalgamation of Test Cases **********************************************/

void test_aoc2015_day8(bool printTest) {
    if (!printTest) {
        RUN_TEST(test_aoc_day8_basic_input);
        RUN_TEST(test_aoc_day8_input_file);
    } else {
        printf("%s\n", "test_aoc_day8_basic_input");
        printf("%s\n", "test_aoc_day8_input_file");
    }
}

