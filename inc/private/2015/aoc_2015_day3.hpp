//
// Created by conan on 11/12/2021.
//

#ifndef CPP_AOC_2015_DAY3_H
#define CPP_AOC_2015_DAY3_H
#include <string>
#include <map>
#include <iostream>

using namespace std;

enum move_house
{
    NORTH = '^',
    SOUTH = 'v',
    EAST = '>',
    WEST = '<'
};

/*!
    Class to implement the solution to AoC 2015 Day 3
    This class takes an input string of a combination of the characters '<', '^', 'v', '>' which each represent a
    direction for Santa to travel to a new house to deliver presents. Santa delivers one present to his start location
    and then will deliver one to each house he travels to even it is has already received a gift.
*/
class AoC2015Day3 {
public:
    /*!
        Constructor and Destructor
    */
    AoC2015Day3();
    ~AoC2015Day3();

    /*!
        Function to find the present paper area required and the length of string for tying the presents from an
        input string of the from LengthxWidthxHeight
        \return void
    */
    void deliveryDirections(string &inputString);

    int getTotalDeliveries() const;             // NOLINT

    unsigned int getTotalHousesVisited() const;          // NOLINT

    void activateRobot();

    void deactivateRobot();

    void reset();

private:

    string convertCordsToKey(bool robo) const;           // NOLINT

    void updateMap(bool robo);

    bool updateSantaPosition(char input);

    bool updateRoboSantaPosition(char input);

    int iSantaXCoords;
    int iRoboXCoords;
    int iSantaYCoords;
    int iRoboYCoords;
    int uiTotalDeliveries;
    bool bRobotActivated;
    bool bRobotDelivered;
    unsigned int uiTotalHousesVisited;
    multimap<string, int> mmsiHouseMap;
};


#endif //CPP_AOC_2015_DAY3_H
