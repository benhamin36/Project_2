//
// Created by bigbe on 9/19/2022.
//

#include "RulesAutomata.h"

void RulesAutomaton::S0(const std::string& input) {
    if (input[index] == 'R') {
        inputRead = 1;
        index = 1;
        S1(input);
    }
    else {
        Serr();
    }
}

void RulesAutomaton::S1(const std::string& input) {
    if (input[index] == 'u') {
        inputRead++;
        index++;
        S2(input);
    }
    else {
        Serr();
    }
}

void RulesAutomaton::S2(const std::string& input) {
    if (input[index] == 'l') {
        inputRead++;
        index++;
        S3(input);
    }
    else {
        Serr();
    }
}

void RulesAutomaton::S3(const std::string& input) {
    if (input[index] == 'e') {
        inputRead++;
        index++;
        S4(input);
    }
    else {
        Serr();
    }
}

void RulesAutomaton::S4(const std::string& input) {
    if (input[index] == 's') {
        inputRead++;
    }
    else {
        Serr();
    }
}