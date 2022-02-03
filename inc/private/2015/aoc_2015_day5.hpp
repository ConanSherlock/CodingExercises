//
// Created by conan on 11/12/2021.
//

#ifndef CPP_AOC_2015_DAY5_H
#define CPP_AOC_2015_DAY5_H

#include <string>
#include <iostream>

using namespace std;

#define VOWELS {"a", "e", "i", "o", "u"}
#define FORBIDDEN_SUBSTRINGS {"ab", "cd", "pq", "xy"}
#define REQUIRED_VOWELS 3

typedef enum behaviour {
    UNKNOWN = -1,
    NICE = 0,
    NAUGHTY = 1,
}behaviour;


/*!
    Class to implement the solution to AoC 2015 Day 5
*/
class AoC2015Day5 {
public:

    /*!
        Constructor and Destructor
    */
    AoC2015Day5();
    ~AoC2015Day5();

    /*!
        Function to reset the values of the class
        \return void
    */
    void reset();

    behaviour checkNaughtyOrNice(string &sInputString);

    uint32_t getNiceCount();

private:
    bool bVowelsFound;
    bool bRepeatLetterFound;
    bool bForbiddenStringFound;
    uint32_t u32NiceCount;
    behaviour beh_Behaviour;

};

#endif //CPP_AOC_2015_DAY5_H
