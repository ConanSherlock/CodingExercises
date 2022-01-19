/** ***************************************** Includes ****************************************************************/

#include "unity.h"
#include <fstream>
#include <string>
#include "aoc_2015_day4.hpp"

using namespace std;

/** ***************************************** Global Variables ********************************************************/

/** ***************************************** Private Function Declarations *******************************************/

/** ***************************************** Test Cases **************************************************************/

void test_aoc_day4_basic_input() {

    //  Mining Advent Coins, search for correct md5 hashes
    //  abcdef combines with 609043 => abcdef609043 => md5 hash 000001dbbfa...
    //  pqrstuv combines with 1048970 => pqrstuv1048970 => md5 hash 000006136ef....

    AoC2015Day4 day4;

    string inputString1 = "abcdef";
    string inputString2 = "pqrstuv";
    string inputStringBadInput = "Bad Input";

    // No input, no calc Check


    // Good input Check


    // Bad input Check

}

void test_aoc_day4_input_file() {

    // Test using the original input file with expected correct answers for Day 4

    AoC2015Day4 day4;

    string inputString;
    ifstream inputFile;

    string inputFileName = {"./input_data/2015/day4_input.txt"};
    inputFile.open(inputFileName);

    if (inputFile.is_open()) {
        while (getline(inputFile, inputString)) {
            day4.basic(inputString, 0);
        }
    }

    inputFile.close();
}

/** ***************************************** Private Function Definitions *********************************************/

/** ***************************************** Amalgamation of Test Cases **********************************************/

void test_aoc2015_day4(bool printTest) {
    if (!printTest) {
        RUN_TEST(test_aoc_day4_basic_input);
        RUN_TEST(test_aoc_day4_input_file);
    } else {
        printf("%s\n", "test_aoc_day4_basic_input");
        printf("%s\n", "test_aoc_day4_input_file");
    }
}

