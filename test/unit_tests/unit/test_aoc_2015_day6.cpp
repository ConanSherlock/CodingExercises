/** ***************************************** Includes ****************************************************************/

#include "unity.h"
#include <fstream>
#include <string>
#include "aoc_2015_day6.hpp"

using namespace std;

/** ***************************************** Global Variables ********************************************************/

/** ***************************************** Private Function Declarations *******************************************/

/** ***************************************** Test Cases **************************************************************/

void test_aoc_day6_basic_input() {

    //  Mining Advent Coins, search for correct md5 hashes
    //  abcdef combines with 609043 => abcdef609043 => md5 hash 000001dbbfa...
    //  pqrstuv combines with 1048970 => pqrstuv1048970 => md5 hash 000006136ef....

    AoC2015Day6 day6;

    string inputStrings[3] = {"turn on 0,0 through 999,999",
                              "toggle 0,0 through 999,0",
                              "turn off 499,499 through 500,500"};
    int expectedLights[3] = {1000000, 999000, 998996};
    int expectedInitialLights = 0;
    int j = 0;

    TEST_ASSERT_EQUAL(expectedInitialLights, day6.getNumberOfLightsOn());

    // Good input Check
    for (auto &i: inputStrings) {
        day6.updateLightsPartA(i);
        TEST_ASSERT_EQUAL(expectedLights[j], day6.getNumberOfLightsOn());
        j++;
    }

    day6.reset();

    TEST_ASSERT_EQUAL(expectedInitialLights, day6.getNumberOfLightsOn());

}

void test_aoc_day6_input_file() {

    // Test using the original input file with expected correct answers for Day 4

    AoC2015Day6 day6;

    string inputString;
    ifstream inputFile;

    string inputFileName = {"./input_data/2015/day6_input.txt"};
    inputFile.open(inputFileName);

    int expectedLightsOn = 400410;
    int expectedBrightness = 15343601;

    if (inputFile.is_open()) {
        while (getline(inputFile, inputString)) {
            day6.updateLightsPartA(inputString);
        }
    }

    TEST_ASSERT_EQUAL(expectedLightsOn, day6.getNumberOfLightsOn());

    day6.reset();

    inputFile.clear();
    inputFile.seekg(0, std::ifstream::beg);

    if (inputFile.is_open()) {
        while (getline(inputFile, inputString)) {
            day6.updateLightsPartB(inputString);
        }
    }

    TEST_ASSERT_EQUAL(expectedBrightness, day6.getTotalBrightness());

    day6.reset();


    inputFile.close();
}

/** ***************************************** Private Function Definitions *********************************************/

/** ***************************************** Amalgamation of Test Cases **********************************************/

void test_aoc2015_day6(bool printTest) {
    if (!printTest) {
        RUN_TEST(test_aoc_day6_basic_input);
        RUN_TEST(test_aoc_day6_input_file);
    } else {
        printf("%s\n", "test_aoc_day6_basic_input");
        printf("%s\n", "test_aoc_day6_input_file");
    }
}

