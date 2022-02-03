//
// Created by conan on 11/12/2021.
//

#include "aoc_2015_day5.hpp"

AoC2015Day5::AoC2015Day5() {
    bVowelsFound = false;
    bRepeatLetterFound = false;
    bForbiddenStringFound = false;
    bTwoLettersFoundTwice = false;
    u32NiceCount = 0;
    beh_Behaviour = UNKNOWN;
}

void AoC2015Day5::reset() {
    bVowelsFound = false;
    bRepeatLetterFound = false;
    bForbiddenStringFound = false;
    bTwoLettersFoundTwice = false;
    u32NiceCount = 0;
    beh_Behaviour = UNKNOWN;
}

behaviour AoC2015Day5::checkNaughtyOrNiceV1(string &sInputString) {
    size_t badStringPosition;
    int vowelsFound = 0;
    bVowelsFound = false;
    bRepeatLetterFound = false;
    bForbiddenStringFound = false;

    for(uint32_t i = 0; i<sInputString.length(); i++){

        for(string sBadSubstring : FORBIDDEN_SUBSTRINGS) {
            badStringPosition = sInputString.find(sBadSubstring, i);
            if(badStringPosition!=SIZE_MAX){
                bForbiddenStringFound = true;
                break;
            }
        }

        if(bForbiddenStringFound){
            beh_Behaviour = NAUGHTY;
            break;
        }

        for(string sVowel : VOWELS) {
            if(sVowel[0] == sInputString[i]){
                vowelsFound++;
            }
        }

        if(vowelsFound>=REQUIRED_VOWELS){
            bVowelsFound = true;
        }

        if(i+1<sInputString.length() && !bRepeatLetterFound){
            if(sInputString[i] == sInputString[i+1]){
                bRepeatLetterFound=true;
            }
        }
    }

    if(!bForbiddenStringFound && bVowelsFound && bRepeatLetterFound){
        beh_Behaviour = NICE;
        u32NiceCount++;
    } else{
        beh_Behaviour = NAUGHTY;
    }

    return beh_Behaviour;
}

behaviour AoC2015Day5::checkNaughtyOrNiceV2(string &sInputString) {
    size_t stringPosition;
    string tempSubstring;
    bVowelsFound = false;
    bRepeatLetterFound = false;
    bTwoLettersFoundTwice = false;

    for(uint32_t i = 0; i<sInputString.length(); i++){
        if(i+2<sInputString.length()) {
            tempSubstring = sInputString.substr(i, 2);
            stringPosition = sInputString.find(tempSubstring, i + 2);
            if (stringPosition >= i+2 && stringPosition != SIZE_MAX){
                bTwoLettersFoundTwice = true;
            }
        }

        if(i+1<sInputString.length() && !bRepeatLetterFound){
            if(sInputString[i] == sInputString[i+2]){
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