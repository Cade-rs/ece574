#ifndef LATENCYCALCULATOR_H
#define LATENCYCALCULATOR_H

#include <string>
#include <vector>

#include "component.h"
#include "latency.h"
#include "variable.h"

class latencycalculator {
public:
    latencycalculator();
    void sumPathLatencies(std::vector<component> complist);
    void recursivesearch(std::vector<component> complist, int compnum, int branch);
    std::vector<component> examplecomps1();
    std::vector<component> examplecomps4();

    double criticalpath_;

private:
    vector<double> delays_;
};

#endif