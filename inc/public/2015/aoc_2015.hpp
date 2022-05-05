#ifndef AOC_2015_HPP_
#define AOC_2015_HPP_

/* Includes section
 **********************************************************************************************************************/
#include <string>
#include <iostream>
#include <fstream>
#include "aoc_2015_day1.hpp"
#include "aoc_2015_day2.hpp"
#include "aoc_2015_day3.hpp"
#include "aoc_2015_day4.hpp"
#include "aoc_2015_day5.hpp"
#include "aoc_2015_day6.hpp"
#include "aoc_2015_day7.hpp"
#include "aoc_2015_day8.hpp"
#include "aoc_2015_version.hpp"

using namespace std;
namespace aoc_2015 {
#define EXPORT_API __declspec(dllexport)
}


class EXPORT_API AoC2015 {
public:

    /*!
        Constructor and Destructor
    */
    AoC2015();
    ~AoC2015();

    /*!
        Function to reset the internal variables used in each Day.
        \return void
    */
    void reset();

    /*!
        Function to print the solution to Day 1.
        \return void
    */
    void Day1();

    /*!
        Function to print the solution to Day 2.
        \return void
    */
    void Day2();


    /*!
        Function to print the solution to Day 3.
        \return void
    */
    void Day3();

    /*!
        Function to print the solution to Day 4.
        \return void
    */
    void Day4();

    /*!
        Function to print the solution to Day 5.
        \return void
    */
    void Day5();

    /*!
        Function to print the solution to Day 6.
        \return void
    */
    void Day6();

    /*!
        Function to print the solution to Day 7.
        \return void
    */
    void Day7();

    /*!
        Function to print the solution to Day 8.
        \return void
    */
    void Day8();

    /*!
        Retrieves the version number of the 2015 implementation.
        \return The version identifier as a string
    */
    static string AoC2015GetVersion();
private:
    AoC2015Day1 day1;
    AoC2015Day2 day2;
    AoC2015Day3 day3;
    AoC2015Day4 day4;
    AoC2015Day5 day5;
    AoC2015Day6 day6;
    AoC2015Day7 day7;
    AoC2015Day8 day8;
};




#endif //AOC_2015_HPP_
