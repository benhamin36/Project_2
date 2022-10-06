//
// Created by bigbe on 10/4/2022.
//

#ifndef PROJECT_1_PREDICATE_H
#define PROJECT_1_PREDICATE_H

#include <string>
#include <vector>
#include "Parameter.h"

class Predicate {
public:
    Predicate();
    Predicate(std::string id, std::vector<Parameter> parameters);

    std::string toString();

    void setId(std::string id);
    void addParameter(Parameter parameter);
private:
    std::string id;

    std::vector<Parameter> parameters;
};


#endif //PROJECT_1_PREDICATE_H
