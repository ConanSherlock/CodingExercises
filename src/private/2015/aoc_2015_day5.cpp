//
// Created by conan on 11/12/2021.
//

#include "aoc_2015_day5.hpp"

#define VOWELS {"a", "e", "i", "o", "u"}
#define FORBIDDEN_SUBSTRINGS {"ab", "cd", "pq", "xy"}
#define REQUIRED_VOWELS 3
#define SUBSTRING_SIZE 2
#define DISPLACEMENT_TO_NEXT_CHAR 2


void AoC2015Day5::reset() {
    bVowelsFound = false;
    bRepeatLetterFound = false;
    bTwoLettersFoundTwice = false;
    u32NiceCount = 0;
    beh_Behaviour = UNKNOWN;
}

behaviour AoC2015Day5::checkNaughtyOrNiceV1(string const &sInputString) {
    string sub_string;
    int vowelsFound = 0;
    bVowelsFound = false;
    bRepeatLetterFound = false;

    for(auto it = sInputString.begin(); it != sInputString.end(); it++){

        for(string sBadSubstring : FORBIDDEN_SUBSTRINGS) {
            sub_string = {*it, *(it+1)};
            if(it != sInputString.end()) {
                if (sub_string == sBadSubstring) {
                    beh_Behaviour = NAUGHTY;
                    return beh_Behaviour;
                }
            }
        }

        for(string sVowel : VOWELS) {
            if(sVowel[0] == *it){
                vowelsFound++;
            }
            if(vowelsFound>=REQUIRED_VOWELS){
                bVowelsFound = true;
            }
        }

        if(it != sInputString.end() && !bRepeatLetterFound){
            if(*it == *(it+1)){
                bRepeatLetterFound=true;
            }
        }
    }

    if(bVowelsFound && bRepeatLetterFound){
        beh_Behaviour = NICE;
        u32NiceCount++;
    } else{
        beh_Behaviour = NAUGHTY;
    }

    return beh_Behaviour;
}

behaviour AoC2015Day5::checkNaughtyOrNiceV2(string const &sInputString) {
    size_t stringPosition;
    string tempSubstring;
    bVowelsFound = false;
    bRepeatLetterFound = false;
    bTwoLettersFoundTwice = false;

    for(uint32_t i = 0; i<sInputString.length(); i++){
        if(i+2<sInputString.length()) {
            tempSubstring = sInputString.substr(i, SUBSTRING_SIZE);
            stringPosition = sInputString.find(tempSubstring, i + SUBSTRING_SIZE);
            if (stringPosition >= i+SUBSTRING_SIZE && stringPosition != SIZE_MAX){
                bTwoLettersFoundTwice = true;
            }
        }

        if(i+1<sInputString.length() && !bRepeatLetterFound){
            if(sInputString[i] == sInputString[i+DISPLACEMENT_TO_NEXT_CHAR]){
                bRepeatLetterFound=true;
            }
        }
    }

    if(bTwoLettersFoundTwice && bRepeatLetterFound){
        beh_Behaviour = NICE;
        u32NiceCount++;
    } else{
        beh_Behaviour = NAUGHTY;
    }

    return beh_Behaviour;
}


uint32_t AoC2015Day5::getNiceCount() const {
    return u32NiceCount;
}

AoC2015Day5::~AoC2015Day5() = default;