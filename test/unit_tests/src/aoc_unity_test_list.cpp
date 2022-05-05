/** ***************************************** Includes ****************************************************************/

#include "aoc_unity_test_list.h"
#include <cstdint>

/** ***************************************** Global Variables ********************************************************/

TEST_LIST_NODE *g_Head;

/** ***************************************** Private Function Definitions *********************************************/

static TEST_LIST_NODE *initList();
static uint8_t appendToList(TEST_LIST_NODE *head_node, std::string const &test_name, TEST_SUITE_FUNC func);
static uint8_t appendToListNull(TEST_LIST_NODE *head_node);

/** ***************************************** Public Functions ********************************************************/

void InitialiseTestList(TEST_TYPE enTestType) {
    TEST_LIST_NODE *head_node = initList();
    head_node->test_name = nullptr;
    head_node->testFunc = nullptr;

    // Append Test Suites to List

    switch (enTestType) {
        case SHORT_TEST_TYPE:

            printf("Short Tests");

            printf("Test 2015 Short Tests\n");

            appendToList(head_node, "test_aoc2015_day1", test_aoc2015_day1);
            appendToList(head_node, "test_aoc2015_day2", test_aoc2015_day2);
            appendToList(head_node, "test_aoc2015_day3", test_aoc2015_day3);
            appendToList(head_node, "test_aoc2015_day4", test_aoc2015_day4);
            appendToList(head_node, "test_aoc2015_day5", test_aoc2015_day5);
            appendToList(head_node, "test_aoc2015_day6", test_aoc2015_day6);
            appendToList(head_node, "test_aoc2015_day7", test_aoc2015_day7);
            appendToList(head_node, "test_aoc2015_day8", test_aoc2015_day8);

            break;

        case MEDIUM_TEST_TYPE:

            printf("Medium Tests");

            printf("Test 2015 Medium Tests\n");

            appendToList(head_node, "test_aoc2015_day1", test_aoc2015_day1);
            appendToList(head_node, "test_aoc2015_day2", test_aoc2015_day2);
            appendToList(head_node, "test_aoc2015_day3", test_aoc2015_day3);
            appendToList(head_node, "test_aoc2015_day4", test_aoc2015_day4);
            appendToList(head_node, "test_aoc2015_day5", test_aoc2015_day5);
            appendToList(head_node, "test_aoc2015_day6", test_aoc2015_day6);
            appendToList(head_node, "test_aoc2015_day7", test_aoc2015_day7);
            appendToList(head_node, "test_aoc2015_day8", test_aoc2015_day8);

            break;

        case LONG_TEST_TYPE:

            printf("Long Tests");

            printf("Test 2015 Long Tests\n");

            appendToList(head_node, "test_aoc2015_day1", test_aoc2015_day1);
            appendToList(head_node, "test_aoc2015_day2", test_aoc2015_day2);
            appendToList(head_node, "test_aoc2015_day3", test_aoc2015_day3);
            appendToList(head_node, "test_aoc2015_day4", test_aoc2015_day4);
            appendToList(head_node, "test_aoc2015_day5", test_aoc2015_day5);
            appendToList(head_node, "test_aoc2015_day6", test_aoc2015_day6);
            appendToList(head_node, "test_aoc2015_day7", test_aoc2015_day7);
            appendToList(head_node, "test_aoc2015_day8", test_aoc2015_day8);

            break;

        case TEST_2015_TYPE:

            printf("Test 2015\n");

            appendToList(head_node, "test_aoc2015_day1", test_aoc2015_day1);
            appendToList(head_node, "test_aoc2015_day2", test_aoc2015_day2);
            appendToList(head_node, "test_aoc2015_day3", test_aoc2015_day3);
            appendToList(head_node, "test_aoc2015_day4", test_aoc2015_day4);
            appendToList(head_node, "test_aoc2015_day5", test_aoc2015_day5);
            appendToList(head_node, "test_aoc2015_day6", test_aoc2015_day6);
            appendToList(head_node, "test_aoc2015_day7", test_aoc2015_day7);
            appendToList(head_node, "test_aoc2015_day8", test_aoc2015_day8);

            break;

    }

    // Append Null Test Suite (tail node)
    appendToListNull(head_node);

    // assign global reference to head node
    g_Head = head_node;
}


void RunAllTests(bool shouldPrintTest) {
    TEST_LIST_NODE *current_node = g_Head;
    while (current_node->next != nullptr) {
        // execute tests
        if (current_node->testFunc != nullptr) {
            // Execute tests in suite function definition
            current_node->testFunc(shouldPrintTest);
        }

        // Move to the next suite
        current_node = current_node->next;
    }
}

void RunSingleTestSuite(const std::string &test_name, bool shouldPrintTest) {
    TEST_LIST_NODE *current_node = g_Head;
    while (current_node->next != nullptr) {
        // scan through list until suite is found
        if ((current_node->test_name != nullptr) && (*current_node->test_name == test_name)) {
            // execute tests
            if (current_node->testFunc != nullptr) {
                // Execute tests in suite function definition
                current_node->testFunc(shouldPrintTest);
            }
        }

        // Move to the next suite
        current_node = current_node->next;
    }
}

void CleanTestList() {
    TEST_LIST_NODE *current_node = g_Head;
    TEST_LIST_NODE *next_node;

    while (current_node != nullptr) {
        next_node = current_node->next;
        delete current_node->test_name;
        delete current_node;
        current_node = next_node;
    }

    g_Head = nullptr;
}

/** ***************************************** Private Functions *******************************************************/

static TEST_LIST_NODE *initList() {
    auto *head_node = new TEST_LIST_NODE;
    head_node->next = nullptr;
    return head_node;
}

static uint8_t appendToList(TEST_LIST_NODE *head_node, std::string const &test_name, TEST_SUITE_FUNC func) {
    TEST_LIST_NODE *current_node = head_node;

    while (current_node->next != nullptr) {
        current_node = current_node->next;
    }

    current_node->next = new TEST_LIST_NODE;
    current_node->next->test_name = new std::string(test_name);
    current_node->next->testFunc = func;
    current_node->next->next = nullptr;
    return 1;
}

static uint8_t appendToListNull(TEST_LIST_NODE *head_node) {
    TEST_LIST_NODE *current_node = head_node;

    while (current_node->next != nullptr) {
        current_node = current_node->next;
    }

    current_node->next = new TEST_LIST_NODE;
    current_node->next->test_name = nullptr;
    current_node->next->testFunc = nullptr;
#if !defined(_WIN32) && !defined(__linux__)
    current_node->next->testResultFunc = nullptr;
#endif
    current_node->next->next = nullptr;
    return 1;
}