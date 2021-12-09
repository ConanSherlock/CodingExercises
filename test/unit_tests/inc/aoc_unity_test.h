#ifndef AOC_UNITY_TEST_H
#define AOC_UNITY_TEST_H

#ifdef __cpluscplus
extern "C"
{
#endif

/** ***************************************** Includes ****************************************************************/
#include "aoc_unity_test_parameters.h"
#include "aoc_unity_test_list.h"

/** ***************************************** Defines *****************************************************************/
#define FULL_TEST_EXECUTION         "ALL"

#define SHORT_TEST_ARG_TYPE         "SHORT"
#define MED_TEST_ARG_TYPE           "MEDIUM"
#define LONG_TEST_ARG_TYPE          "LONG"
#define TEST_2015_ARG_TYPE          "2015"


/** ***************************************** Public Functions ********************************************************/
int runTests(int argc, const char *argv[]);

#ifdef __cpluscplus
}
#endif

#endif //AOC_UNITY_TEST_H
