//
// Created by bigbe on 9/21/2022.
//

#include "BadStringAutomaton.h"

void BadStringAutomaton::S0(const std::string& input) {
    //This Automaton checks for unfinished block comments and strings.
    if (input[index] == '#') {
        inputRead = 1;
        index = 1;
        SHash1(input);
    }
    else if (input[index] == '\'') {
        inputRead = 1;
        index = 1;
        SString1(input);
    } else {
        Serr();
    }
}

void BadStringAutomaton::SHash1(const std::string& input) {
    //If we don't have #|, it's a line comment, not a block comment. We
    //don't need to check line comments since they automatically end with
    //a newline. Serr those
    if (input[index] == '|') {
        inputRead++;
        index++;
        SHash2(input);
    } else {
        Serr();
    }
}

void BadStringAutomaton::SHash2(const std::string& input) {
    //If we're here, we started a block comment. If we reach our
    //input's size, we have a bad hash, and therefore we accept
    //that strung. If we hit a |, move to state Hash3
    if (index < (int) input.size()) {
        if (input[index] != '|') {
            inputRead++;
            index++;
            SHash2(input);
        } else {
            inputRead++;
            index++;
            SHash3(input);
        }
    }
}

void BadStringAutomaton::SHash3(const std::string& input) {
    //If we're at the end of the file, accept the string. It is a bad block comment.
    //If we hit a #, it's a good block comment, and we Serr.
    //If there's more but not #, the block comment isn't over.
    if (index < (int) input.size()) {
        if (input[index] == '#') {
            Serr();
        } else {
            inputRead++;
            index++;
            SHash2(input);
        }
    }
}

void BadStringAutomaton::SString1(const std::string& input) {
    //If we're at the end of the file, we have a bad string
    //if we have a ', we need to check if it's an escape or the end of the string
    //if we don't have a ', keep going.
    if (index < (int) input.size()) {
        if (input[index] != '\'') {
            inputRead++;
            index++;
            SString1(input);
        } else {
            inputRead++;
            index++;
            SString2(input);
        }
    }
}

void BadStringAutomaton::SString2(const std::string& input) {
    if (index >= (int) input.size()) { //If it's the end of the file here, we ended with a good string
        Serr();                  //which means we do not accept this as a bad string
    } else if (input[index] == '\'') {  //if it's another ', it was just an escape character
        inputRead++;                    //and not the end of the string
        index++;                        //so we keep going in state String1
        SString1(input);
    }
}