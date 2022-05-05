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
    u32CharsInStringCode = sInputString.length();

    for (unsigned int i=1; i<sInputString.length()-1; ++i) {
        if(skipChars > 0){
            --skipChars;
            continue;
        }

        ++u32CharsInMem;

        if(sInputString[i] == '\\'){
            if(sInputString[i+1] == 'x'){
                skipChars = 3;
            } else {
                skipChars = 1;
            }
        }
    }
}

void AoC2015Day8::evaluateEncodedString(const string &sInputString) {
    string encodedInput = "\"";
    int skipChars = 0;

    u32CharsInMem = 0;
    u32CharsInStringCode = sInputString.length();

    for (unsigned int i=0; i<sInputString.length(); ++i) {
        if(skipChars > 0){
            encodedInput += sInputString[i];
            --skipChars;
            continue;
        }

        if(sInputString[i] == '\"'){
            encodedInput.append("\\\"");
            continue;
        } else if(sInputString[i] == '\\'){
            encodedInput.append("\\\\");

            if(i+1>=sInputString.length()) {
                return;
            }

            if(sInputString[i+1] == 'x'){
                if(i+3 >= sInputString.length()){
                    return;
                }

                if(isdigit(sInputString[i+3])&&isdigit(sInputString[i+2])){
                    skipChars = 3;
                }else if (isdigit(sInputString[i+2])){
                    skipChars = 2;
                } else{
                    skipChars = 0;
                }
                ++u32CharsInMem;
                continue;
            }
        } else{
            encodedInput += sInputString[i];
        }
        ++u32CharsInMem;
    }

    encodedInput += "\"";

    u32CharsInStringCode = encodedInput.length();
}

uint32_t AoC2015Day8::getCharsStringCode() {
    return u32CharsInStringCode;
}

uint32_t AoC2015Day8::getCharsInMem() {
    return u32CharsInMem;
}

AoC2015Day8::~AoC2015Day8() = default;