//
// Created by bigbe on 10/1/2022.
//

#ifndef PROJECT_2_PARSER_H
#define PROJECT_2_PARSER_H


#include "Token.h"
#include <vector>

class Parser {
private:
    std::vector<Token*> tokens;
    int pointer;

    //We won't use this once we have the data
    //structures going, but we'll use this
    //string to return what we have in the
    //meantime
    std::string returnable;

    void parseDatalogProgram();

    void parseSchemeList();
    void parseFactList();
    void parseRuleList();
    void parseQueryList();

    void parseScheme();
    void parseFact();
    void parseRule();
    void parseQuery();

    void parseHeadPredicate();
    void parsePredicate();

    void parsePredicateList();
    void parseParameterList();
    void parseStringList();
    void parseIdList();
    void parseParameter();

    void match(TokenType type);

public:
    Parser();
    ~Parser();

    // TODO: This is actually going to return a data structure with
    //the contents of a datalog program. We're going to start by
    //having it return a string that represents the program.
    std::string Run(std::vector<Token*> tokenVector);
};

#endif //PROJECT_2_PARSER_H
