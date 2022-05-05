//
// Created by conan on 11/12/2021.
//

#ifndef CPP_AOC_2015_DAY8_H
#define CPP_AOC_2015_DAY8_H

#include <string>
#include <iostream>

using namespace std;


/*!
    Class to implement the solution to AoC 20XX Day X
*/
class AoC2015Day8 {
public:

    /*!
        Constructor and Destructor
    */
    AoC2015Day8();
    ~AoC2015Day8();

    /*!
    Function to input a string to be checked
    \return void
    */
    void evaluateString(const string &sInputString);

    void evaluateEncodedString(const string &sInputString);

    uint32_t getCharsStringCode();
    uint32_t getCharsInMem();

    /*!
        Function to reset the values of the class
        \return void
    */
    void reset();

private:
    uint32_t u32CharsInMem;
    uint32_t u32CharsInStringCode;
};

#endif //CPP_AOC_2015_DAY8_H
