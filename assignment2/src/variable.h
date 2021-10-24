#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>

#include "latency.h"


class variable {
public:
    variable(std::string name, int size);
    variable(std::string name, comp_size size);
    variable(const variable& in_var);
    bool operator== (std::string param);

    std::string name_;
    comp_size size_;
};


#endif