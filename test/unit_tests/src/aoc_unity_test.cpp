/**
 * @file aoc2015_unity_test
 *
 * @brief Main entry point for running Unity-based unit tests
 *
 * @author CS
 * @date 14/07/2021
 */

/** ***************************************** Includes ****************************************************************/

#include "aoc_unity_test.h"
#include "unity.h"
#include "aoc_2015.hpp"

#include <cstring>

using namespace aoc_2015;
/** ***************************************** Defines *****************************************************************/

/** ***************************************** Global Variables ********************************************************/
static UnityTestInternalStruct g_stUnityTestInternalParams;

/** ***************************************** Private Functions *******************************************************/
static void printLibraryVersion();
static void initialiseCorrectTestList(UnityTestInternalStruct *ptr_stUnityTestParams);
static void usage();

/** ***************************************** Global setup/teardown methods *******************************************/
void setUp()
{
    // do nothing for now
}

void tearDown()
{
    // do nothing for now
}

/** ***************************************** Public functions ********************************************************/
int runTests(int argc, const char *argv[]) {
	
  int16_t sTestResult = 0;

  // process input parameters
  processParameters(argc, argv, &g_stUnityTestInternalParams);

  // check for input parameter errors
  if(checkParameters(&g_stUnityTestInternalParams))
  {
    // print library version
    printLibraryVersion();

    // Initialise Test List - Dependent on test type
    initialiseCorrectTestList(&g_stUnityTestInternalParams);

    // Just print tests
    if(shouldGetTests(&g_stUnityTestInternalParams))
    {
      // Print Test List
      if (strcmp(g_stUnityTestInternalParams.arr_cUnitTest, FULL_TEST_EXECUTION) == 0) {
        // Run all test suites
        RunAllTests(true);
      } else {
        // Run single test suite
        RunSingleTestSuite(g_stUnityTestInternalParams.arr_cUnitTest, true);
      }
    }
    // otherwise perform test execution
    else {
      // Setup Unity
      UNITY_BEGIN();

      // Test execution
      if (strcmp(g_stUnityTestInternalParams.arr_cUnitTest, FULL_TEST_EXECUTION) == 0) {
        // Run all test suites
        RunAllTests(false);
      } else {
        // Run single test suite
        RunSingleTestSuite(g_stUnityTestInternalParams.arr_cUnitTest, false);
      }

      // cleanup test framework
      sTestResult = UNITY_END();
    }
  }
  else {
    usage();
    sTestResult = -1;
  }

  // return PASS/Failures
  return sTestResult;
}

int main(int argc, char *argv[])
{
  return runTests(argc, (const_cast<const char **>(argv)));
}

/** ***************************************** Private Functions *******************************************************/

static void printLibraryVersion()
{
  printf("\n\n************************* AOC2015 ************************* \n\n"
         "Version: %s\n\n"
         "***********************************************************\n\n", AoC2015::AoC2015GetVersion().c_str());

}

static void initialiseCorrectTestList(UnityTestInternalStruct *ptr_stUnityTestParams)
{
  if(strcmp(ptr_stUnityTestParams->arr_cTestType, SHORT_TEST_ARG_TYPE) == 0)
  {
    InitialiseTestList(SHORT_TEST_TYPE);
  }
  else if(strcmp(ptr_stUnityTestParams->arr_cTestType, MED_TEST_ARG_TYPE) == 0)
  {
    InitialiseTestList(MEDIUM_TEST_TYPE);
  }
  else if(strcmp(ptr_stUnityTestParams->arr_cTestType, LONG_TEST_ARG_TYPE) == 0)
  {
    InitialiseTestList(LONG_TEST_TYPE);
  }
  else if(strcmp(ptr_stUnityTestParams->arr_cTestType, TEST_2015_ARG_TYPE) == 0)
  {
    InitialiseTestList(TEST_2015_TYPE);
  }
}




static void usage()
{
  printf("\nUsage\tAoC2015_Test %s <test_type - SHORT | MEDIUM | LONG> %s <unit_test - ALL | test_suite_name> %s <get_test - 0 | 1>\n\n",
         TEST_TYPE_PARAM,
         UNIT_TEST_PARAM,
         GET_TESTS_PARAM);
}
