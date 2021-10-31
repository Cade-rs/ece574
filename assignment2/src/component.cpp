#include "component.h"

#include <iostream>
#include <string>
#include <vector>

#include "latency.h"

using namespace std;


component::component(comp_type type, comp_size datawidth, vector<variable> in, vector<variable> out, bool isSigned)
{
    type_ = type;
    dw_ = datawidth;
    isSigned_ = isSigned;

    for (int i=0; i<in.size(); i++)
    {
        in_.push_back( variable(in[i]) ) ;
    }

    for (int i=0; i<out.size(); i++)
    {
        out_.push_back( variable(out[i]) );
    }

    lat_ = findLatency();
}

// Copy constructor
component::component(const component& in_comp)
{
    type_ = in_comp.type_;
    dw_ = in_comp.dw_;
    isSigned_ = in_comp.isSigned_;

    for (int i=0; i<in_comp.in_.size(); i++)
    {
        in_.push_back( variable(in_comp.in_[i]) ) ;
    }

    for (int i=0; i<in_comp.out_.size(); i++)
    {
        out_.push_back( variable(in_comp.out_[i]) );
    }

    lat_ = in_comp.lat_;
}

bool component::containsInput(std::string var)
{
    for( int i=0; i < in_.size(); i++ )
    {
        if (in_[i] == var)
        {
            return true;
        }
    }
    return false;
}

bool component::containsInput(variable& var)
{
    for( int i=0; i < in_.size(); i++ )
    {
        if (in_[i] == var)
        {
            return true;
        }
    }
    return false;
}

bool component::containsOutput(std::string var)
{
    for( int i=0; i < out_.size(); i++ )
    {
        if (out_[i] == var)
        {
            return true;
        }
    }
    return false;
}

bool component::containsOutput(variable& var)
{
    for( int i=0; i < out_.size(); i++ )
    {
        if (out_[i] == var)
        {
            return true;
        }
    }
    return false;
}

double component::findLatency(void)
{
    double lat = 0;
    if (type_ >=comp_type::REG)
    {
        lat = latlist[type_][dw_];
        std::cout << std::to_string(lat) << std::endl;   
    }
    else
    {
        lat = 0;
    }
    
    return(lat);
}

