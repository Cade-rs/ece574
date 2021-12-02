#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "common.h"
#include "variable.h"

using namespace std;
using std::vector;

class component {
public:
    component(comp_type type, comp_size datawidth, 
              vector<variable> in, vector<variable> out, 
              bool isSigned=false, int compNum=0, int outputPos=0, int withinIf=-1, std::string line = "");
    component(const component& in_comp);
    bool containsInput(std::string var);
    bool containsInput(variable& var);
    bool containsOutput(std::string var);
    bool containsOutput(variable& var);
    double findLatency(void);
    std::string writeLine();
    std::string comp2Str();
    std::string dw2Str();
    std::string trunc();
    std::string cPadd();
    resource whichResource();
    void printComponent(std::ofstream& fout);
    std::string replaceString( std::string& s, const std::string& toReplace, const std::string& replaceWith);

    std::string line_;
    comp_type type_;
    comp_size dw_;
    bool isSigned_;
    double lat_;
    int compNum_;
    int outputPos_;
    int withinIf_;
    std::string sctype_;
    std::string scdw_;
    int asapFrame_;
    int alapFrame_;
    int fdsFrame_;
    resource restype_;
    vector<variable> in_;
    vector<variable> out_;
    vector<int> parent_;
    vector<int> child_;
};
#endif