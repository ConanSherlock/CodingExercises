#ifndef AOC_2015_DAY1_HPP_
#define AOC_2015_DAY1_HPP_

/* Includes section
 **********************************************************************************************************************/
#include <string>
#include <iostream>

using namespace std;

enum AOC_2015_DAY1_EXCEPTIONS{
    INVALID_CHARACTER,
};

const char * aoc2015Day1ExceptionToString(AOC_2015_DAY1_EXCEPTIONS type);

struct InvalidCharacter : public exception {
    const char * what () const noexcept override {                          // NOLINT
        return aoc2015Day1ExceptionToString(INVALID_CHARACTER);
    }
};

/*!
    Class to implement the solution to AoC 2015 Day 1
    This class takes an input string of ( and ). It then uses this to calculate what floor Santa will be on, and it also
    captures the index/position santa first enters the basement. This basement value is 1 indexed instead of the usual
    0 indexing
*/
class AoC2015Day1 {
public:

    /*!
        Constructor and Destructor
    */
    AoC2015Day1();
    ~AoC2015Day1();

    /*!
        Function to find the floor Santa is on based on an input string.
        \return int Floor number
    */
    int findFloor(string &sInputString);

    /*!
        Function to find the position of the character that first puts Santa in the basement which is -1 by
        default/not found
        \return int 1 indexed position in the string
    */
    int getBasementPosition() const;    // NOLINT

    /*!
        Function to reset the internal variables used in Day 1.
        \return void
    */
    void reset();

private:
    int iLoopCount;
    int iFloorNumber;
    int iBasementPosition;
};

#endif //AOC_2015_DAY1_HPP_
