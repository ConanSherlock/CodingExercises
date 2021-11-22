#ifndef AOC_2015_HPP_
#define AOC_2015_HPP_

/* Includes section
 **********************************************************************************************************************/
#include <string>
#include <iostream>
#include "aoc_2015_version.hpp"

using namespace std;
namespace aoc_2015 {
#define EXPORT_API __declspec(dllexport)
}

/*!
      Retrieves the version number of the exe.
      \return The version identifier as a string
  */
EXPORT_API string AoC2015GetVersion();
#endif //AOC_2015_HPP_
