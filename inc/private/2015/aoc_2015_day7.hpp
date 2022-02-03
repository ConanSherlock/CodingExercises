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
    Which takes in a strings containing wire definitions of a circuit in the form of an expression an assignment
    deliminator( -> ) and a wire name. The expression can be a uint16_t value, a wire or an expression such as
     1. NOT value/wire
     2. value/wire OR value/wire
     3. value/wire AND value/wire
     4. value/wire LSHIFT value/wire
     5. value/wire RSHIFT value/wire
    then these are evaluated recursively to valuate the values of all wires in the circuit.
*/
class AoC2015Day7 {
public:

    /*!
        Constructor and Destructor
    */
    AoC2015Day7();
    ~AoC2015Day7();

    /*!
        Function to reset the values of the class
        \return void
    */
    void reset();

    /*!
        Function to add a new string to the circuit, invalid strings will be ignored and may leave 0 values causing
        potentially unwanted behaviour
        \return void
    */
    void buildCircuit(string &sInputString);

    /*!
        Function to evalaute the current circuit
        \return void
    */
    void evaluateCircuit();

    /*!
        Function to change a wire already built into the circuit
        \return void
    */
    void changeWireInfo(const string &sKey, const wireInfo &wI_NewInfo);

    /*!
        Function to return the current circuit map
        \return  multimap<string, wireInfo> Circuit map
    */
    multimap<string, wireInfo> getCircuitMap();

private:
    /*!
        Function to create a component entry based on the wire equation
        \return void
    */
    void createComponentEntry(string &sComponent);

    /*!
        Function to evaluate all wires based on the created component equations
        \return void
    */
    void evaluateWire(wireInfo &wI_InputWireInfo);

    /*!
        Function to check a wire expression to see if it contains a direct uint16_t value as a direct assignment
        and creates a dummy expression of the evaluation or sets the pointer to the wire info in the key
        \return void
    */
    void checkForValue(wireInfo **pwI_WireInfo, const string &sKey, wireInfo &wI_WireInfo);

    /*!
        Function to implement the Not Operation and set the wire as evaluated
        \return void
    */
    static void notOperation(wireInfo *wI_InputWire, wireInfo &wI_OutputWire);

    /*!
        Function to implement the And Operation and set the wire as evaluated
        \return void
    */
    static void andOperation(wireInfo *wI_InputWire1, wireInfo *wI_InputWire2, wireInfo &wI_OutputWire);

    /*!
        Function to implement the Or Operation and set the wire as evaluated
        \return void
    */
    static void orOperation(wireInfo *wI_InputWire1, wireInfo *wI_InputWire2, wireInfo &wI_OutputWire);

    /*!
        Function to implement the LShift Operation and set the wire as evaluated
        \return void
    */
    static void lShiftOperation(wireInfo *wI_InputWire1, wireInfo *wI_InputWire2, wireInfo &wI_OutputWire);

    /*!
        Function to implement the RShift Operation and set the wire as evaluated
        \return void
    */
    static void rShiftOperation(wireInfo *wI_InputWire1, wireInfo *wI_InputWire2, wireInfo &wI_OutputWire);

    vector<string> svecCircuitComponent;
    multimap<string, wireInfo> mmssWireMap;
};

#endif //CPP_AOC_2015_DAY7_H
