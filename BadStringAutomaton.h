//
// Created by bigbe on 9/21/2022.
//

#ifndef PROJECT_1_BADSTRINGAUTOMATON_H
#define PROJECT_1_BADSTRINGAUTOMATON_H

#include "Automaton.h"

class BadStringAutomaton : public Automaton{

private:

    void SHash1(const std::string& input);
    void SHash2(const std::string& input);
    void SHash3(const std::string& input);
    void SString1(const std::string& input);
    void SString2(const std::string& input);

public:
    BadStringAutomaton() : Automaton(TokenType::UNDEFINED) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //PROJECT_1_BADSTRINGAUTOMATON_H
