//
// Created by conan on 11/12/2021.
//

#ifndef CPP_AOC_2015_DAY7_H
#define CPP_AOC_2015_DAY7_H

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>
#include <map>
#include <cstdio>

using namespace std;

#define DELIMINATOR_WIRE_EQUATION " -> "
#define DELIMINATOR_WIRE_EXPRESSION " "
#define OPERATOR_AND "AND"
#define OPERATOR_OR "OR"
#define OPERATOR_LSHIFT "LSHIFT"
#define OPERATOR_RSHIFT "RSHIFT"
#define OPERATOR_NOT "NOT"

struct wireInfo{
    string equation;
    bool evaluated;
    uint16_t value;
};

/*!
    Class to implement the solution to AoC 2015 Day 7
*/

class AoC2015Day7 {
public:
    /*!
        Constructor and Destructor
    */
    AoC2015Day7();
    ~AoC2015Day7();

    void reset();
    void buildCircuit(string &inputString);
    void evaluateCircuit();

private:
    void createComponentEntry(string &component);
    void evaluateWire(wireInfo &inputWireInfo);

    vector<string> svecCircuitComponent;
    multimap<string, wireInfo> mmssWireMap;

    void NotOperation(wireInfo *inputWire, wireInfo &outputWire);

    static void AndOperation(wireInfo *inputWire1, wireInfo *inputWire2, wireInfo &outputWire);

    static void OrOperation(wireInfo *inputWire1, wireInfo *inputWire2, wireInfo &outputWire);

    static void LShiftOperation(wireInfo *inputWire1, wireInfo *inputWire2, wireInfo &outputWire);

    static void RShiftOperation(wireInfo *inputWire1, wireInfo *inputWire2, wireInfo &outputWire);
};

#endif //CPP_AOC_2015_DAY7_H
