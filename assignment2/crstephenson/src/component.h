#ifndef COMPONENT_H
#define COMPONENT_H
#include <string>
#include "latency.h"

class component {
public:
    component(COMPONENT type, SIZE datawidth, std::string in, std::string out);
    double findLatency(void);

    COMPONENT type_;
    SIZE dw_;
    std::string in_;
    std::string out_;
    double lat_;
};
#endif