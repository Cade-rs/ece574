#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "latency.h"
#include "variable.h"

using namespace std;
using std::vector;

class component {
public:
    component(comp_type type, comp_size datawidth, 
              vector<variable> in, vector<variable> out, 
              bool isSigned=false, int compNum=0, int outputPos=0);
    component(const component& in_comp);
    bool containsInput(std::string var);
    bool containsInput(variable& var);
    bool containsOutput(std::string var);
    bool containsOutput(variable& var);
    double findLatency(void);
    std::string writeLine();
    std::string comp2Str();
    std::string dw2Str();

    void printComponent(std::ofstream& fout);

    comp_type type_;
    comp_size dw_;
    bool isSigned_;
    vector<variable> in_;
    vector<variable> out_;
    double lat_;
    int compNum_;
    int outputPos_;
    std::string sctype_;
    std::string scdw_;
};
#endif