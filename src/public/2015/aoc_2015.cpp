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
    day4.reset();
}

void AoC2015::Day1() {
    string inputString;
    ifstream inputFile;

    cout << "--- Day 1: Not Quite Lisp ---\n";

    inputFile.open(R"(./input_data/2015/day1_input.txt)");

    int iFloor = 0;

    if ( inputFile.is_open() ) {
        inputFile >> inputString;

        iFloor = day1.findFloor(inputString);
    }

    inputFile.close();

    cout << "Floor: " << iFloor << "\n";
    cout << "Basement Position: " << day1.getBasementPosition() << "\n\n";
}

void AoC2015::Day2() {
    string inputString;
    ifstream inputFile;

    cout << "--- Day 2: I Was Told There Would Be No Math ---\n";

    inputFile.open(R"(./input_data/2015/day2_input.txt)");

    int iAreaOfPaperNeeded = 0;
    int iLengthOfRibbonNeeded = 0;
    int iSumAreaOfPaperNeeded = 0;
    int iSumLengthOfRibbonNeeded = 0;

    if (inputFile.is_open()) {
        while (getline(inputFile, inputString)) {
            day2.calcMaterialsNeeded(inputString);
            iAreaOfPaperNeeded = day2.getPresentPaper();
            iLengthOfRibbonNeeded = day2.getRibbonLength();

            if(iAreaOfPaperNeeded > 0) {
                iSumAreaOfPaperNeeded += iAreaOfPaperNeeded;
            }
            if(iLengthOfRibbonNeeded > 0) {
                iSumLengthOfRibbonNeeded += iLengthOfRibbonNeeded;
            }
        }
    }

    inputFile.close();

    cout << "Square feet of present paper: " << iSumAreaOfPaperNeeded << "\n";
    cout << "Feet of ribbon needed: " << iSumLengthOfRibbonNeeded << "\n\n";

}

void AoC2015::Day3() {
    string inputString;
    string inputFileLocation = R"(./input_data/2015/day3_input.txt)";
    ifstream inputFile;

    cout << "--- Day 3: Perfectly Spherical Houses in a Vacuum ---\n";

    inputFile.open(inputFileLocation);

    unsigned int uiHousesVisitedSoloSanta = 0;
    unsigned int uiPresentsDeliveredSoloSanta = 0;
    unsigned int uiHousesVisitedWRoboSanta = 0;
    unsigned int uiPresentsDeliveredWRoboSanta = 0;

    if (inputFile.is_open()) {
        while (getline(inputFile, inputString)) {
            day3.deliveryDirections(inputString);
        }

        uiHousesVisitedSoloSanta = day3.getTotalHousesVisited();
        uiPresentsDeliveredSoloSanta = day3.getTotalDeliveries();
    }

    inputFile.close();

    cout << "Houses delivered to as Solo Santa: " << uiHousesVisitedSoloSanta << "\n";
    cout << "Presents delivered as Solo Santa: " << uiPresentsDeliveredSoloSanta << "\n";

    inputFile.open(inputFileLocation);

    day3.activateRobot();

    if (inputFile.is_open()) {
        while (getline(inputFile, inputString)) {
            day3.deliveryDirections(inputString);
        }

        uiHousesVisitedWRoboSanta = day3.getTotalHousesVisited();
        uiPresentsDeliveredWRoboSanta = day3.getTotalDeliveries();
    }

    inputFile.close();

    cout << "Houses delivered to with Robo Santa: " << uiHousesVisitedWRoboSanta << "\n";
    cout << "Presents delivered with Robo Santa: " << uiPresentsDeliveredWRoboSanta << "\n\n";
}

void AoC2015::Day4() {
    string inputString;
    string inputFileLocation = R"(./input_data/2015/day4_input.txt)";
    ifstream inputFile;
    int intCode;

    cout << "--- Day 4: The Ideal Stocking Stuffer ---\n";

    inputFile.open(inputFileLocation);

    if (inputFile.is_open()) {
        while (getline(inputFile, inputString)) {
            intCode = day4.md5LeadingZeroes(inputString, 5);
            day4.reset();

            cout << "Int Code for 5 Leading Zeroes: " << intCode << "\n";

            intCode = day4.md5LeadingZeroes(inputString, 6);

            cout << "Int Code for 6 Leading Zeroes: " << intCode << "\n";
        }
    }

    inputFile.close();
}

void AoC2015::Day7() {
    string inputString;
    string inputFileLocation = R"(./input_data/2015/day7_input.txt)";
    ifstream inputFile;

    cout << "--- Day 7: Some Assembly Required ---\n";

    inputFile.open(inputFileLocation);

    if (inputFile.is_open()) {
        while (getline(inputFile, inputString)) {
//            intCode = day4.md5LeadingZeroes(inputString, 5);
//            day4.reset();

        }
    }

    inputFile.close();
}

string AoC2015::AoC2015GetVersion() {
    return AOC_2015_VERSION + to_string(AOC_2015_BUILD_NUM);
}
