#include "variable.h"

#include "latency.h"

variable::variable(std::string name, int size, bool isSigned, bool isReg)
{
    name_ = name;
    size_ = int2size(size);
    isSigned_ = isSigned;
    isReg_ = isReg;
}
variable::variable(std::string name, comp_size size, bool isSigned, bool isReg)
{
    name_ = name;
    size_ = size;
    isSigned_ = isSigned;
    isReg_ = isReg;
}

// Copy constructor
variable::variable(const variable& in_var)
{
    name_ = in_var.name_;
    size_ = in_var.size_;
    isSigned_ = in_var.isSigned_;
    isReg_ = in_var.isReg_;
}

bool variable::operator== (std::string param)
{
    return name_ == param;
}

bool variable::operator== (variable param)
{
    return name_ == param.name_;
}