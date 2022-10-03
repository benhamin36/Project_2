//
// Created by bigbe on 9/19/2022.
//

#include "LineCommentAutomaton.h"

void LineCommentAutomaton::S0(const std::string& input) {
    if ((input[index] == '#') & (input[index + 1] != '|')) {
        inputRead = 1;
        index = 1;
        S1(input);
    }
    else {
        Serr();
    }
}

void LineCommentAutomaton::S1(const std::string& input) {
    if (input[index] != '\n') {
        inputRead++;
        index++;
        S1(input);
    }
}