//
// Created by bigbe on 9/19/2022.
//

#include "QMarkAutomaton.h"

void QMarkAutomaton::S0(const std::string& input) {
    if (input[index] == '?') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}