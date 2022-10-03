//
// Created by bigbe on 10/1/2022.
//

#include "Parser.h"
#include "Token.h"
#include <iostream>
#include <vector>
#include <algorithm>

Parser::~Parser() {
    for (Token* token : tokens) {
        delete token;
    }
    tokens.clear();
}

Parser::Parser() {
    //Not really sure what to do here
}

bool checkIfComment(Token* token) {
    if (token->getType() == TokenType::COMMENT) {
        return true;
    }
    return false;
}

std::string Parser::Run(std::vector<Token*> tokenVector) {
    //Set our new vector and put our pointer at the beginning.
    tokens = tokenVector;
    pointer = 0;

    //Take out all comments before we go. They're going to mess with the parser if we leave them in.
    tokens.erase(std::remove_if(tokens.begin(), tokens.end(), checkIfComment));

    //Now get into the parsing.
    parseDatalogProgram();

    return returnable;
}

void Parser::parseDatalogProgram() {
    match(TokenType::SCHEMES);
    match(TokenType::COLON);
    parseScheme();
    parseSchemeList();
    match(TokenType::FACTS);
    match(TokenType::COLON);
    parseFactList();
    match(TokenType::RULES);
    match(TokenType::COLON);
    parseRuleList();
    match(TokenType::QUERIES);
    match(TokenType::COLON);
    parseQuery();
    parseQueryList();
    match(TokenType::END_OF_FILE);
}

void Parser::parseSchemeList() {
    if (tokens[pointer]->getType() == TokenType::ID) {
        parseScheme();
        parseSchemeList();
    }
    //Else if it's facts we just move on,
    //but we can handle throwing in the match(Facts) function
    //so we don't have to do anything else here.
}

void Parser::parseFactList() {
    if (tokens[pointer]->getType() == TokenType::ID) {
        parseFact();
        parseFactList();
    }
    //Else if it's rules we just move on,
    //but we can handle throwing in the match(Rules) function
    //so we don't have to do anything else here.
}

void Parser::parseRuleList() {
    if (tokens[pointer]->getType() == TokenType::ID) {
        parseRule();
        parseRuleList();
    }
    //Else if it's queries we just move on,
    //but we can handle throwing in the match(Queries) function
    //so we don't have to do anything else here.
}

void Parser::parseQueryList() {
    if (tokens[pointer]->getType() == TokenType::ID) {
        parseQuery();
        parseQueryList();
    }
    //Else if it's EOF we just move on,
    //but we can handle throwing in the match(EOF) function
    //so we don't have to do anything else here.
}

void Parser::parseScheme() {
    //We could double check that we have an ID before we go, but
    //if not we'll get the throw when we do the match function anyway
    match(TokenType::ID);
    match(TokenType::LEFT_PAREN);
    match(TokenType::ID);
    parseIdList();
    match(TokenType::RIGHT_PAREN);
}

void Parser::parseFact() {
    //We could double check that we have an ID before we go, but
    //if not we'll get the throw when we do the match function anyway
    match(TokenType::ID);
    match(TokenType::LEFT_PAREN);
    match(TokenType::STRING);
    parseStringList();
    match(TokenType::RIGHT_PAREN);
    match(TokenType::PERIOD);
}

void Parser::parseRule() {
    //We could double check that we have an ID before we go, but
    //if not we'll get the throw when we do the match function anyway
    parseHeadPredicate();
    match(TokenType::COLON_DASH);
    parsePredicate();
    parsePredicateList();
    match(TokenType::PERIOD);
}

void Parser::parseQuery() {
    //We could double check that we have an ID before we go, but
    //if not we'll get the throw when we do the match function anyway
    parsePredicate();
    match(TokenType::Q_MARK);
}

void Parser::parseHeadPredicate() {
    //We could double check that we have an ID before we go, but
    //if not we'll get the throw when we do the match function anyway
    match(TokenType::ID);
    match(TokenType::LEFT_PAREN);
    match(TokenType::ID);
    parseIdList();
    match(TokenType::RIGHT_PAREN);
}

void Parser::parsePredicate() {
    //We could double check that we have an ID before we go, but
    //if not we'll get the throw when we do the match function anyway
    match(TokenType::ID);
    match(TokenType::LEFT_PAREN);
    parseParameter();
    parseParameterList();
    match(TokenType::RIGHT_PAREN);
}

void Parser::parsePredicateList() {
    if (tokens[pointer]->getType() == TokenType::COMMA) {
        match(TokenType::COMMA);
        parsePredicate();
        parsePredicateList();
    }
    //If we have something that follows a predicate, like a period or a question mark
    //just move on. We'll handle bad follow-ups in the match function.
}

void Parser::parseParameterList() {
    if (tokens[pointer]->getType() == TokenType::COMMA) {
        match(TokenType::COMMA);
        parseParameter();
        parseParameterList();
    }
    //If we have something that follows a parameter, like parentheses,
    //just move on. We'll handle bad follow-ups in the match function.
}

void Parser::parseStringList() {
    if (tokens[pointer]->getType() == TokenType::COMMA) {
        match(TokenType::COMMA);
        match(TokenType::STRING);
        parseStringList();
    }
    //If we have something that follows a string, like parentheses,
    //just move on. We'll handle bad follow-ups in the match function.
}

void Parser::parseIdList() {
    if (tokens[pointer]->getType() == TokenType::COMMA) {
        match(TokenType::COMMA);
        match(TokenType::ID);
        parseIdList();
    }
    //If we have something that follows an ID, like parentheses,
    //just move on. We'll handle bad follow-ups in the match function.
}

void Parser::parseParameter() {
    if (tokens[pointer]->getType() == TokenType::STRING) {
        match(TokenType::STRING);
    } else if (tokens[pointer]->getType() == TokenType::ID) {
        match(TokenType::ID);
    }
    //We'll handle throwing in the match functions.
}


void Parser::match(TokenType type) {
    if (tokens[pointer]->getType() == type) {
        //Once this is working, add this to a data structure.
        returnable += " " + tokens[pointer]->toString();
        pointer++;
    } else {
        std::cout << "expected: " + Token::typeToString(type) + ", actual: " + tokens[pointer]->toString();
        throw "expected: " + Token::typeToString(type) + ", actual: " + tokens[pointer]->toString();
    }
}


/*public struct datalogProgram{
    int numSchemes;
    std::vector<Token*> schemeTokens;
    int numFacts;
    std::vector<Token*> factTokens;
    int
};*/