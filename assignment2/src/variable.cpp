#include "variable.h"

#include "latency.h"

variable::variable(std::string name, int size)
{
    name_ = name;
    size_ = int2size(size);
    return;
}
variable::variable(std::string name, comp_size size)
{
    name_ = name;
    size_ = size;
    return;
}

bool variable::operator== (std::string param)
{
    return name_ == param;
}