//
// Created by bigbe on 10/4/2022.
//

#include "Rule.h"
#include "Predicate.h"

Rule::Rule() {}

Rule::Rule(Predicate headPredicate, std::vector<Predicate> predicates) {
    this->headPredicate = headPredicate;
    this->predicates = predicates;
}

std::string Rule::toString() {
    std::string returnable = "";
    returnable.append(headPredicate.toString() + " :- ");
    for (int i = 0; i < predicates.size(); i++) {
        returnable.append(predicates[i].toString());
        if (i < predicates.size() - 1) {
            returnable.append(",");
        } else {
            returnable.append(".");
        }
    }
    return returnable;
}

void Rule::setHeadPredicate(Predicate predicate) {
    headPredicate = predicate;
}

void Rule::addPredicate(Predicate predicate) {
    predicates.push_back(predicate);
}