#include "variable.h"

#include "latency.h"

variable::variable(std::string name, int size, bool isSigned)
{
    name_ = name;
    size_ = int2size(size);
    isSigned_ = isSigned;
}
variable::variable(std::string name, comp_size size, bool isSigned)
{
    name_ = name;
    size_ = size;
    isSigned_ = isSigned;
}

// Copy constructor
variable::variable(const variable& in_var)
{
    name_ = in_var.name_;
    size_ = in_var.size_;
    isSigned_ = in_var.isSigned_;
}

bool variable::operator== (std::string param)
{
    return name_ == param;
}

bool variable::operator== (variable param)
{
    return name_ == param.name_;
}