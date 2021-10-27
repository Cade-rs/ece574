#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>

#include "latency.h"


class variable {
public:
    variable(std::string name, int size, bool isSigned=false);
    variable(std::string name, comp_size size, bool isSigned=false);
    variable(const variable& in_var);
    bool operator== (std::string param);
    bool operator== (variable param);

    std::string name_;
    comp_size size_;
    bool isSigned_;
};


#endif