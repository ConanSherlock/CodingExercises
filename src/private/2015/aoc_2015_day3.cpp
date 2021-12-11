//
// Created by conan on 11/12/2021.
//

#include "aoc_2015_day3.hpp"

AoC2015Day3::AoC2015Day3() {
    iXCoords = 0;
    iYCoords = 0;
    iTotalDeliveries = 1;
    uiTotalHousesVisited = 1;
    mmsiHouseMap.insert({convertCordsToKey(), 1});
}

void AoC2015Day3::deliveryDirections(string &inputString) {
    uiTotalHousesVisited = mmsiHouseMap.size();
}

int AoC2015Day3::getTotalDeliveries() const {
    return iTotalDeliveries;
}

unsigned int AoC2015Day3::getTotalHousesVisited() const {
    return uiTotalHousesVisited;
}

string AoC2015Day3::convertCordsToKey() const {
    return "X:" + to_string(iXCoords) + " Y:" + to_string(iYCoords) ;
}

void AoC2015Day3::reset(){
    iXCoords = 0;
    iYCoords = 0;
    iTotalDeliveries = 1;
    uiTotalHousesVisited = 1;
    mmsiHouseMap.clear();
    mmsiHouseMap.insert({convertCordsToKey(), 1});
}

AoC2015Day3::~AoC2015Day3() = default;