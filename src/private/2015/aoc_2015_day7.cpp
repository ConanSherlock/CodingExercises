//
// Created by conan on 11/12/2021.
//

#include "aoc_2015_day7.hpp"

AoC2015Day7::AoC2015Day7() = default;

void AoC2015Day7::reset() {
    svecCircuitComponent.clear();
    mmssWireMap.clear();

}

void AoC2015Day7::buildCircuit(string &inputString) {
    svecCircuitComponent.push_back(inputString);
}

void AoC2015Day7::evaluateCircuit() {
    for(auto & component : svecCircuitComponent) {
        createComponentEntry(component);
    }

    for (auto & entry : mmssWireMap) {
        cout << "Key: " << entry.first << "\n";
        evaluateWire(entry.second);
    }

    for (auto & entry : mmssWireMap) {
        cout << "Key: " << entry.first << " Value: " << entry.second.value << "\n";
    }
}

void AoC2015Day7::createComponentEntry(string &component) {
    size_t pos;
    string deliminator = DELIMINATOR_WIRE_EQUATION;
    wireInfo mapValue;

    if (( pos = component.find(deliminator)) != std::string::npos)
    {
        mapValue.equation = component.substr(0, pos);
        mapValue.evaluated = false;
        mapValue.value = 0;

        component.erase(0, pos + deliminator.length());

        mmssWireMap.insert({component, mapValue});
    }
}


void AoC2015Day7::evaluateWire(wireInfo &inputWireInfo) {
    size_t pos;
    string deliminator = DELIMINATOR_WIRE_EXPRESSION;
    wireInfo mapValue;
    string expressionPart1;
    string expressionPart2;
    string expressionPart3;
    wireInfo *pTempWire1Info;
    wireInfo *pTempWire2Info;

    if ((pos = inputWireInfo.equation.find(deliminator)) != std::string::npos)
    {
        expressionPart1 = inputWireInfo.equation.substr(0, pos);
//        cout << "expressionPart1: " << expressionPart1 << "\n";
        inputWireInfo.equation.erase(0, pos + deliminator.length());

        if(expressionPart1 == OPERATOR_NOT){
//            cout << "expressionPart2" << expressionPart2 << "\n";
            if(mmssWireMap.count(inputWireInfo.equation) == 0){
                wireInfo TempWire1Info;
                TempWire1Info.value = stoi(inputWireInfo.equation);
                TempWire1Info.evaluated = true;
                pTempWire1Info = &TempWire1Info;
            } else{
                pTempWire1Info = &mmssWireMap.find(inputWireInfo.equation)->second;
            }

            if (!pTempWire1Info->evaluated){
                evaluateWire(*pTempWire1Info);
            }
            NotOperation(pTempWire1Info, inputWireInfo);
        } else{
            if (( pos = inputWireInfo.equation.find(deliminator)) != std::string::npos)
            {
                expressionPart2 = inputWireInfo.equation.substr(0, pos);
                inputWireInfo.equation.erase(0, pos + deliminator.length());
            }

            expressionPart3 = inputWireInfo.equation;

//            cout << "expressionPart2: " << expressionPart2 << "\n";
//            cout << "expressionPart3: " << expressionPart3 << "\n";

            if(mmssWireMap.count(expressionPart1) == 0){
                wireInfo TempWire1Info;
                TempWire1Info.value = stoi(expressionPart1);
                TempWire1Info.evaluated = true;
                pTempWire1Info = &TempWire1Info;
            } else{
                pTempWire1Info = &mmssWireMap.find(expressionPart1)->second;
            }

            if(mmssWireMap.count(expressionPart3) == 0){
                wireInfo TempWire2Info;
                TempWire2Info.value = stoi(expressionPart3);
                TempWire2Info.evaluated = true;
                pTempWire2Info = &TempWire2Info;
            } else{
                pTempWire2Info = &mmssWireMap.find(expressionPart3)->second;
            }

            if (!pTempWire1Info->evaluated){
                evaluateWire(*pTempWire1Info);
            }
            if (!pTempWire2Info->evaluated){
                evaluateWire(*pTempWire2Info);
            }

            if(expressionPart2 == OPERATOR_AND){
                AndOperation(pTempWire1Info, pTempWire2Info, inputWireInfo);
            } else if(expressionPart2 == OPERATOR_OR){
                OrOperation(pTempWire1Info, pTempWire2Info, inputWireInfo);
            } else if(expressionPart2 == OPERATOR_LSHIFT){
                LShiftOperation(pTempWire1Info, pTempWire2Info, inputWireInfo);
            } else if(expressionPart2 == OPERATOR_RSHIFT){
                RShiftOperation(pTempWire1Info, pTempWire2Info, inputWireInfo);
            }
        }
    } else{
        if(mmssWireMap.count(inputWireInfo.equation) == 0){
            wireInfo TempWire1Info;
            TempWire1Info.value = stoi(inputWireInfo.equation);
            TempWire1Info.evaluated = true;
            pTempWire1Info = &TempWire1Info;
        } else{
            pTempWire1Info = &mmssWireMap.find(inputWireInfo.equation)->second;
        }

        if (!pTempWire1Info->evaluated){
            evaluateWire(*pTempWire1Info);
        }

        inputWireInfo.value = pTempWire1Info->value;
        inputWireInfo.evaluated = true;
    }
}

void AoC2015Day7::NotOperation(wireInfo *inputWire, wireInfo &outputWire){
    if (inputWire->evaluated){
        outputWire.value = ~inputWire->value;
        outputWire.evaluated = true;
    } else{
        evaluateWire(*inputWire);
        outputWire.value = ~inputWire->value;
        outputWire.evaluated = true;
    }
}

void AoC2015Day7::AndOperation(wireInfo *inputWire1, wireInfo *inputWire2, wireInfo &outputWire){
    outputWire.value = inputWire1->value & inputWire2->value;
    outputWire.evaluated = true;
}

void AoC2015Day7::OrOperation(wireInfo *inputWire1, wireInfo *inputWire2, wireInfo &outputWire){
    outputWire.value = inputWire1->value | inputWire2->value;
    outputWire.evaluated = true;
}

void AoC2015Day7::LShiftOperation(wireInfo *inputWire1, wireInfo *inputWire2, wireInfo &outputWire){
    outputWire.value = inputWire1->value << inputWire2->value;
    outputWire.evaluated = true;
}

void AoC2015Day7::RShiftOperation(wireInfo *inputWire1, wireInfo *inputWire2, wireInfo &outputWire){
    outputWire.value = inputWire1->value >> inputWire2->value;
    outputWire.evaluated = true;
}

AoC2015Day7::~AoC2015Day7() = default;