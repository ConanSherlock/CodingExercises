#include "aoc_2015.hpp"

using namespace aoc_2015;
// as
AoC2015::AoC2015(){
    day1.reset();
}

AoC2015::~AoC2015() = default;

void AoC2015::reset(){
    day1.reset();
}

void AoC2015::Day1() {
    string inputString;
    ifstream inputFile;
    inputFile.open(R"(./input_data/2015/day1_input.txt)");

    int actualFloor = 0;
    int actualBasementPosition = 0;

    if ( inputFile.is_open() ) {
        inputFile >> inputString;

        actualFloor = day1.findFloor(inputString);
    }

    cout << "Floor: " << actualFloor << "\n";

    actualBasementPosition = day1.getBasementPosition();

    cout << "Basement Position: " << actualBasementPosition << "\n";

    reset();
}

string AoC2015::AoC2015GetVersion() {
    return AOC_2015_VERSION + to_string(AOC_2015_BUILD_NUM);
}
