#ifndef PSCHEDULE_H
#define PSCHEDULE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "component.h"

class pschedule{
public:
    pschedule(std::vector<component>& compVec);
    void asap(std::vector<component> cV);
    void alap(std::vector<component> cV);
    void recurse(std::vector<component> cV, int nodeidx);
    int findalaptf( resource restype, int childtf);

    int latconstrnt_;
};

#endif