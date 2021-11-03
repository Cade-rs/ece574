#include "component.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "latency.h"

using namespace std;


component::component(comp_type type, comp_size datawidth, vector<variable> in, vector<variable> out, bool isSigned, int compNum, int outputPos)
{
    type_ = type;
    dw_ = datawidth;
    isSigned_ = isSigned;
    compNum_ = compNum;
    outputPos_ = outputPos;

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
    compNum_ = in_comp.compNum_;
    outputPos_ = in_comp.outputPos_;

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
    }
    else
    {
        lat = 0;
    }
    
    return(lat);
}

std::string component::writeLine()
{
    return( "THANKS FOR BREAKING THE CODE BRANDON");
}

void component::printComponent(std::ofstream& fout)
{

    fout << std::endl;
    fout << "New Component" << std::endl;
    fout << "Type:         " << type2str(type_) << std::endl;
    fout << "Number:       " << compNum_ << std::endl;
    fout << "OutputPos:    " << outputPos_ << std::endl;
    fout << "Size:         " << size2str(dw_) << std::endl;
    fout << "Signed:       " << isSigned_ << std::endl;
    fout << "Latency:      " << lat_ << std::endl;
    fout << "Inputs:" << std::endl;
    for(int i=0; i<in_.size(); i++)
    {
        fout << "      " << in_[i].name_ << std::endl;
    }
    fout << "Outputs:" << std::endl;
    for(int i=0; i<out_.size(); i++)
    {
        fout << "      " << out_[i].name_ << std::endl;
    }
    fout << std::endl ;
}