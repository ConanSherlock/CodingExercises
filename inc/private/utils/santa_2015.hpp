//
// Created by conan on 01/01/2022.
//

#ifndef CPP_SANTA_2015_H
#define CPP_SANTA_2015_H

enum moveHouse
{
    NORTH = '^',
    SOUTH = 'v',
    EAST = '>',
    WEST = '<'
};


class Santa2015 {
public:
    /*!
        Constructor and Destructor
    */
    Santa2015();
    ~Santa2015();

    bool Movement(char movement);

    int GetXCoords() const;     // NOLINT
    int GetYCoords() const;     // NOLINT
    void Reset();

private:
    void XCoordsMovement(int x);
    void YCoordsMovement(int y);

    int iSantaXCoords;
    int iSantaYCoords;

};

#endif //CPP_SANTA_2015_H
