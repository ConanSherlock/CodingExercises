//
// Created by conan on 11/12/2021.
//

#include "aoc_2015_day4.hpp"

AoC2015Day4::AoC2015Day4() {
    bDebugPrint = false;
    iLeadingZeroCount=0;
    ui32IntCode=0;
}

void AoC2015Day4::reset() {
    bDebugPrint = false;
    iLeadingZeroCount=0;
    ui32IntCode=0;
}

uint32_t AoC2015Day4::md5LeadingZeroes(string &sInputString, int iLeadingZeroes) {
    string md5Input;
    const byte *digest;

    for (uint32_t i = 1; i < UINT32_MAX; i++) {
        md5Input = sInputString + to_string(i);

        if(bDebugPrint) {
            cout << md5Input << "\n";
        }

        MD5 md5(md5Input);
        digest = md5.getDigest();

        if(bDebugPrint) {
            cout << "\n";
        }

        for (size_t j = 0; j < MAX_DIGEST_LENGTH; j++) {
            if(bDebugPrint) {
                cout << std::uppercase << std::hex << std::setfill('0') << std::setw(2)
                     << (((int) digest[j]) & 0xFF) << " ";
            }

            if (digest[j] == 0) {
                iLeadingZeroCount += 2;
            } else if (digest[j] < 10) {
                iLeadingZeroCount++;
                ui32IntCode = i;
                break;
            } else {
                ui32IntCode = i;
                break;
            }
        }

        if (iLeadingZeroCount >= iLeadingZeroes) {
            break;
        } else {
            iLeadingZeroCount = 0;
            ui32IntCode= 0;
        }
    }

    return ui32IntCode;
}

uint32_t AoC2015Day4::getSecretCode() const {
    return ui32IntCode;
}

int AoC2015Day4::getLeadingZeroes() const {
    return iLeadingZeroCount;
}

AoC2015Day4::~AoC2015Day4() = default;