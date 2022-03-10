//
// Created by conan on 11/12/2021.
//

#include "aoc_2015_day7.hpp"

AoC2015Day7::AoC2015Day7() = default;

void AoC2015Day7::reset() {
    svecCircuitComponent.clear();
    mmssWireMap.clear();

}

void AoC2015Day7::buildCircuit(string &sInputString) {
    svecCircuitComponent.push_back(sInputString);
}

void AoC2015Day7::evaluateCircuit() {
    for(auto & component : svecCircuitComponent) {
        createComponentEntry(component);
    }

    for (auto & entry : mmssWireMap) {
        evaluateWire(entry.second);
    }
}

void AoC2015Day7::createComponentEntry(string &sComponent) {
    size_t stPos;
    string sDeliminator = DELIMINATOR_WIRE_EQUATION;
    wireInfo wI_mapValue;

    if ((stPos = sComponent.find(sDeliminator)) != std::string::npos)
    {
        wI_mapValue.equation = sComponent.substr(0, stPos);
        wI_mapValue.evaluated = false;
        wI_mapValue.value = 0;

        sComponent.erase(0, stPos + sDeliminator.length());

        if(mmssWireMap.count(sComponent) == 0) {
            mmssWireMap.insert({sComponent, wI_mapValue});
        }
    }
}


void AoC2015Day7::evaluateWire(wireInfo &wI_InputWireInfo) {
    size_t stPos;
    string sDeliminator = DELIMINATOR_WIRE_EXPRESSION;
    wireInfo wI_DapValue;
    string sExpressionPart1;
    string sExpressionPart2;
    string sExpressionPart3;
    wireInfo *pwI_TempWire1Info;
    wireInfo *pwI_TempWire2Info;
    auto* TempWire1Info = (wireInfo *)malloc(sizeof(wireInfo));
    auto* TempWire2Info = (wireInfo *)malloc(sizeof(wireInfo));

    // Breaks up the wire expression based on the deliminator " " and decide which operation to implement.
    // Also, recursively calls this function if one of the input wire assignments has not been evaluated.
    if ((stPos = wI_InputWireInfo.equation.find(sDeliminator)) != std::string::npos)
    {
        sExpressionPart1 = wI_InputWireInfo.equation.substr(0, stPos);
        wI_InputWireInfo.equation.erase(0, stPos + sDeliminator.length());

        if(sExpressionPart1 == OPERATOR_NOT){
            checkForValue(&pwI_TempWire1Info, wI_InputWireInfo.equation, *TempWire1Info);

            if (!pwI_TempWire1Info->evaluated){
                evaluateWire(*pwI_TempWire1Info);
            }
            notOperation(pwI_TempWire1Info, wI_InputWireInfo);
        } else{
            if ((stPos = wI_InputWireInfo.equation.find(sDeliminator)) != std::string::npos)
            {
                sExpressionPart2 = wI_InputWireInfo.equation.substr(0, stPos);
                wI_InputWireInfo.equation.erase(0, stPos + sDeliminator.length());
            } else{
                // Invalid string check exiting function
                return;
            }

            sExpressionPart3 = wI_InputWireInfo.equation;

            // Check for possible invalid strings moved these checks here to avoid possible accessing memory outside
            // its scope
            if(mmssWireMap.count(sExpressionPart1) == 0) {
                for (char digit: sExpressionPart1) {
                    if (!isdigit(digit)) {
                        // Invalid string check exiting function
                        return;
                    }
                }
            }

            // Check for possible invalid strings moved these checks here to avoid possible accessing memory outside
            // its scope
            if(mmssWireMap.count(sExpressionPart3) == 0) {
                for (char digit: sExpressionPart3) {
                    if (!isdigit(digit)) {
                        // Invalid string check exiting function
                        return;
                    }
                }
            }

            if(mmssWireMap.count(sExpressionPart1) == 0){
                TempWire1Info->value = stoi(sExpressionPart1);
                TempWire1Info->evaluated = true;
                pwI_TempWire1Info = TempWire1Info;
            } else{
                pwI_TempWire1Info = &mmssWireMap.find(sExpressionPart1)->second;
            }

            if(mmssWireMap.count(sExpressionPart3) == 0){
                TempWire2Info->value = stoi(sExpressionPart3);
                TempWire2Info->evaluated = true;
                pwI_TempWire2Info = TempWire2Info;
            } else{
                pwI_TempWire2Info = &mmssWireMap.find(sExpressionPart3)->second;
            }

            if (!pwI_TempWire1Info->evaluated){
                evaluateWire(*pwI_TempWire1Info);
            }
            if (!pwI_TempWire2Info->evaluated){
                evaluateWire(*pwI_TempWire2Info);
            }

            if(sExpressionPart2 == OPERATOR_AND){
                andOperation(pwI_TempWire1Info, pwI_TempWire2Info, wI_InputWireInfo);
            } else if(sExpressionPart2 == OPERATOR_OR){
                orOperation(pwI_TempWire1Info, pwI_TempWire2Info, wI_InputWireInfo);
            } else if(sExpressionPart2 == OPERATOR_LSHIFT){
                lShiftOperation(pwI_TempWire1Info, pwI_TempWire2Info, wI_InputWireInfo);
            } else if(sExpressionPart2 == OPERATOR_RSHIFT){
                rShiftOperation(pwI_TempWire1Info, pwI_TempWire2Info, wI_InputWireInfo);
            }
        }
    } else{
        if(mmssWireMap.count(wI_InputWireInfo.equation) == 0){

            for(char digit : wI_InputWireInfo.equation){
                if(!isdigit(digit)){
                    // invalid string
                    return;
                }
            }

            TempWire1Info->value = stoi(wI_InputWireInfo.equation);
            TempWire1Info->evaluated = true;
            pwI_TempWire1Info = TempWire1Info;
        } else{
            pwI_TempWire1Info = &mmssWireMap.find(wI_InputWireInfo.equation)->second;
        }

        if (!pwI_TempWire1Info->evaluated){
            evaluateWire(*pwI_TempWire1Info);
        }

        wI_InputWireInfo.value = pwI_TempWire1Info->value;
        wI_InputWireInfo.evaluated = true;
    }
    free(TempWire1Info);
    free(TempWire2Info);
}

void AoC2015Day7::notOperation(wireInfo *wI_InputWire, wireInfo &wI_OutputWire){
    wI_OutputWire.value = ~wI_InputWire->value;
    wI_OutputWire.evaluated = true;
}

void AoC2015Day7::andOperation(wireInfo *wI_InputWire1, wireInfo *wI_InputWire2, wireInfo &wI_OutputWire){
    wI_OutputWire.value = wI_InputWire1->value & wI_InputWire2->value;
    wI_OutputWire.evaluated = true;
}

void AoC2015Day7::orOperation(wireInfo *wI_InputWire1, wireInfo *wI_InputWire2, wireInfo &wI_OutputWire){
    wI_OutputWire.value = wI_InputWire1->value | wI_InputWire2->value;
    wI_OutputWire.evaluated = true;
}

void AoC2015Day7::lShiftOperation(wireInfo *wI_InputWire1, wireInfo *wI_InputWire2, wireInfo &wI_OutputWire){
    wI_OutputWire.value = wI_InputWire1->value << wI_InputWire2->value;
    wI_OutputWire.evaluated = true;
}

void AoC2015Day7::rShiftOperation(wireInfo *wI_InputWire1, wireInfo *wI_InputWire2, wireInfo &wI_OutputWire){
    wI_OutputWire.value = wI_InputWire1->value >> wI_InputWire2->value;
    wI_OutputWire.evaluated = true;
}

void AoC2015Day7::checkForValue(wireInfo **pwI_WireInfo, const string& sKey, wireInfo &wI_WireInfo) {
    // Deal with the scenario of a value being directly assigned to a wire instead of another wire or the wires info
    if(mmssWireMap.count(sKey) == 0){
        wI_WireInfo.value = stoi(sKey);
        wI_WireInfo.evaluated = true;
        *pwI_WireInfo = &wI_WireInfo;
    } else{
        *pwI_WireInfo = &mmssWireMap.find(sKey)->second;
    }
}

void AoC2015Day7::changeWireInfo(const string& sKey, const wireInfo& wI_NewInfo) {
    mmssWireMap.erase(sKey);
    mmssWireMap.insert({sKey, wI_NewInfo});
}

multimap<string, wireInfo> AoC2015Day7::getCircuitMap() {
    return mmssWireMap;
}

AoC2015Day7::~AoC2015Day7() = default;