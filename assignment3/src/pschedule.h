#ifndef PSCHEDULE_H
#define PSCHEDULE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "component.h"

class pschedule{
public:
    pschedule(int latencyConstraint);
    void performScheduling(std::vector<component>& compVec);
    void asap();
    void alap();
    void recurse(int nodeidx);
    void FDS();
    void buildFDSTable(std::vector<double>& FDSTable, std::vector<double>& probVec,  std::vector<int> nodeVec);
    void outputDebug();
    int findalaptf( resource restype, int childtf);
    
    std::vector<component> compVec_;
    int latconstrnt_;

    std::vector<double> addTable_;
    std::vector<double> multTable_;
    std::vector<double> logicTable_;
    std::vector<double> divTable_;

    std::vector<double> addProbs_;
    std::vector<double> multProbs_;
    std::vector<double> logicProbs_;
    std::vector<double> divProbs_;

};

#endif