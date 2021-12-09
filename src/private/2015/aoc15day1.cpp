#include "aoc15day1.hpp"

AoC2015Day1::AoC2015Day1() {
    ifloorNumber = 0;
    ibasementPosition = -1;
    iloopCount = 0;
}

int AoC2015Day1::findFloor(string &inputString) {
    for(char i : inputString){
        if(i == '('){
            ifloorNumber++;
        } else if (i == ')'){
            ifloorNumber--;
        }
        if(ifloorNumber < 0 && ibasementPosition < 0){
            ibasementPosition = iloopCount;
        }
        iloopCount++;
    }

    return ifloorNumber;
}

int AoC2015Day1::getBasementPosition() const{
    return ibasementPosition + 1;
}

void AoC2015Day1::reset(){
    ifloorNumber = 0;
    ibasementPosition = -1;
    iloopCount = 0;
}

AoC2015Day1::~AoC2015Day1() = default;
