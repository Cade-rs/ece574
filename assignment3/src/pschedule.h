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
    void FDS();
    void buildFDSTable(double** FDSTable, std::vector<int> nodeVec);
    void outputDebug();
    int findalaptf( resource restype, int childtf);
    
    std::vector<component> compVec_;
    int latconstrnt_;

    double* addTable_;
    double* multTable_;
    double* logicTable_;
    double* divTable_;

    std::ifstream fin_;
    std::ofstream fout_;
};

#endif