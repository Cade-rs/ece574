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
    void sumPathLatencies(const std::vector<component> complist);
    //double recursivesearch(std::vector<component> complist);
    std::vector<component> examplecomps();

    double criticalpath_;

private:
    //std::vector<component> complist_;
};

#endif