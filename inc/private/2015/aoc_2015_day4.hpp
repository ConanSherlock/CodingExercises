//
// Created by conan on 11/12/2021.
//

#ifndef CPP_AOC_2015_DAY4_H
#define CPP_AOC_2015_DAY4_H

#include <string>
#include <map>
#include <iostream>
#include <iomanip>
#include "md5.h"

using namespace std;

/*!
    Class to implement the solution to AoC 2015 Day 4
*/

#define MAX_DIGEST_LENGTH 16

class AoC2015Day4 {
public:
    /*!
        Constructor and Destructor
    */
    AoC2015Day4();
    ~AoC2015Day4();

    uint32_t md5LeadingZeroes(string &sInputString, int iLeadingZeroes);
    uint32_t getSecretCode() const;  //NOLINT
    int getLeadingZeroes() const;  //NOLINT

    void reset();

private:
    bool bDebugPrint;
    int iLeadingZeroCount;
    uint32_t ui32IntCode;
};

#endif //CPP_AOC_2015_DAY4_H
