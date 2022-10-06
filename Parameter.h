//
// Created by bigbe on 10/4/2022.
//

#ifndef PROJECT_1_PARAMETER_H
#define PROJECT_1_PARAMETER_H

#include <string>

class Parameter {
public:
    Parameter();
    Parameter(std::string stringOrId);

    std::string toString();
private:
    std::string stringOrId;
};


#endif //PROJECT_1_PARAMETER_H
