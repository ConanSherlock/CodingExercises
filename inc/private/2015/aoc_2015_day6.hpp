//
// Created by conan on 11/02/2021.
//

#ifndef CPP_AOC_2015_DAY6_H
#define CPP_AOC_2015_DAY6_H

#include <string>
#include <iostream>
#include <regex>

#define LIGHTS_ON "on"
#define LIGHTS_OFF "off"
#define NUMBER_OF_ROWS 1000
#define NUMBER_OF_COLUMNS 1000
#define INDEX_SIZE_OFFSET 1
#define TOGGLE_INCREASE 2
#define TURN_CHANGE 1

enum lightMatchPosition
{
    OFF_ON_POSITION = 1,
    START_X_POSITION = 2,
    START_Y_POSITION = 3,
    END_X_POSITION = 4,
    END_Y_POSITION = 5
};


using namespace std;

/*!
    Class to implement the solution to AoC 2015 Day 4
*/

class AoC2015Day6 {
public:
    /*!
        Constructor and Destructor
    */
    AoC2015Day6();
    ~AoC2015Day6();

    void reset();

    void updateLightsPartA(string &inputString);
    void updateLightsPartB(string &inputString);

    int getNumberOfLightsOn();
    int getTotalBrightness();


private:
    uint8_t lightsArray[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS]{};
    int numLights;
    int totalBrightness;
    uint16_t ui16StartX;
    uint16_t ui16StartY;
    uint16_t ui16EndX;
    uint16_t ui16EndY;
    regex rgxRegExLightsToggleCommandInput;
    regex rgxRegExLightsTurnCommandInput;
};

#endif //CPP_AOC_2015_DAY6_H
