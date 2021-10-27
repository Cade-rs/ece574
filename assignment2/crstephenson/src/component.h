#ifndef COMPONENT_H
#define COMPONENT_H
#include <string>
#include "latency.h"
#include <iostream>
#include <vector>
using namespace std;
using std::vector;

class component {
public:
    component(int type, int datawidth, vector<string> in, vector<string> out);
    double findLatency(void);

    int type_;
    int dw_;
    vector<string> in_;
    vector<string> out_;
    double lat_;
};
#endif