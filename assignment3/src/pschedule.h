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
    bool performScheduling(std::vector<component>& compVec);
    void buildFamily();
    void asap(int TF);
    void alap();
    void recurse_firstNodes(int nodeidx);
    void recurse(int nodeidx);
    void FDS();
    void calcSelfForce(int frame, int n);
    void calcPredecessorForces(int frame, int n);
    void calcSuccessorForces(int frame, int n);
    void buildFDSTable(std::vector<double>& FDSTable, std::vector<double>& probVec,  std::vector<int> nodeVec);
    void outputDebug(int TF);
    void debugPrints();
    void what_if_branch();
    int calculateForces(int TF, int n);
    int findalaptf( resource restype, int childtf);
    int findasaptf( resource restype, int parenttf);
    
    std::vector<component> compVec_;
    
    bool error_;
    int latconstrnt_;

    std::vector<double> forces_;

    std::vector<double> addTable_;
    std::vector<double> multTable_;
    std::vector<double> logicTable_;
    std::vector<double> divTable_;

    std::vector<double> addProbs_;
    std::vector<double> multProbs_;
    std::vector<double> logicProbs_;
    std::vector<double> divProbs_;

    std::vector<int> addVec_;
    std::vector<int> multVec_;
    std::vector<int> logicVec_;
    std::vector<int> divVec_;

    std::vector<int> chosenOnes_;

    std::ifstream fin_;
    std::ofstream fout_;

};

#endif