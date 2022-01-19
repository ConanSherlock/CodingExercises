//
// Created by conan on 11/12/2021.
//

#include "aoc_2015_day4.hpp"

AoC2015Day4::AoC2015Day4() {
    MAX_DIGEST_LENGTH = 16;
}

void AoC2015Day4::reset() {

}

void AoC2015Day4::basic(string &inputString, int stringLength) {
    string md5Input;
    const byte *digest;

    for(uint32_t i = 609040; i<UINT32_MAX; i++){
        md5Input = inputString + to_string(i);
        MD5 md5(md5Input);
        digest = md5.getDigest();

        for (size_t j = 0; j < MAX_DIGEST_LENGTH; j++) {
            cout << uppercase << hex << setfill('0') << setw(2) << (((int) digest[i]) & 0xFF) << " ";
        }
        break;
    }
}

AoC2015Day4::~AoC2015Day4() = default;