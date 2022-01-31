//
// Created by conan on 01/01/2022.
//

#include "santa_2015.hpp"

Santa2015::Santa2015() {
  Reset();
}

Santa2015::~Santa2015() = default;

void Santa2015::XCoordsMovement(int x) {
    iSantaXCoords += x;
}

void Santa2015::YCoordsMovement(int y) {
    iSantaYCoords += y;
}

int Santa2015::GetXCoords() const {
    return iSantaXCoords;
}

int Santa2015::GetYCoords() const {
    return iSantaYCoords;
}

void Santa2015::Reset() {
    iSantaXCoords = 0;
    iSantaYCoords = 0;
}

bool Santa2015::Movement(char movement) {
    bool bSuccess = false;

    switch (movement) {
        case NORTH:
            YCoordsMovement(1);
            bSuccess = true;
            break;
        case SOUTH:
            YCoordsMovement(-1);
            bSuccess = true;
            break;
        case EAST:
            XCoordsMovement(1);
            bSuccess = true;
            break;
        case WEST:
            XCoordsMovement(-1);
            bSuccess = true;
            break;
        default:
            break;
    }
    return bSuccess;
}
