#include "aoc_2015_day1.hpp"

const char * aoc2015Day1ExceptionToString(AOC_2015_DAY1_EXCEPTIONS type) {
    switch(type) {
        case INVALID_CHARACTER:
            return "\n Invalid Character in string";
        default:
            return "Unknown exception";
    }
}

AoC2015Day1::AoC2015Day1() {
    iFloorNumber = 0;
    iBasementPosition = -1;
    iLoopCount = 0;
}

int AoC2015Day1::findFloor(string &sInputString) {
    for(char i : sInputString){
        if(i == '('){
            iFloorNumber++;
        } else if (i == ')'){
            iFloorNumber--;
        } else{
            cerr << i << " is an invalid character\n";
            throw InvalidCharacter();
        }
        if(iFloorNumber < 0 && iBasementPosition < 0){
            iBasementPosition = iLoopCount;
        }
        iLoopCount++;
    }

    return iFloorNumber;
}

int AoC2015Day1::getBasementPosition() const{
    return iBasementPosition + 1;
}

void AoC2015Day1::reset(){
    iFloorNumber = 0;
    iBasementPosition = -1;
    iLoopCount = 0;
}

AoC2015Day1::~AoC2015Day1() = default;
