//
// Created by conan on 11/12/2021.
//

#include "aoc_2015_day8.hpp"

AoC2015Day8::AoC2015Day8() {
    u32CharsInMem = 0;
    u32CharsInStringCode = 0;
}

void AoC2015Day8::reset() {
    u32CharsInMem = 0;
    u32CharsInStringCode = 0;
}

void AoC2015Day8::evaluateString(const string &sInputString) {
    uint16_t skipChars = 0;
    u32CharsInMem = 0;
    u32CharsInStringCode = 2;

    for (int i=1; i<sInputString.length()-1; ++i) {
        if(skipChars > 0){
            --skipChars;
            continue;
        }

        ++u32CharsInStringCode;
        ++u32CharsInMem;

        if(sInputString[i] == '\\'){
            if(sInputString[i+1] == 'x'){
                skipChars = 3;
                u32CharsInStringCode += 3;
            } else {
                ++u32CharsInStringCode;
                skipChars = 1;
            }
        }
        // TODO read string literal character by character
        // TODO If \x plus 2 char hex code is 1 actual character and 4 code characters
        // TODO else if \ + escaped character should be 1 actual character but 2 code characters
        // TODO else just add one character

    }
}

uint32_t AoC2015Day8::getCharsStringCode() {
    return u32CharsInStringCode;
}

uint32_t AoC2015Day8::getCharsInMem() {
    return u32CharsInMem;
}

AoC2015Day8::~AoC2015Day8() = default;