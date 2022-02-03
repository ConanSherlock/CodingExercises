#include "aoc_2015_day2.hpp"

AoC2015Day2::AoC2015Day2() {
    iLength = 0;
    iWidth = 0;
    iHeight = 0;
    iSmallestArea = -1;
    iTotalSurfaceArea = -1;
    iBowLength = -1;
    rgxRegExDimensionInput = (R"((\d+)x(\d+)x(\d+))");
}

void AoC2015Day2::calcMaterialsNeeded(string &sInputString) {
    smatch digitMatch;
    vector<int> ivecAreaOfSides;
    vector<int> ivecDimensions;

    int iTempArea1;
    int iTempArea2;
    int iTempArea3;

    if(regex_match(sInputString, rgxRegExDimensionInput)){
        regex_search(sInputString, digitMatch, rgxRegExDimensionInput);

        iLength = stoi(digitMatch.str(LENGTH_POSITION));
        iWidth = stoi(digitMatch.str(WIDTH_POSITION));
        iHeight = stoi(digitMatch.str(HEIGHT_POSITION));

        ivecDimensions = {iLength, iWidth, iHeight};

        std::sort(ivecDimensions.begin(), ivecDimensions.end());

        iBowLength = ivecDimensions[0]*2 + ivecDimensions[1]*2 + iLength * iWidth * iHeight;

        iTempArea1 = iLength * iWidth;
        iTempArea2 = iWidth * iHeight;
        iTempArea3 = iHeight * iLength;

        iTotalSurfaceArea = 2 * iTempArea1 + 2 * iTempArea2 + 2 * iTempArea3;
        ivecAreaOfSides = {iTempArea1, iTempArea2, iTempArea3};

        iSmallestArea = *&*min_element(ivecAreaOfSides.begin(), ivecAreaOfSides.end());
    } else{
        iTotalSurfaceArea = -1;
        iSmallestArea = -1;
    }
}

int AoC2015Day2::getPresentPaper() const{
    return iTotalSurfaceArea+iSmallestArea;
}

int AoC2015Day2::getRibbonLength() const{
    return iBowLength;
}

void AoC2015Day2::reset(){
    iLength = 0;
    iWidth = 0;
    iHeight = 0;
    iSmallestArea = -1;
    iTotalSurfaceArea = -1;
    iBowLength = -1;
    rgxRegExDimensionInput = (R"((\d+)x(\d+)x(\d+))");
}

AoC2015Day2::~AoC2015Day2() = default;
