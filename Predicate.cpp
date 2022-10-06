//
// Created by bigbe on 10/4/2022.
//

#include "Predicate.h"

Predicate::Predicate() {}

Predicate::Predicate(std::string id, std::vector<Parameter> parameters) {
    this->id = id;
    this->parameters = parameters;
}

std::string Predicate::toString() {
    std::string returnable = "";
    returnable.append(id + "(");
    for (int i = 0; i < parameters.size(); i++) {
        returnable.append(parameters[i].toString());
        if (i < parameters.size() - 1) {
            returnable.append(",");
        } else {
            returnable.append(")");
        }
    }
    return returnable;
}

void Predicate::setId(std::string id) {
    this->id = id;
}

void Predicate::addParameter(Parameter parameter) {
    parameters.push_back(parameter);
}