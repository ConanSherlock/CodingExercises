//
// Created by conan on 11/02/2021.
//

#include "aoc_2015_day6.hpp"

#define LIGHTS_ON "on"
#define LIGHTS_OFF "off"
#define INDEX_SIZE_OFFSET 1
#define TOGGLE_INCREASE 2
#define TURN_CHANGE 1

void AoC2015Day6::reset() {
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

void AoC2015Day6::updateLightsPartA(string const &inputString) {
    smatch matches;
    string on_off_string;

    if (regex_match(inputString, rgxRegExLightsToggleCommandInput)) {
        regex_search(inputString, matches, rgxRegExLightsToggleCommandInput);

        ui16StartX = stoi(matches.str(START_X_POSITION));
        ui16StartY = stoi(matches.str(START_Y_POSITION));
        ui16EndX = stoi(matches.str(END_X_POSITION));
        ui16EndY = stoi(matches.str(END_Y_POSITION));

        for(uint16_t i=ui16StartX; i <= ui16EndX; i++){
            for(uint16_t j=ui16StartY; j <= ui16EndY; j++){
                lightsArray[i][j] = !lightsArray[i][j];
            }
        }

    } else if(regex_match(inputString, rgxRegExLightsTurnCommandInput)) {
        regex_search(inputString, matches, rgxRegExLightsTurnCommandInput);

        on_off_string = matches.str(OFF_ON_POSITION);
        ui16StartX = stoi(matches.str(START_X_POSITION));
        ui16StartY = stoi(matches.str(START_Y_POSITION));
        ui16EndX = stoi(matches.str(END_X_POSITION));
        ui16EndY = stoi(matches.str(END_Y_POSITION));

        if(on_off_string == LIGHTS_ON){
            for(uint16_t i=ui16StartX; i <= ui16EndX; i++){
                memset(*(lightsArray + i) + ui16StartY, true, (ui16EndY - ui16StartY + INDEX_SIZE_OFFSET) * sizeof(bool));
            }
        }else if(on_off_string == LIGHTS_OFF){
            for(uint16_t i=ui16StartX; i <= ui16EndX; i++){
                memset(*(lightsArray + i) + ui16StartY, false, (ui16EndY - ui16StartY + INDEX_SIZE_OFFSET) * sizeof(bool));
            }
        }

    }
}

void AoC2015Day6::updateLightsPartB(string const &inputString) {
    smatch matches;
    string on_off_string;

    if (regex_match(inputString, rgxRegExLightsToggleCommandInput)) {
        regex_search(inputString, matches, rgxRegExLightsToggleCommandInput);

        ui16StartX = stoi(matches.str(START_X_POSITION));
        ui16StartY = stoi(matches.str(START_Y_POSITION));
        ui16EndX = stoi(matches.str(END_X_POSITION));
        ui16EndY = stoi(matches.str(END_Y_POSITION));

        for(uint16_t i=ui16StartX; i <= ui16EndX; i++){
            for(uint16_t j=ui16StartY; j <= ui16EndY; j++){
                lightsArray[i][j] += TOGGLE_INCREASE;
            }
        }

    } else if(regex_match(inputString, rgxRegExLightsTurnCommandInput)) {
        regex_search(inputString, matches, rgxRegExLightsTurnCommandInput);

        on_off_string = matches.str(OFF_ON_POSITION);
        ui16StartX = stoi(matches.str(START_X_POSITION));
        ui16StartY = stoi(matches.str(START_Y_POSITION));
        ui16EndX = stoi(matches.str(END_X_POSITION));
        ui16EndY = stoi(matches.str(END_Y_POSITION));

        if(on_off_string == LIGHTS_ON){
            for(uint16_t i=ui16StartX; i <= ui16EndX; i++){
                for(uint16_t j=ui16StartY; j <= ui16EndY; j++){
                    lightsArray[i][j] += TURN_CHANGE;
                }
            }
        }else if(on_off_string == LIGHTS_OFF){
            for(uint16_t i=ui16StartX; i <= ui16EndX; i++){
                for(uint16_t j=ui16StartY; j <= ui16EndY; j++){
                    if(lightsArray[i][j]>0) {
                        lightsArray[i][j] -= TURN_CHANGE;
                    }
                }
            }
        }

    }
}

int AoC2015Day6::getNumberOfLightsOn(){
    numLights = 0;

    for(auto & lightRow : lightsArray){
        for(uint8_t light : lightRow){
            if(light){
                numLights++;
            }
        }
    }
    return numLights;
}

int AoC2015Day6::getTotalBrightness() {
    totalBrightness = 0;

    for(auto & lightRow : lightsArray){
        for(uint8_t light : lightRow){
            if(light){
                totalBrightness+=light;
            }
        }
    }
    return totalBrightness;
}

AoC2015Day6::~AoC2015Day6() = default;