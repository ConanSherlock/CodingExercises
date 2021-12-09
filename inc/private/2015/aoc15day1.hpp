#ifndef AOC_2015_DAY1_HPP_
#define AOC_2015_DAY1_HPP_

/* Includes section
 **********************************************************************************************************************/
#include <string>
#include <iostream>


using namespace std;

// Class to implement the solution to AoC 2015 Day 1
// This class takes an input string of ( and ). It then uses this to calculate what floor Santa will be on, and it also
// captures the index/position santa first enters the basement. This basement value is 1 indexed instead of the usual
// 0 indexing
class AoC2015Day1 {
public:

    // Constructor and Destructor
    AoC2015Day1();
    ~AoC2015Day1();

    int findFloor(string &inputString);
    int getBasementPosition() const;    // NOLINT
    void reset();

private:
    int iloopCount;
    int ifloorNumber;
    int ibasementPosition;
};

#endif //AOC_2015_DAY1_HPP_
