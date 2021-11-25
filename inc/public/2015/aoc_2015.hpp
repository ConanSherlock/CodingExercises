#ifndef AOC_2015_HPP_
#define AOC_2015_HPP_

/* Includes section
 **********************************************************************************************************************/
#include <string>
#include <iostream>
#include <fstream>
#include "aoc15day1.hpp"
#include "aoc_2015_version.hpp"

using namespace std;
namespace aoc_2015 {
#define EXPORT_API __declspec(dllexport)
}


class EXPORT_API AoC2015 {
public:

    // Constructor and Destructor
    AoC2015();
    ~AoC2015();

    void reset();

    void Day1();

    /*!
      Retrieves the version number of the 2015 implementation.
      \return The version identifier as a string
    */
    static string AoC2015GetVersion();
private:
    AoC2015Day1 day1;

};




#endif //AOC_2015_HPP_
