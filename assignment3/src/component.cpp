#include "component.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "common.h"

using namespace std;


component::component(comp_type type, comp_size datawidth, vector<variable> in, vector<variable> out, bool isSigned, int compNum, int outputPos, int withinIf, std::string line)
{
    line_       = line;
    type_       = type;
    dw_         = datawidth;
    isSigned_   = isSigned;
    lat_        = findLatency();
    compNum_    = compNum;
    outputPos_  = outputPos;
    withinIf_   = withinIf;
    sctype_     = comp2Str();
    scdw_       = dw2Str();
    //Scheduler Additions
    asapFrame_  = -1;
    alapFrame_  = -1;
    fdsFrame_   = -1;
    restype_    = whichResource();
    alreadyPrinted_ = false;


    for (int i=0; i<in.size(); i++)
    {
        in_.push_back( variable(in[i]) ) ;
    }

    for (int i=0; i<out.size(); i++)
    {
        out_.push_back( variable(out[i]) );
    }

}

// Copy constructor
component::component(const component& in_comp)
{
    line_       = in_comp.line_;
    type_       = in_comp.type_;
    dw_         = in_comp.dw_;
    isSigned_   = in_comp.isSigned_;
    lat_        = in_comp.lat_;
    compNum_    = in_comp.compNum_;
    outputPos_  = in_comp.outputPos_;
    withinIf_   = in_comp.withinIf_;
    sctype_     = in_comp.sctype_;
    scdw_       = in_comp.scdw_;
    asapFrame_  = in_comp.asapFrame_;
    alapFrame_  = in_comp.alapFrame_;
    fdsFrame_   = in_comp.fdsFrame_;
    restype_    = in_comp.restype_;
    alreadyPrinted_ = in_comp.alreadyPrinted_;

    for (int i=0; i<in_comp.in_.size(); i++)
    {
        in_.push_back( variable(in_comp.in_[i]) ) ;
    }

    for (int i=0; i<in_comp.out_.size(); i++)
    {
        out_.push_back( variable(in_comp.out_[i]) );
    }

    for (int i=0; i<in_comp.parent_.size(); i++)
    {
        parent_.push_back( in_comp.parent_[i] );
    }

    for (int i=0; i<in_comp.child_.size(); i++)
    {
        child_.push_back( in_comp.child_[i] );
    }
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

std::string component::comp2Str()
{
    if( !isSigned_ )
    {
        switch(type_)
        {
            case comp_type::Variables:  return "reg";
            case comp_type::Registers:  return "wire";
            case comp_type::Wires:      return "wire";
            case comp_type::Inputs:     return "input";
            case comp_type::Outputs:    return "output";
            case comp_type::REG:        return "REG";
            case comp_type::ADD:        return "ADD";
            case comp_type::SUB:        return "SUB";
            case comp_type::MUL:        return "MUL";
            case comp_type::COMP:       return "COMP";
            case comp_type::MUX:        return "MUX2x1";
            case comp_type::SHR:        return "SHR";
            case comp_type::SHL:        return "SHL";
            case comp_type::DIV:        return "DIV";
            case comp_type::MOD:        return "MOD";
            case comp_type::INC:        return "INC";
            case comp_type::DEC:        return "DEC";
            default: return "";
        }
    }
    else
    {
        switch(type_)
        {
            case comp_type::Variables:  return "reg";
            case comp_type::Registers:  return "wire";
            case comp_type::Wires:      return "wire";
            case comp_type::Inputs:     return "input";
            case comp_type::Outputs:    return "output";
            case comp_type::REG:        return "SREG";
            case comp_type::ADD:        return "SADD";
            case comp_type::SUB:        return "SSUB";
            case comp_type::MUL:        return "SMUL";
            case comp_type::COMP:       return "SCOMP";
            case comp_type::MUX:        return "SMUX2x1";
            case comp_type::SHR:        return "SSHR";
            case comp_type::SHL:        return "SSHL";
            case comp_type::DIV:        return "SDIV";
            case comp_type::MOD:        return "SMOD";
            case comp_type::INC:        return "SINC";
            case comp_type::DEC:        return "SDEC";
            default: return "";
        }
    }
    return "";
}

std::string component::dw2Str()
{
    if (type_ < comp_type::REG) // Is input, output, wire, or register
    {
        switch(dw_)
        {
            case comp_size:: ONE:       return"";
            case comp_size:: TWO:       return "[1:0]";
            case comp_size:: EIGHT:     return "[7:0]";
            case comp_size:: SIXTEEN:   return "[15:0]";
            case comp_size:: THIRTYTWO: return "[31:0]";
            case comp_size:: SIXTYFOUR: return "[63:0]";
            default: return "";
        }
    }   
    else
    {
        switch(dw_)
        {
            case comp_size:: ONE:       return "#(.DATAWIDTH(0))";
            case comp_size:: TWO:       return "#(.DATAWIDTH(2))";
            case comp_size:: EIGHT:     return "#(.DATAWIDTH(8))";
            case comp_size:: SIXTEEN:   return "#(.DATAWIDTH(16))";
            case comp_size:: THIRTYTWO: return "#(.DATAWIDTH(32))";
            case comp_size:: SIXTYFOUR: return "#(.DATAWIDTH(64))";
            default: return "";
        }
    }
    return "";
}

std::string component::trunc(){
    switch(dw_)
        {
            case comp_size:: ONE:       return "[0]";
            case comp_size:: TWO:       return "[1:0]";
            case comp_size:: EIGHT:     return "[7:0]";
            case comp_size:: SIXTEEN:   return "[15:0]";
            case comp_size:: THIRTYTWO: return "[31:0]";
            case comp_size:: SIXTYFOUR: return "[63:0]";
            default: return "";
        }
}
std::string component::cPadd(){
    switch(dw_)
        {
            case comp_size:: ONE:       return"";
            case comp_size:: TWO:       return "1-";
            case comp_size:: EIGHT:     return "7-";
            case comp_size:: SIXTEEN:   return "15-";
            case comp_size:: THIRTYTWO: return "31-";
            case comp_size:: SIXTYFOUR: return "63-";
            default: return "";
        }
}

std::string component::writeLine()
{
    std::string nL = "\n";
    std::string tab="\t";
    std::string spc = " ";
    std::string opn = "(";
    std::string cls = ")";
    std::string sc = ";";
    std::string clsc = ");";
    std::string com = ",";
    std::string wire = "wire";
    std::string cOpen = "{", cCls="}", zBit = "1'b0";
    std::string out = "";
    std::string lineCopy = line_;

    if(type_<comp_type::REG){
        out = tab+comp2Str();
        if(type_==comp_type::Outputs){
            out.append(spc+wire+spc+dw2Str()+spc);
        }
        else{
            out.append(spc+dw2Str()+spc);
        }
        for (int i=0;i<in_.size();i++){
            out.append(in_[i].name_);
            out.append(com);
        }
        for (int i=0;i<out_.size();i++){
            out.append(out_[i].name_);
            out.append(com);
        }
        int _trailingComma=out.size();
        out = out.substr(0,_trailingComma-1);
        out.append(sc);
    }
    else
    {
        out = replaceString(lineCopy, "=", "<=") + ";";
    }
    alreadyPrinted_ = true;
    return out;
}

void component::printComponent(std::ofstream& fout)
{

    fout << std::endl;
    fout << "New Component"  << std::endl;
    fout << "Line:"          << std::endl << line_ << std::endl;
    fout << "Type:         " << type2str(type_) << std::endl;
    fout << "Resource:     " << restype_ << std::endl;
    fout << "Number:       " << compNum_ << std::endl;
    fout << "OutputPos:    " << outputPos_ << std::endl;
    fout << "Size:         " << size2str(dw_) << std::endl;
    fout << "Signed:       " << isSigned_ << std::endl;
    fout << "Latency:      " << lat_ << std::endl;
    
    fout << std::endl ;
    fout << "Within If Statement: " << withinIf_ << std::endl;
    fout << std::endl ;

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

    fout << "ASAP TF:      " << asapFrame_ << std::endl;
    fout << "ALAP TF:      " << alapFrame_ << std::endl;
    fout << "Scheduled TF: " << fdsFrame_  << std::endl;
    fout << "Parents:" << std::endl;
    for(int i=0; i<parent_.size(); i++)
    {
        fout << "      " << parent_[i] << std::endl;
    }
    fout << "Children:" << std::endl;
    for(int i=0; i<child_.size(); i++)
    {
        fout << "      " << child_[i] << std::endl;
    }
}

resource component::whichResource(){

    switch(type_)
    {
        case comp_type::ADD:        return resource::ADD_SUB;
        case comp_type::SUB:        return resource::ADD_SUB;
        case comp_type::MUL:        return resource::MULT;
        case comp_type::COMP:       return resource::LOGIC;
        case comp_type::MUX:        return resource::LOGIC;
        case comp_type::SHR:        return resource::LOGIC;
        case comp_type::SHL:        return resource::LOGIC;
        case comp_type::REG:        return resource::LOGIC;
        case comp_type::DIV:        return resource::DIV_MOD;
        case comp_type::MOD:        return resource::DIV_MOD;
        case comp_type::INC:        return resource::ADD_SUB;
        case comp_type::DEC:        return resource::ADD_SUB;
        default: return resource::UNINIT;
    }
}

std::string component::replaceString( std::string& s, const std::string& toReplace, const std::string& replaceWith)
{
    std::size_t pos = s.find(toReplace);
    if (pos == std::string::npos)
    {
        return s;
    }
    return s.replace(pos, toReplace.length(), replaceWith);
}