//
// Created by bigbe on 9/19/2022.
//

#ifndef PROJECT_1_PERIODAUTOMATON_H
#define PROJECT_1_PERIODAUTOMATON_H

#include "Automaton.h"

class PeriodAutomaton : public Automaton
{
public:
    PeriodAutomaton() : Automaton(TokenType::PERIOD) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif //PROJECT_1_PERIODAUTOMATON_H
