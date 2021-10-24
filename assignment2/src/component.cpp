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
        in_.push_back( variable(in[i].name_, in[i].size_) ) ;
        std::cout << in_[i].name_ << ", ";
    }

    for (int i=0; i<out.size(); i++)
    {
        out_.push_back( out[i] );
        std::cout << out_[i].name_ << ", ";
    }

    lat_ = findLatency();
}

double component::findLatency(void)
{
    if (dw_ >=0)
    {
        lat_ = latlist[type_][dw_];
    }
    else
    {
        lat_ = 0;
    }
    
    return(0);
}

