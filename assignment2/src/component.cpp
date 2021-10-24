#include "component.h"

#include <iostream>
#include <string>
#include <vector>

#include "latency.h"

using namespace std;


component::component(comp_type type, comp_size datawidth, vector<variable> in, vector<variable> out)
{
    type_ = type;
    dw_ = datawidth;

    for (int i=0; i<in.size(); i++)
    {
        in_.push_back( variable(in[i]) ) ;
        std::cout << in_[i].name_ << ", ";
    }

    for (int i=0; i<out.size(); i++)
    {
        out_.push_back( variable(out[i]) );
        std::cout << out_[i].name_ << ", ";
    }

    lat_ = findLatency();
}

// Copy constructor
component::component(const component& in_comp)
{
    type_ = in_comp.type_;
    dw_ = in_comp.dw_;

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

double component::findLatency(void)
{
    if (type_ >=comp_type::REG)
    {
        lat_ = latlist[type_][dw_];
    }
    else
    {
        lat_ = 0;
    }
    
    return(0);
}

