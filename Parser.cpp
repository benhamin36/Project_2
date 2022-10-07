//
// Created by bigbe on 10/1/2022.
//

#include "Parser.h"
#include "Token.h"
#include "DatalogProgram.h"
#include "Parameter.h"
#include "Predicate.h"
#include "Rule.h"
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

Parser::~Parser() {
    /*for (Token* token : tokens) {
        delete token;
    }
    tokens.clear();*/
}

Token* Parser::currentToken() {
    return tokens[pointer];
}

Parser::Parser() {
/*    schemes = std::vector<std::string>();
    facts = std::vector<std::string>();
    rules = std::vector<Rule>();
    queries = std::vector<Predicate>();
    domain = std::vector<std::string>();
    program = DatalogProgram(schemes, facts, rules, queries, domain);*/
}

bool checkIfComment(Token* token) {
    if (token->getType() == TokenType::COMMENT) {
        //TODO: I think this works but double-check
        //delete token;
        return true;
    }
    return false;
}

DatalogProgram Parser::Run(std::vector<Token*> tokenVector) {
    //Set our new vector and put our pointer at the beginning.
    tokens = tokenVector;
    pointer = 0;

    //Take out all comments before we go. They're going to mess with the parser if we leave them in.
    //TODO: We need to delete them before erasing, fix this first thing next time we work on this!!!
    tokens.erase(std::remove_if(tokens.begin(), tokens.end(), checkIfComment));

    //Now get into the parsing.
    parseDatalogProgram();

    std::sort(domain.begin(), domain.end());
    return DatalogProgram(schemes, facts, rules, queries, domain);
}

void Parser::parseDatalogProgram() {
    match(TokenType::SCHEMES);
    match(TokenType::COLON);
    builderMode = 0;
    parseScheme();
    parseSchemeList();
    match(TokenType::FACTS);
    match(TokenType::COLON);
    builderMode = 1;
    parseFactList();
    match(TokenType::RULES);
    match(TokenType::COLON);
    builderMode = 2;
    parseRuleList();
    match(TokenType::QUERIES);
    match(TokenType::COLON);
    builderMode = 3;
    parseQuery();
    parseQueryList();
    match(TokenType::END_OF_FILE);
    //Outputs for testing
    //std::cout << rules.size();
    /*for (int i = 0; i < queries.size(); i++) {
        std::cout << queries[i].toString() << "\n";
    }*/
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
    schemeBuilderString = "";

    addInfo();
    match(TokenType::ID);

    addInfo();
    match(TokenType::LEFT_PAREN);

    addInfo();
    match(TokenType::ID);

    parseIdList();

    addInfo();
    match(TokenType::RIGHT_PAREN);

    schemes.push_back(schemeBuilderString);
}

void Parser::parseFact() {
    //We could double check that we have an ID before we go, but
    //if not we'll get the throw when we do the match function anyway
    factBuilderString = "";

    addInfo();
    match(TokenType::ID);

    addInfo();
    match(TokenType::LEFT_PAREN);

    addInfo();
    match(TokenType::STRING);

    parseStringList();

    addInfo();
    match(TokenType::RIGHT_PAREN);

    addInfo();
    match(TokenType::PERIOD);

    facts.push_back(factBuilderString);
}

void Parser::parseRule() {
    //We could double check that we have an ID before we go, but
    //if not we'll get the throw when we do the match function anyway
    ruleBuilder = Rule();
    rulePredicate = Predicate();

    parseHeadPredicate();
    ruleBuilder.setHeadPredicate(rulePredicate);
    match(TokenType::COLON_DASH);
    parsePredicate();
    parsePredicateList();
    match(TokenType::PERIOD);

    rules.push_back(ruleBuilder);
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

    rulePredicate.setId(tokens[pointer]->getValue()); //We'll get a throw if the match doesn't work, and it won't matter what the data structures look like, so I'm just going to put this here.
    match(TokenType::ID);
    match(TokenType::LEFT_PAREN);
    addInfo();
    match(TokenType::ID);
    parseIdList();
    match(TokenType::RIGHT_PAREN);
}

void Parser::parsePredicate() {
    //We could double check that we have an ID before we go, but
    //if not we'll get the throw when we do the match function anyway
    queryBuilder = Predicate();
    rulePredicate = Predicate();
    rulePredicate.setId(tokens[pointer]->getValue());
    queryBuilder.setId(tokens[pointer]->getValue());
    match(TokenType::ID);
    match(TokenType::LEFT_PAREN);
    addInfo();
    parseParameter();
    parseParameterList();
    match(TokenType::RIGHT_PAREN);

    if (builderMode == 2) {
        ruleBuilder.addPredicate(rulePredicate);
    } else if (builderMode == 3) {
        queries.push_back(queryBuilder);
    }
}

void Parser::parsePredicateList() {
    //If we're ever in a list of predicates, we're in rules.
    //Queries separate their predicates
    rulePredicate = Predicate();
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
        addInfo();
        parseParameter();
        parseParameterList();
    }
    //If we have something that follows a parameter, like parentheses,
    //just move on. We'll handle bad follow-ups in the match function.
}

void Parser::parseStringList() {
    if (tokens[pointer]->getType() == TokenType::COMMA) {
        addInfo();
        match(TokenType::COMMA);
        addInfo();
        match(TokenType::STRING);
        parseStringList();
    }
    //If we have something that follows a string, like parentheses,
    //just move on. We'll handle bad follow-ups in the match function.
}

void Parser::parseIdList() {
    if (tokens[pointer]->getType() == TokenType::COMMA) {
        if (builderMode <= 1) {
            addInfo();
        }
        match(TokenType::COMMA);
        addInfo();
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
        //If we have a string, we need to add it to the domain if it isn't already in there.
        if (tokens[pointer]->getType() == TokenType::STRING && builderMode == 1) {
            bool alreadyInDomain = false;
            for (int i = 0; i < (int) domain.size(); i++) {
                if (domain[i] == tokens[pointer]->getValue()) {
                    alreadyInDomain = true;
                }
            }
            if (!alreadyInDomain) {
                domain.push_back(tokens[pointer]->getValue());
            }
        }
        returnable += " " + tokens[pointer]->toString();
        pointer++;
    } else {
        throw tokens[pointer]->toString();
    }
}

void Parser::addInfo() {
    switch(builderMode) {
        case 0:
            schemeBuilderString += tokens[pointer]->getValue();
            break;
        case 1:
            factBuilderString += tokens[pointer]->getValue();
            break;
        case 2:
            rulePredicate.addParameter(Parameter(tokens[pointer]->getValue()));
            break;
        case 3:
            queryBuilder.addParameter(Parameter(tokens[pointer]->getValue()));
            break;
        default:
            break;
    }
}