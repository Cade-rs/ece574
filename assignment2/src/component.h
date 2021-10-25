#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>
#include <string>
#include <vector>

#include "latency.h"
#include "variable.h"

using namespace std;
using std::vector;

class component {
public:
    component(comp_type type, comp_size datawidth, vector<variable> in, vector<variable> out, bool isSigned=false);
    component(const component& in_comp);
    bool containsInput(std::string var);
    bool containsInput(variable& var);
    bool containsOutput(std::string var);
    bool containsOutput(variable& var);
    double findLatency(void);

    comp_type type_;
    comp_size dw_;
    bool isSigned_;
    vector<variable> in_;
    vector<variable> out_;
    double lat_;
};
#endif