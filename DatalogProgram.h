//
// Created by bigbe on 10/4/2022.
//

#ifndef PROJECT_1_DATALOGPROGRAM_H
#define PROJECT_1_DATALOGPROGRAM_H

#include <string>
#include <vector>
#include "Rule.h"
#include "Predicate.h"

class DatalogProgram {
public:
    DatalogProgram();
    DatalogProgram(std::vector<Predicate> schemes, std::vector<Predicate> facts, std::vector<Rule> rules, std::vector<Predicate> queries, std::vector<std::string> domain);

    std::string toString();
private:
    std::vector<Predicate> schemes;

    std::vector<Predicate> facts;

    std::vector<Rule> rules;

    std::vector<Predicate> queries;

    std::vector<std::string> domain;
};


#endif //PROJECT_1_DATALOGPROGRAM_H
