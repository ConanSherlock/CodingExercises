#ifndef AOC_UNITY_TEST_LIST_H
#define AOC_UNITY_TEST_LIST_H

#ifdef __cpluscplus
extern "C"
{
#endif
/** ***************************************** Includes ****************************************************************/
#include <string>

/** ***************************************** Public types ************************************************************/
typedef void (*TEST_SUITE_FUNC)(bool);

typedef struct test_list_node {
  TEST_SUITE_FUNC testFunc;
  std::string *test_name;
  struct test_list_node *next;
} TEST_LIST_NODE;

typedef enum TEST_TYPE {
  SHORT_TEST_TYPE = 0,
  MEDIUM_TEST_TYPE = 1,
  LONG_TEST_TYPE = 2,
  TEST_2015_TYPE = 3,
}TEST_TYPE;

/** ***************************************** Test Suite List *********************************************************/
extern void test_aoc2015_day1(bool printTest);
extern void test_aoc2015_day2(bool printTest);
extern void test_aoc2015_day3(bool printTest);
extern void test_aoc2015_day4(bool printTest);
extern void test_aoc2015_day5(bool printTest);
extern void test_aoc2015_day6(bool printTest);
extern void test_aoc2015_day7(bool printTest);
extern void test_aoc2015_day8(bool printTest);

/** ***************************************** Public Function Declarations ********************************************/

/**
 * Method for constructing list of test suites
 */
void InitialiseTestList(TEST_TYPE enTestType);

/**
 * Method for running tests in each test suite
 */
void RunAllTests(bool shouldPrintTest);

/**
 * Method for running individual test suite
 */
void RunSingleTestSuite(const std::string &test_name, bool shouldPrintTests);

/**
 * Method for removing list of test suites
 */
void CleanTestList();

#ifdef __cpluscplus
}
#endif

#endif //AOC_UNITY_TEST_LIST_H
