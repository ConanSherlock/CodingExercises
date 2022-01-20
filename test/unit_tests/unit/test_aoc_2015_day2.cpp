/** ***************************************** Includes ****************************************************************/

#include "unity.h"
#include <fstream>
#include <string>
#include "aoc_2015_day2.hpp"

using namespace std;

/** ***************************************** Global Variables ********************************************************/

/** ***************************************** Private Function Declarations *******************************************/

/** ***************************************** Test Cases **************************************************************/

void test_aoc_day2_basic_input() {

    //  Paper
    //  2x3x4 => 52 surface area + 6 slack   =>  58 total
    //  1x1x10 => 10 surface area + 1 slack  =>  1 total

    //  Ribbon
    //  2x3x4 => perimeter + volume => 10 + 24 => 34 total
    //  1x1x10 => perimeter + volume => 10 + 4 => 14 total

    AoC2015Day2 day2;

    int expectedTotalPaper;
    int actualTotalPaper;
    int expectedTotalRibbon;
    int actualTotalRibbon;

    string inputString1 = "2x3x4";
    string inputString2 = "1x1x10";
    string inputString3 = "RandomCharacters";

    // No input, no calc Check
    expectedTotalPaper = -2;
    expectedTotalRibbon = -1;

    actualTotalPaper = day2.getPresentPaper();
    actualTotalRibbon = day2.getRibbonLength();
    TEST_ASSERT_EQUAL(expectedTotalPaper, actualTotalPaper);
    TEST_ASSERT_EQUAL(expectedTotalRibbon, actualTotalRibbon);

    // Good input Check
    expectedTotalPaper = 58;
    expectedTotalRibbon = 34;

    day2.calcMaterialsNeeded(inputString1);
    actualTotalPaper = day2.getPresentPaper();
    actualTotalRibbon = day2.getRibbonLength();
    TEST_ASSERT_EQUAL(expectedTotalPaper, actualTotalPaper);
    TEST_ASSERT_EQUAL(expectedTotalRibbon, actualTotalRibbon);

    expectedTotalPaper = 43;
    expectedTotalRibbon = 14;

    day2.calcMaterialsNeeded(inputString2);
    actualTotalPaper = day2.getPresentPaper();
    actualTotalRibbon = day2.getRibbonLength();
    TEST_ASSERT_EQUAL(expectedTotalPaper, actualTotalPaper);
    TEST_ASSERT_EQUAL(expectedTotalRibbon, actualTotalRibbon);
    day2.reset();

    // Bad input Check
    expectedTotalPaper = -2;
    expectedTotalRibbon = -1;

    day2.calcMaterialsNeeded(inputString3);
    actualTotalPaper = day2.getPresentPaper();
    actualTotalRibbon = day2.getRibbonLength();
    TEST_ASSERT_EQUAL(expectedTotalPaper, actualTotalPaper);
    TEST_ASSERT_EQUAL(expectedTotalRibbon, actualTotalRibbon);
    day2.reset();

}

void test_aoc_day2_input_file() {

    // Test using the original input file with expected correct answers for Day 2

    AoC2015Day2 day2;

    string inputString;

    ifstream inputFile;
    string inputFileName = {"./input_data/2015/day2_input.txt"};
    inputFile.open(inputFileName);

    int expectedAreaOfPaperNeeded = 1598415;
    int actualAreaOfPaperNeeded;
    int actualSumAreaOfPaperNeeded = 0;

    int expectedLengthOfRibbonNeeded = 3812909;
    int actualLengthOfRibbonNeeded;
    int actualSumLengthOfRibbonNeeded = 0;

    if (inputFile.is_open()) {
        while (getline(inputFile, inputString)) {
            day2.calcMaterialsNeeded(inputString);
            actualAreaOfPaperNeeded = day2.getPresentPaper();
            actualLengthOfRibbonNeeded = day2.getRibbonLength();

            if(actualAreaOfPaperNeeded > 0) {
                actualSumAreaOfPaperNeeded += actualAreaOfPaperNeeded;
            }
            if(actualLengthOfRibbonNeeded > 0) {
                actualSumLengthOfRibbonNeeded += actualLengthOfRibbonNeeded;
            }
        }
    }

    inputFile.close();

    TEST_ASSERT_EQUAL(expectedAreaOfPaperNeeded, actualSumAreaOfPaperNeeded);
    TEST_ASSERT_EQUAL(expectedLengthOfRibbonNeeded, actualSumLengthOfRibbonNeeded);
}

/** ***************************************** Private Function Definitions *********************************************/

/** ***************************************** Amalgamation of Test Cases **********************************************/

void test_aoc2015_day2(bool printTest) {
    if (!printTest) {
        RUN_TEST(test_aoc_day2_basic_input);
        RUN_TEST(test_aoc_day2_input_file);
    } else {
        printf("%s\n", "test_aoc_day2_basic_input");
        printf("%s\n", "test_aoc_day2_input_file");
    }
}

