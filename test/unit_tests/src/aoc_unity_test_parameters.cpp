#include <cstdint>
#include <cstring>
#include <cstdio>

#include "aoc_unity_test_parameters.h"

/** ***************************************** Global Variables ********************************************************/

/** ***************************************** Private Function Definitions *********************************************/
static void initTestParameters(UnityTestInternalStruct *ptr_stUnityTestParams);
static uint8_t isArgument(const char *arr_cArgIn, const char *arr_cArg);
static uint8_t setParameterValue(int argc, const char **argv, uint16_t *ptr_ui16ArgumentIndex, char *arr_cParameter, uint8_t *isSet);

/** ***************************************** Public Functions ********************************************************/
uint8_t isSetTestTypeParameter(const UnityTestInternalStruct *ptr_stUnityTestParams)
{
    return ptr_stUnityTestParams->isSetTestType;
}

char *getTestTypeParameter(UnityTestInternalStruct *ptr_stUnityTestParams)
{
    return ptr_stUnityTestParams->arr_cTestType;
}

uint8_t isSetUnitTestParameter(const UnityTestInternalStruct *ptr_stUnityTestParams)
{
    return ptr_stUnityTestParams->isSetUnitTest;
}

char *getUnitTestParameter(UnityTestInternalStruct *ptr_stUnityTestParams)
{
    return ptr_stUnityTestParams->arr_cUnitTest;
}

uint8_t isGetTestsParameter(UnityTestInternalStruct *ptr_stUnityTestParams)
{
    return ptr_stUnityTestParams->isGetTests;
}

uint8_t shouldGetTests(UnityTestInternalStruct *ptr_stUnityTestParams)
{
    char cGetTestParam = ptr_stUnityTestParams->arr_cGetTests[0];

    return (uint8_t)(cGetTestParam - '0');
}

void processParameters(int argc, const char *argv[], UnityTestInternalStruct *ptr_stUnityTestParams)
{
    uint16_t ui16ArgIdx = 1;

    // Initialize Test Params
    initTestParameters(ptr_stUnityTestParams);

    // process all arguments
    while((ui16ArgIdx < argc) && ptr_stUnityTestParams->isProcessSuccess)
    {

        // set test type
        if(isArgument(argv[ui16ArgIdx], TEST_TYPE_PARAM))
        {
            ptr_stUnityTestParams->isProcessSuccess = setParameterValue(argc, argv, &ui16ArgIdx,
                                                                        ptr_stUnityTestParams->arr_cTestType, &ptr_stUnityTestParams->isSetTestType);
        }

        // set unit test to execute
        else if(isArgument(argv[ui16ArgIdx], UNIT_TEST_PARAM))
        {
            ptr_stUnityTestParams->isProcessSuccess = setParameterValue(argc, argv, &ui16ArgIdx,
                    ptr_stUnityTestParams->arr_cUnitTest, &ptr_stUnityTestParams->isSetUnitTest);
        }

        // set get tests to print
        else if(isArgument(argv[ui16ArgIdx], GET_TESTS_PARAM))
        {
            ptr_stUnityTestParams->isProcessSuccess = setParameterValue(argc, argv, &ui16ArgIdx,
                     ptr_stUnityTestParams->arr_cGetTests, &ptr_stUnityTestParams->isGetTests);
        }

        // otherwise there was a problem
        else{
            printf("Error processing input parameters. Unknown parameter %s\n", argv[ui16ArgIdx]);
            ptr_stUnityTestParams->isProcessSuccess = 0;
        }

        // Check error parsing current parameter.
        if (!ptr_stUnityTestParams->isProcessSuccess)
        {
            printf("Error processing parameter %s\n", argv[ui16ArgIdx]);
        }

        // Next argument
        ui16ArgIdx++;
    }
}


uint8_t checkParameters(UnityTestInternalStruct *ptr_stUnityTestParams)
{
    // test type is mandatory - check if it exists
    if(!isSetTestTypeParameter(ptr_stUnityTestParams))
    {
        printf("Mandatory parameter is missing %s\n", TEST_TYPE_PARAM);
        ptr_stUnityTestParams->isProcessSuccess = 0;
    }

    return ptr_stUnityTestParams->isProcessSuccess;
}

/** ***************************************** Private Function Declarations *******************************************/
/**
 * Initializes parameter structure with initial values
 * @param ptr_stUnityTestParams (OUT) parameters structure to initialize
 */
static void initTestParameters(UnityTestInternalStruct *ptr_stUnityTestParams)
{
    ptr_stUnityTestParams->isProcessSuccess = 1;
    ptr_stUnityTestParams->isSetTestType = 0;
    ptr_stUnityTestParams->isSetUnitTest = 0;
    ptr_stUnityTestParams->isGetTests = 0;
}

/**
 * checks if 2 strings are equal
 * @param arr_cArgIn (IN) first string to compare
 * @param arr_cArg (IN) second string to compare
 * @return TRUE if strings are equal
 *         FALSE otherwise
 */
static uint8_t isArgument(const char *arr_cArgIn, const char *arr_cArg)
{
    return (uint8_t)(strcmp(arr_cArgIn, arr_cArg) == 0);
}

/**
 * Sets parameter value
 * @param argc (IN) number of input arguments
 * @param argv (IN) list of input arguments
 * @param ptr_ui16ArgumentIndex (IN/OUT) index of current argument
 * @param arr_cParameter (OUT) variable where parameter value will be stored
 * @param isSet (OUT) flag indicator
 * @return TRUE if parameter correctly processed
 *         FALSE otherwise
 */
static uint8_t setParameterValue(int argc, const char **argv, uint16_t *ptr_ui16ArgumentIndex, char *arr_cParameter, uint8_t *isSet)
{
    uint8_t isSuccess = 1;

    // Check if there is no extra argument.
    if ((argc-1) == (*ptr_ui16ArgumentIndex))
    {
        isSuccess = 0;
        printf("Parameter value not supplied\n");
    }
        // Parse argument.
    else
    {
        (*ptr_ui16ArgumentIndex)++;
        strcpy(arr_cParameter, argv[(*ptr_ui16ArgumentIndex)]);
        (*isSet) = 1;
    }

    return isSuccess;
}
