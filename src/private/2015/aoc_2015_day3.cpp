//
// Created by conan on 11/12/2021.
//

#include "aoc_2015_day3.hpp"

AoC2015Day3::AoC2015Day3() {
    Santa.Reset();
    RoboSanta.Reset();
    bRobotActivated = false;
    bRobotDelivered = false;
    uiTotalDeliveries = 1;
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

void AoC2015Day3::deliveryDirections(string &inputString) {
    for(char i : inputString){
        updateSantaPosition(i);
    }
    uiTotalHousesVisited = mmsiHouseMap.size();
}

void AoC2015Day3::updateSantaPosition(char input){
    if(bRobotActivated) {
        if(bRobotDelivered) {
            if (Santa.Movement(input)) {
                updateMap(!bRobotDelivered);
                bRobotDelivered = false;
            }
        } else {
            if (RoboSanta.Movement(input)) {
                updateMap(!bRobotDelivered);
                bRobotDelivered = true;
            }
        }
    } else{
        if (Santa.Movement(input)) {
            updateMap(false);
        }
    }
}

void AoC2015Day3::updateMap(bool robo){
    auto it = mmsiHouseMap.find(convertCordsToStringKey(robo));

    if(it == mmsiHouseMap.end()){
        mmsiHouseMap.insert({convertCordsToStringKey(robo), 1});
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

string AoC2015Day3::convertCordsToStringKey(bool robo) const {
    if (robo){
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
    uiTotalDeliveries = 1;
    uiTotalHousesVisited = 1;
    mmsiHouseMap.clear();
    mmsiHouseMap.insert({convertCordsToStringKey(false), 1});
}

AoC2015Day3::~AoC2015Day3() = default;