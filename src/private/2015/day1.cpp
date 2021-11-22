#include <cstring>
# include "day1.hpp"

AoC2015Day1::AoC2015Day1() {
    floorNumber = 0;
}

int AoC2015Day1::findFloor(string &inputString) {
    for(char i : inputString){
        if(i == '('){
            floorNumber++;
        } else if (i == ')'){
            floorNumber--;
        }
    }

    return floorNumber;
}

void AoC2015Day1::reset(){
    floorNumber = 0;
}

AoC2015Day1::~AoC2015Day1() = default;
