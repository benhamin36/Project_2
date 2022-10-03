//
// Created by bigbe on 9/19/2022.
//

#ifndef PROJECT_1_RULESAUTOMATA_H
#define PROJECT_1_RULESAUTOMATA_H

#include "Automaton.h"

class RulesAutomaton : public Automaton{

private:
    void S1(const std::string& input);
    void S2(const std::string& input);
    void S3(const std::string& input);
    void S4(const std::string& input);

public:
    RulesAutomaton() : Automaton(TokenType::RULES) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //PROJECT_1_RULESAUTOMATA_H
