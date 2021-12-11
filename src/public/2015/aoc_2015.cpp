#include "aoc_2015.hpp"

using namespace aoc_2015;

AoC2015::AoC2015(){
    day1.reset();
    day2.reset();
    day3.reset();
}

AoC2015::~AoC2015() = default;

void AoC2015::reset(){
    day1.reset();
    day2.reset();
    day3.reset();
}

void AoC2015::Day1() {
    string inputString;
    ifstream inputFile;
    inputFile.open(R"(./input_data/2015/day1_input.txt)");

    int iFloor = 0;

    if ( inputFile.is_open() ) {
        inputFile >> inputString;

        iFloor = day1.findFloor(inputString);
    }

    inputFile.close();

    cout << "Floor: " << iFloor << "\n";
    cout << "Basement Position: " << day1.getBasementPosition() << "\n";
}

void AoC2015::Day2() {
    string inputString;
    ifstream inputFile;
    inputFile.open(R"(./input_data/2015/day2_input.txt)");

    int areaOfPaperNeeded = 0;
    int lengthOfRibbonNeeded = 0;
    int sumAreaOfPaperNeeded = 0;
    int sumLengthOfRibbonNeeded = 0;

    if (inputFile.is_open()) {
        while (getline(inputFile, inputString)) {
            day2.calcMaterialsNeeded(inputString);
            areaOfPaperNeeded = day2.getPresentPaper();
            lengthOfRibbonNeeded = day2.getRibbonLength();

            if(areaOfPaperNeeded > 0) {
                sumAreaOfPaperNeeded += areaOfPaperNeeded;
            }
            if(lengthOfRibbonNeeded > 0) {
                sumLengthOfRibbonNeeded += lengthOfRibbonNeeded;
            }
        }
    }

    inputFile.close();

    cout << "Square feet of present paper: " << sumAreaOfPaperNeeded << "\n";
    cout << "Feet of ribbon needed: " << sumLengthOfRibbonNeeded << "\n";

}

void AoC2015::Day3() {

}

string AoC2015::AoC2015GetVersion() {
    return AOC_2015_VERSION + to_string(AOC_2015_BUILD_NUM);
}
