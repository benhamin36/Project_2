//
// Created by bigbe on 9/21/2022.
//

#include "StringAutomaton.h"

void StringAutomaton::S0(const std::string& input) {
    if (input[index] == '\'') {
        inputRead = 1;
        index = 1;
        S1(input);
    }
    else {
        Serr();
    }
}

void StringAutomaton::S1(const std::string& input) {
    if (index >= (int) input.size()) {
        Serr();
    } else if (input[index] != '\'') {
        if (input[index] == '\n') {

        }
        inputRead++;
        index++;
        S1(input);
    } else {
        inputRead++;
        index++;
        S2(input);
    }
}

void StringAutomaton::S2(const std::string& input) {
    if (index < (int) input.size()) { //We may not have more in the file. If we don't
                                //we can call this string accepted. If we do, we
                                //need to check if it's another ' before calling it
                                //done.
        if (input[index] == '\'') {
            inputRead++;
            index++;
            S1(input);
        }
    }
}