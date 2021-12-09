#include "aoc_2015_day1.hpp"

AoC2015Day1::AoC2015Day1() {
    iFloorNumber = 0;
    iBasementPosition = -1;
    iLoopCount = 0;
}

int AoC2015Day1::findFloor(string &inputString) {
    for(char i : inputString){
        if(i == '('){
            iFloorNumber++;
        } else if (i == ')'){
            iFloorNumber--;
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
