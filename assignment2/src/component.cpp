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
    //Call the switch to member variables
    sctype_ = comp2Str();
    scdw_ = dw2Str();

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

std::string component::comp2Str(){
    if(isSigned_==0){
        switch(type_){
            case 0: return "    reg "; 
            case 1: return "    wire ";
            case 2: return "    input ";
            case 3: return "    output ";
            case 4: return "    REG ";
            case 5: return "    ADD ";
            case 6: return "    SUB ";
            case 7: return "    MUL ";
            case 8: return "    COMP ";
            case 9: return "    MUX ";
            case 10: return "   SHR ";
            case 11: return "   SHL ";
            case 12: return "   DIV ";
            case 13: return "   MOD ";
            case 14: return "   INC ";
            case 15: return "   DEC ";
        }
    }
    else {
        switch(type_){
            case 0: return "    reg "; 
            case 1: return "    wire ";
            case 2: return "    input ";
            case 3: return "    output ";
            case 4: return "    REG ";
            case 5: return "    SADD ";
            case 6: return "    SSUB ";
            case 7: return "    SMUL ";
            case 8: return "    SCOMP ";
            case 9: return "    SMUX ";
            case 10: return "   SSHR ";
            case 11: return "   SSHL ";
            case 12: return "   SDIV ";
            case 13: return "   SMOD ";
            case 14: return "   SINC ";
            case 15: return "   SDEC ";
        }
    }
}

std::string component::dw2Str(){
    if (type_==0 | type_== 1 | type_==2 | type_==3){
        switch(dw_){
            case 0: return;
            case 1: return "[1:0]";
            case 2: return "[7:0]";
            case 3: return "[15:0]";
            case 4: return "[63:0]";
        }
    }   
    else{
        switch(dw_){
            case 0: return "#(.DATAWIDTH(0))";
            case 1: return "#(.DATAWIDTH(8))";
            case 2: return "#(.DATAWIDTH(16))";
            case 3: return "#(.DATAWIDTH(64))";
        }
    }
}

std::string component::writeLine(const component& in_comp){
    std::string out = in_comp.comp2Str();
    out.append();

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