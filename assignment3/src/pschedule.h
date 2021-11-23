#ifndef PSCHEDULE_H
#define PSCHEDULE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "component.h"

class pschedule{
public:
    pschedule();
    void performScheduling(std::vector<component>& compVec);
    void asap();
    void alap();
    void recurse(int nodeidx);
    void buildFDSTable();
    void outputDebug();
    int findalaptf( resource restype, int childtf);
    
    std::vector<component> compVec_;
    int latconstrnt_;

    std::ifstream fin_;
    std::ofstream fout_;
};

#endif