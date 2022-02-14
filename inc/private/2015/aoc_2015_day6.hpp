//
// Created by conan on 11/02/2021.
//

#ifndef CPP_AOC_2015_DAY6_H
#define CPP_AOC_2015_DAY6_H

#include <string>
#include <iostream>
#include <regex>

#define NUMBER_OF_ROWS 1000
#define NUMBER_OF_COLUMNS 1000

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
    Class to implement the solution to AoC 2015 Day 6
*/
class AoC2015Day6 {
public:
    /*!
        Constructor and Destructor
    */
    AoC2015Day6(){
        numLights = 0;
        totalBrightness = 0;
        ui16StartX = UINT16_MAX;
        ui16StartY = UINT16_MAX;
        ui16EndX = UINT16_MAX;
        ui16EndY = UINT16_MAX;
        rgxRegExLightsToggleCommandInput = (R"((toggle) (\d+),(\d+) through (\d+),(\d+))");
        rgxRegExLightsTurnCommandInput = (R"(turn (\w+) (\d+),(\d+) through (\d+),(\d+))");
        memset(lightsArray, false, NUMBER_OF_ROWS * NUMBER_OF_COLUMNS * sizeof(bool));
    }

    ~AoC2015Day6();

    /*!
        Function to reset the values of the class
        \return void
    */
    void reset();

    /*!
        Function to take in a string and update the lights array based on its value for part A
        \return void
    */
    void updateLightsPartA(string const &inputString);

    /*!
        Function to take in a string and update the lights array based on its value for part B
        \return void
    */
    void updateLightsPartB(string const &inputString);

    /*!
        Function to return the number of lights on in the light array for the answer for part A
        \return int
    */
    int getNumberOfLightsOn();

    /*!
        Function to return the brightness value of the light array for the answer for part B
        \return int
    */
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
