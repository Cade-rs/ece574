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

std::string component::comp2Str()
{
    if( !isSigned_ )
    {
        switch(type_)
        {
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
            case comp_size:: ONE:       return"[0]";
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
<<<<<<< Updated upstream
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
    std::string out;

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
    else if(type_!=comp_type::COMP){
        out = tab+comp2Str();
        out.append(tab+dw2Str());
        std::string compNumS = to_string(compNum_);
        out.append(spc+comp2Str()+compNumS);
        out.append(opn);
        
        for(int i=0;i < in_.size(); i++){
            //out.append(in_[i].name_);
            if(in_[i].size_<dw_){
                if (isSigned_){
                    std::string signc_="$signed(";
                    out.append(signc_+in_[i].name_+cls);
                }
                else{
                    out.append(cOpen+cOpen+cPadd()+in_[i].iPadd()+cOpen+zBit+cCls+cCls+com+in_[i].name_+cCls);
                }
            }
            else if(in_[i].size_>dw_){
                out.append(in_[i].name_);
                out.append(trunc());
            }
            else{
                out.append(in_[i].name_);
            }
            out.append(com);
        }
        if (type_==comp_type::REG){
            std::string clk="Clk", rst="Rst";
            out.append(clk+com+rst+com);
        }
        if(out_[0].size_<dw_){
            if(isSigned_){
                std::string signc_="$signed(";
                out.append(signc_+out_[0].name_+cls);
            }
            else{
                out.append(cOpen+cOpen+cPadd()+out_[0].iPadd()+cCls+cCls+com+out_[0].name_+cCls);
            }
        }
        else if(out_[0].size_>dw_){
            out.append(out_[0].name_);
            out.append(trunc());
        }
        else{
            out.append(out_[0].name_);
        }
        out.append(clsc);
    }
    else{
        out = tab+comp2Str();
        out.append(tab+dw2Str());
        std::string compNumS = to_string(compNum_);
        out.append(spc+comp2Str()+compNumS);
        out.append(opn);
        
        for(int i=0;i < in_.size(); i++){
            out.append(in_[i].name_);
            out.append(com);
        }
        for(int i=0; i<3;i++){
            if(i!=outputPos_-1){
                out.append(spc);
                out.append(com);
            }           
            else{
                out.append(out_[0].name_);
                if(out_[0].size_ != comp_size::ONE){
                    out.append("[0]");
                }
                out.append(com);
            }
        }
        int _trailingComma=out.size();
        out = out.substr(0,_trailingComma-1);
        out.append(clsc);

    }
    return out;
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
=======
    //creating the instantiation of the components
    std::string c_type = in_comp.type_;
    std::string d_width= in_comp.dw_;
    std::string c_setup= "\t#(.DATAWIDTH(";
    std::string c_sclose="))";
    std::string c_ivar = in_comp.in_;
    std::string c_ovar = in_comp.out_;

    return(c_type+c_setup+d_width+c_sclose+)
    //return( "THANKS FOR BREAKING THE CODE BRANDON");
>>>>>>> Stashed changes
}