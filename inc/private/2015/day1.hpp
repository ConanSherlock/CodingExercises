#ifndef AOC_2015_DAY1_HPP_
#define AOC_2015_DAY1_HPP_

/* Includes section
 **********************************************************************************************************************/
#include <string>
#include <iostream>


using namespace std;

class AoC2015Day1 {
public:

    AoC2015Day1();
    ~AoC2015Day1();
    int findFloor(string &inputString);
    void reset();

private:
    int floorNumber;
};

#endif //AOC_2015_DAY1_HPP_
