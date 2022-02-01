//
// Created by conan on 11/12/2021.
//

#include "aoc_2015_day3.hpp"

AoC2015Day3::AoC2015Day3() {
    Santa.Reset();
    RoboSanta.Reset();
    bRobotActivated = false;
    bRobotDelivered = false;
    iTotalDeliveries = 1;
    uiTotalHousesVisited = 1;
    mmsiHouseMap.insert({convertCordsToStringKey(false), 1});
}

void AoC2015Day3::activateRobot(){
    bRobotActivated = true;
    updateMap(true);
    bRobotDelivered = true;
}

void AoC2015Day3::deactivateRobot(){
    bRobotActivated = false;
}

void AoC2015Day3::deliveryDirections(string &sInputString) {
    for(char i : sInputString){
        updateSantaPosition(i);
    }
    uiTotalHousesVisited = mmsiHouseMap.size();
}

void AoC2015Day3::updateSantaPosition(char cInput){
    if(bRobotActivated) {
        if(bRobotDelivered) {
            if (Santa.Movement(cInput)) {
                updateMap(!bRobotDelivered);
                bRobotDelivered = false;
            }
        } else {
            if (RoboSanta.Movement(cInput)) {
                updateMap(!bRobotDelivered);
                bRobotDelivered = true;
            }
        }
    } else{
        if (Santa.Movement(cInput)) {
            updateMap(false);
        }
    }
}

void AoC2015Day3::updateMap(bool bRobo){
    auto it = mmsiHouseMap.find(convertCordsToStringKey(bRobo));

    if(it == mmsiHouseMap.end()){
        mmsiHouseMap.insert({convertCordsToStringKey(bRobo), 1});
    } else{
        it->second += 1;
    }
    iTotalDeliveries++;
}

int AoC2015Day3::getTotalDeliveries() const {
    return iTotalDeliveries;
}

unsigned int AoC2015Day3::getTotalHousesVisited() const {
    return uiTotalHousesVisited;
}

string AoC2015Day3::convertCordsToStringKey(bool bRobo) const {
    if (bRobo){
        return "X:" + to_string(RoboSanta.GetXCoords()) + " Y:" + to_string(RoboSanta.GetYCoords());
    } else{
        return "X:" + to_string(Santa.GetXCoords()) + " Y:" + to_string(Santa.GetYCoords());
    }

}

void AoC2015Day3::reset(){
    Santa.Reset();
    RoboSanta.Reset();
    bRobotActivated = false;
    bRobotDelivered = false;
    iTotalDeliveries = 1;
    uiTotalHousesVisited = 1;
    mmsiHouseMap.clear();
    mmsiHouseMap.insert({convertCordsToStringKey(false), 1});
}

AoC2015Day3::~AoC2015Day3() = default;