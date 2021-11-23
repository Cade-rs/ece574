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
    void recurse_firstNodes(int nodeidx);
    void recurse(int nodeidx);
    void FDS();
    void buildFDSTable(std::vector<double>& FDSTable, std::vector<int> nodeVec);
    void outputDebug();
    int findalaptf( resource restype, int childtf);
    int findasaptf( resource restype, int tf);
    
    std::vector<component> compVec_;
    int latconstrnt_;

    std::vector<double> addTable_;
    std::vector<double> multTable_;
    std::vector<double> logicTable_;
    std::vector<double> divTable_;

    std::ifstream fin_;
    std::ofstream fout_;
};

#endif