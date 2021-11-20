#include "filewriter.h"
#include "common.h"


#include <iostream>
#include <regex>
#include <string>


// -------------------------------------------------------------------------------
// 
// -------------------------------------------------------------------------------
filewriter::filewriter(std::string outfile, std::vector<component> compVec)
{
    outfile_ = outfile;
    fout_.open(outfile);
    compVec_ = compVec;
    error_ = false;
    
    if ( !fout_.is_open() )
    {
        std::cout << "ERROR: Unable to read file: " << outfile << "\n";
        error_ =  true;
    }
}

// -------------------------------------------------------------------------------
// 
// -------------------------------------------------------------------------------
void filewriter::writeFile()
{

    //fout_.open();
    fout_<<"\n`timescale 1ns / 1ps";
    std::string ofile,mod;
    //need to include the outfile name in the writefile function for module name
    ofile =outfile_;
    //Cutting off the file type to grab the name
    // Trim off the folder paths
    std::size_t pos;
    
    if( ofile.find("/") != std::string::npos )
    {
        pos = ofile.find_last_of("/");
        ofile.erase(0,pos+1);
    }

    // trim off the file extension
    pos = ofile.find_last_of(".");
    ofile = ofile.substr(0,pos);

    //Writing the first line
    mod = "\nmodule ";
    std::string opn = "("; //open parentheses
    std::string cls = ");";//close parentheses
    std::string semi = ";";
    std::string com=",";
    std::string clk = "Clk", rst = "Rst";
    std::string nL="\n",tab = "\t",iput="input",spc = " ";
    mod.append(ofile);
    mod.append(opn);

    for(int i=0;i<compVec_.size();i++){
        if(compVec_[i].type_==comp_type::Inputs||compVec_[i].type_==comp_type::Outputs){
            for(int j=0;j<compVec_[i].in_.size();j++){              
                
                mod.append(compVec_[i].in_[j].name_);
                mod.append(com);
            }
            for(int j=0;j<compVec_[i].out_.size();j++){

                mod.append(compVec_[i].out_[j].name_);
                mod.append(com);
                
            }           
        }
    }
    mod.append(clk+com+rst);
    //mod = mod.substr(0,mod.size());
    mod.append(cls);
    fout_<<nL+mod;
    fout_<<nL+tab+iput+spc+clk+com+rst+semi;
    for (int i=0; i<compVec_.size(); i++)
    {
        std::string ugh=nL+compVec_[i].writeLine();
        fout_<<ugh;
    }
    
    fout_<<"\nendmodule";
}