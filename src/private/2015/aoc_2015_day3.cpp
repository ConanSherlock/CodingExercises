//
// Created by conan on 11/12/2021.
//

#include "aoc_2015_day3.hpp"

AoC2015Day3::AoC2015Day3() {
    bRobotActivated = false;
    iSantaXCoords = 0;
    iSantaYCoords = 0;
    iRoboXCoords = 0;
    iRoboYCoords = 0;
    uiTotalDeliveries = 1;
    uiTotalHousesVisited = 1;
    mmsiHouseMap.insert({convertCordsToKey(false), 1});
}

void AoC2015Day3::activateRobot(){
    bRobotActivated = true;
    updateMap(true);
    bRobotDelivered = true;
}

void AoC2015Day3::deactivateRobot(){
    bRobotActivated = false;
}

void AoC2015Day3::deliveryDirections(string &inputString) {
    for(char i : inputString){
        if(bRobotActivated) {
            if(bRobotDelivered) {
                if (updateSantaPosition(i)) {
                    continue;
                }
                bRobotDelivered = false;
            } else {
                if (updateRoboSantaPosition(i)) {
                    continue;
                }
                bRobotDelivered = true;
            }
        } else{
            if(updateSantaPosition(i)){
                continue;
            }
        }
    }
    uiTotalHousesVisited = mmsiHouseMap.size();
}

bool AoC2015Day3::updateSantaPosition(char input){
    bool bBadInput = false;

    switch (input) {
        case NORTH:
            iSantaYCoords += 1;
            break;
        case SOUTH:
            iSantaYCoords -= 1;
            break;
        case EAST:
            iSantaXCoords += 1;
            break;
        case WEST:
            iSantaXCoords -= 1;
            break;
        default:
            bBadInput = true;
            break;
    }
    if(!bBadInput){
        updateMap(false);
    }

    return bBadInput;
}

bool AoC2015Day3::updateRoboSantaPosition(char input){
    bool bBadInput = false;

    switch (input) {
        case NORTH:
            iRoboYCoords += 1;
            break;
        case SOUTH:
            iRoboYCoords -= 1;
            break;
        case EAST:
            iRoboXCoords += 1;
            break;
        case WEST:
            iRoboXCoords -= 1;
            break;
        default:
            bBadInput = true;
            break;
    }
    if(!bBadInput){
        updateMap(true);
    }

    return bBadInput;
}

void AoC2015Day3::updateMap(bool robo){
    auto it = mmsiHouseMap.find(convertCordsToKey(robo));

    if(it == mmsiHouseMap.end()){
        mmsiHouseMap.insert({convertCordsToKey(robo), 1});
    } else{
        it->second += 1;
    }
    uiTotalDeliveries++;
}

int AoC2015Day3::getTotalDeliveries() const {
    return uiTotalDeliveries;
}

unsigned int AoC2015Day3::getTotalHousesVisited() const {
    return uiTotalHousesVisited;
}

string AoC2015Day3::convertCordsToKey(bool robo) const {
    if (robo){
        return "X:" + to_string(iRoboXCoords) + " Y:" + to_string(iRoboYCoords);
    } else{
        return "X:" + to_string(iSantaXCoords) + " Y:" + to_string(iSantaYCoords) ;
    }

}

void AoC2015Day3::reset(){
    bRobotActivated = false;
    iSantaXCoords = 0;
    iSantaYCoords = 0;
    iRoboXCoords = 0;
    iRoboYCoords = 0;
    uiTotalDeliveries = 1;
    uiTotalHousesVisited = 1;
    mmsiHouseMap.clear();
    mmsiHouseMap.insert({convertCordsToKey(false), 1});
}

AoC2015Day3::~AoC2015Day3() = default;