//
// Created by bigbe on 9/19/2022.
//

#ifndef PROJECT_1_LINECOMMENTAUTOMATON_H
#define PROJECT_1_LINECOMMENTAUTOMATON_H

#include "Automaton.h"

class LineCommentAutomaton : public Automaton{

private:

    void S1(const std::string& input);

public:
    LineCommentAutomaton() : Automaton(TokenType::COMMENT) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //PROJECT_1_LINECOMMENTAUTOMATON_H
