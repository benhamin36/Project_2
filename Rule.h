//
// Created by bigbe on 10/4/2022.
//

#ifndef PROJECT_1_RULE_H
#define PROJECT_1_RULE_H

#include <string>
#include <vector>
#include "Predicate.h"

class Rule {
public:
    Rule();
    Rule(Predicate headPredicate, std::vector<Predicate> predicates);

    std::string toString();

    void setHeadPredicate(Predicate predicate);
    void addPredicate(Predicate predicate);
private:
    Predicate headPredicate;
    std::vector<Predicate> predicates;
};


#endif //PROJECT_1_RULE_H
