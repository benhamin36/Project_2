//
// Created by bigbe on 9/19/2022.
//

#include "IdAutomaton.h"

void IdAutomaton::S0(const std::string& input) {
    soFar = "";
    if (isalpha(input[index])) {
        soFar += input[index];
        inputRead = 1;
        index = 1;
        S1(input);
    }
    else {
        Serr();
    }
}

void IdAutomaton::S1(const std::string& input) {
    if (std::isalpha(input[index]) | std::isdigit(input[index])) {
        inputRead++;
        index++;
        S1(input);
    }
}