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
class AoC2015Day4 {
public:
    /*!
        Constructor and Destructor
    */
    AoC2015Day4();
    ~AoC2015Day4();

    void basic(string &inputString, int stringLength);

    void reset();

private:
    size_t MAX_DIGEST_LENGTH;
};

#endif //CPP_AOC_2015_DAY4_H
