#ifndef AOC_2015_DAY2_HPP_
#define AOC_2015_DAY2_HPP_

/* Includes section
 **********************************************************************************************************************/
#include <string>
#include <iostream>
#include <regex>

using namespace std;

enum matchPosition
{
    LENGTH_POSITION = 1,
    WIDTH_POSITION = 2,
    HEIGHT_POSITION = 3
};

/*!
    Class to implement the solution to AoC 2015 Day 2
    This class takes an input string of IntxIntxInt representing the length, width and height of a perfect right
    rectangular prism. The wrapping paper needed to wrap the present which is the surface area + the area of the
    smallest side
*/
class AoC2015Day2 {
public:

    /*!
        Constructor and Destructor
    */
    AoC2015Day2();
    ~AoC2015Day2();

    /*!
        Function to find the present paper area required and the length of string for tying the presents from an
        input string of the from LengthxWidthxHeight
        \return void
    */
    void calcMaterialsNeeded(string &sInputString);

    /*!
        Function return the amount of present paper needed in square feet.
        \return int Total present paper
    */
    int getPresentPaper() const; // NOLINT

    /*!
        Function return the amount of ribbon needed in feet.
        \return int Ribbon length
    */
    int getRibbonLength() const; // NOLINT

    /*!
        Function to reset the internal variables used in Day 1.
        \return void
    */
    void reset();

private:
    int iLength;
    int iWidth;
    int iHeight;
    int iSmallestArea;              // Slack
    int iTotalSurfaceArea;
    int iBowLength;
    regex rgxRegExDimensionInput;
};

#endif //AOC_2015_DAY2_HPP_
