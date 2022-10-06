//
// Created by bigbe on 10/4/2022.
//

#include "Parameter.h"

Parameter::Parameter() {}

Parameter::Parameter(std::string stringOrId) {
    this->stringOrId = stringOrId;
}

std::string Parameter::toString() {
    return stringOrId;
}