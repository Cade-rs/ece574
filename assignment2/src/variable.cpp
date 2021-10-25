#include "variable.h"

#include "latency.h"

variable::variable(std::string name, int size)
{
    name_ = name;
    size_ = int2size(size);
}
variable::variable(std::string name, comp_size size)
{
    name_ = name;
    size_ = size;
}

// Copy constructor
variable::variable(const variable& in_var)
{
    name_ = in_var.name_;
    size_ = in_var.size_;
}

bool variable::operator== (std::string param)
{
    return name_ == param;
}

bool variable::operator== (variable param)
{
    return name_ == param.name_;
}