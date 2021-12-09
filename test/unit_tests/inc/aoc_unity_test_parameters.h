#ifndef AOC_UNITY_TEST_PARAMETERS_H
#define AOC_UNITY_TEST_PARAMETERS_H

/** ***************************************** Includes ****************************************************************/
#include <cstdint>

/** ***************************************** Defines *****************************************************************/
#define MAX_VERSION_SIZE            (50)
#define MAX_FILE_LINE_SIZE          (500)

#define TEST_TYPE_PARAM             "--testType"
#define UNIT_TEST_PARAM             "--unit"
#define GET_TESTS_PARAM             "--getTests"

/** ***************************************** Exported Types **********************************************************/
typedef struct UnityTestInternalStruct {
  uint8_t     isProcessSuccess;

  uint8_t     isSetTestType;
  char        arr_cTestType[MAX_FILE_LINE_SIZE];

  uint8_t     isSetUnitTest;
  char        arr_cUnitTest[MAX_FILE_LINE_SIZE];

  uint8_t     isGetTests;
  char        arr_cGetTests[1];

}UnityTestInternalStruct;

/** ***************************************** Public Functions ********************************************************/
/**
 * Method for checking if test type parameter is provided
 * @param ptr_stUnityTestParams (IN) parameters structure
 * @return TRUE if test type set
 *         FALSE otherwise
 */
uint8_t isSetTestTypeParameter(const UnityTestInternalStruct *ptr_stUnityTestParams);

/**
 * Method for retrieving test type parameter
 * @param ptr_stUnityTestParams (IN) parameters structure
 * @return (OUT) test type
 */
char *getTestTypeParameter(UnityTestInternalStruct *ptr_stUnityTestParams);

/**
 * Method for checking if single unit test to be executed
 * @param ptr_stUnityTestParams (IN) parameters structure
 * @return TRUE if single unit test to be executed
 *         FALSE otherwise
 */
uint8_t isSetUnitTestParameter(const UnityTestInternalStruct *ptr_stUnityTestParams);

/**
 * Method for retrieving unit test name
 * @param ptr_stUnityTestParams (IN) parameters structure
 * @return (OUT) unit test to be executed
 */
char *getUnitTestParameter(UnityTestInternalStruct *ptr_stUnityTestParams);

/**
 * Method for checking if getTests parameter is provided
 * @param ptr_stUnityTestParams (IN) parameters structure
 * @return (OUT) TRUE if tests are to be retrieved
 *               FALSE otherwise
 */
uint8_t isGetTestsParameters(UnityTestInternalStruct *ptr_stUnityTestParams);

/**
 * Method for checking if tests should be retrieved
 * @param ptr_stUnityTestParams (IN) parameters structure
 * @return (OUT) TRUE if tests should be retrieved
 *               FALSE otherwise
 */
uint8_t shouldGetTests(UnityTestInternalStruct *ptr_stUnityTestParams);

/**
 * Method for processing argc arguments in argv and storing to a parameters structure
 * @param argc (IN) Number of input arguments to process
 * @param argv (IN) List of input arguments to process
 * @param ptr_stUnityTestParams (OUT) structure where parameter values will be stored
 */
void processParameters(int argc, const char *argv[], UnityTestInternalStruct *ptr_stUnityTestParams);

/**
 * Checks if test execution parameters are correct
 * @param ptr_stUnityTestParams (IN/OUT) Test execution parameters
 * @return TRUE if all parameters are set correctly
 *         FALSE otherwise
 */
uint8_t checkParameters(UnityTestInternalStruct *ptr_stUnityTestParams);

#endif //AOC_UNITY_TEST_PARAMETERS_H
