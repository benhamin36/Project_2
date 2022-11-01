//
// Created by bigbe on 10/4/2022.
//

#include "DatalogProgram.h"
#include <string>
#include <vector>
#include "Rule.h"
#include "Predicate.h"

DatalogProgram::DatalogProgram() {}

DatalogProgram::DatalogProgram(std::vector<Predicate> schemes, std::vector<Predicate> facts, std::vector<Rule> rules,std::vector<Predicate> queries, std::vector<std::string> domain) {
    this->schemes = schemes;
    this->facts = facts;
    this->rules = rules;
    this->queries = queries;
    this->domain = domain;
}

std::string DatalogProgram::toString() {
    std::string returnable = "";
    returnable.append("Success!\n");
    returnable.append("Schemes(");
    returnable.append(std::to_string(schemes.size()));
    returnable.append("):\n");
    for (Predicate scheme : schemes) {
        returnable.append( "  " + scheme.toString() + "\n");
    }
    returnable.append("Facts(");
    returnable.append(std::to_string(facts.size()));
    returnable.append("):\n");
    for (Predicate fact : facts) {
        returnable.append( "  " + fact.toString() + ".\n");
    }
    returnable.append("Rules(");
    returnable.append(std::to_string(rules.size()));
    returnable.append("):\n");
    for (Rule rule : rules) {
        returnable.append( "  " + rule.toString() + "\n");
    }
    returnable.append("Queries(");
    returnable.append(std::to_string(queries.size()));
    returnable.append("):\n");
    for (Predicate query : queries) {
        returnable.append( "  " + query.toString() + "?\n");
    }
    returnable.append("Domain(");
    returnable.append(std::to_string(domain.size()));
    returnable.append("):\n");
    for (std::string string : domain) {
        returnable.append( "  " + string + "\n");
    }
    return returnable;
}