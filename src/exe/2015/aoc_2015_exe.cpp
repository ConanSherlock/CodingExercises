//
// Created by conans on 14/07/2021.
//
#include "aoc_2015.hpp"

int main() {
    AoC2015 aoc2015;

    cout << "Version number: " << AoC2015::AoC2015GetVersion() << "\n";

    aoc2015.Day1();
    aoc2015.Day2();

    aoc2015.reset();

    return 0;
}