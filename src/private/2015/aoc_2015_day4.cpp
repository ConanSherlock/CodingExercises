//
// Created by conan on 11/12/2021.
//

#include "aoc_2015_day4.hpp"

AoC2015Day4::AoC2015Day4() {
    bDebugPrint = false;
    iLeadingZeroCount=0;
    iIntCode=-1;
}

void AoC2015Day4::reset() {
    bDebugPrint = false;
    iLeadingZeroCount=0;
    iIntCode=-1;
}

int AoC2015Day4::md5LeadingZeroes(string &inputString, int leadingZeroes) {
    string md5Input;
    const byte *digest;

    for (uint32_t i = 0; i < UINT32_MAX; i++) {
        md5Input = inputString + to_string(i);

        cout << md5Input;

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
                iIntCode = int(j);
                break;
            } else {
                iIntCode = int(j);
                break;
            }
        }

        if (iLeadingZeroCount >= leadingZeroes) {
            break;
        } else {
            iLeadingZeroCount = 0;
            iIntCode= -1;
        }
    }

    return iIntCode;
}

int AoC2015Day4::getSecretCode() const {
    return iIntCode;
}

int AoC2015Day4::getLeadingZeroes() const {
    return iLeadingZeroCount;
}

AoC2015Day4::~AoC2015Day4() = default;