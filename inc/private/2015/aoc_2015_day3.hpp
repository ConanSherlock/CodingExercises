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
        Function to take in the delivery directions and send them to Santa or Robot Santa
        \return void
    */
    void deliveryDirections(string &inputString);

    /*!
        Function to return the total amount of presents delivered to all houses
        \return unsigned int
    */
    int getTotalDeliveries() const;                         // NOLINT

    /*!
        Function to return the total amount houses that had presents delivered
        \return unsigned int
    */
    unsigned int getTotalHousesVisited() const;             // NOLINT

    /*!
        Function to activate robot Santa
        \return void
    */
    void activateRobot();

    /*!
        Function to deactivate robot Santa
        \return void
    */
    void deactivateRobot();

    /*!
        Function to reset class
        \return void
    */
    void reset();

private:

    /*!
        Function to convert the coordinates of Santa or Robo sant to a string to be used as a map key
        \return string
    */
    string convertCordsToStringKey(bool robo) const;        // NOLINT

    /*!
        Function to convert the coordinates of Santa or Robo sant to a string to be used as a map key
        \return void
    */
    void updateMap(bool robo);

    /*!
        Function to update the coordinates of Santa and deliver a present, returns a bool if input is not valid
        \return bool badInput
    */
    bool updateSantaPosition(char input);

    /*!
        Function to update the coordinates of Robo Santa and deliver a present, returns a bool if input is not valid
        \return bool badInput
    */
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
