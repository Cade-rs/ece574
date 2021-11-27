#include "filewriter.h"
#include "common.h"
#include "component.h"


#include <iostream>
#include <regex>
#include <string>


// -------------------------------------------------------------------------------
// 
// -------------------------------------------------------------------------------
filewriter::filewriter(std::string outfile, std::vector<component> compVec, std::vector<std::vector<int>> states)
{
    outfile_ = outfile;
    fout_.open(outfile);
    compVec_ = compVec;
    states_ = states;
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
    fout_ << "`timescale 1ns / 1ps";
    fout_ << std::endl << std::endl;

    // Write module line
    fout_ << "module HLSM(Clk, Rst, Start, Done";

    // Add the inputs and outputs
    std::string mod = "";
    
    for(int i=0;i<compVec_.size();i++){
        if(compVec_[i].type_==comp_type::Inputs||compVec_[i].type_==comp_type::Outputs){
            for(int j=0;j<compVec_[i].in_.size();j++)
            {
                mod.append(", ");
                mod.append(compVec_[i].in_[j].name_);
            }
            for(int j=0;j<compVec_[i].out_.size();j++)
            {
                mod.append(", ");
                mod.append(compVec_[i].out_[j].name_);
            }
        }
    }

    // Wrap up
    fout_ << mod << ")" << std::endl << std::endl;

    // Write inputs, outputs, registers
    fout_ << "    input Clk, Rst, Start;" << std::endl;

    for (int i=0; i<compVec_.size(); i++)
    {
        // Inputs, outputs, variables are defined prior to regular components
        // Break when we're at regular components
        if( compVec_[i].type_ >= comp_type::REG )
        {
            break;
        }
        fout_ << compVec_[i].writeLine() << std::endl;
    }

    // Write state parameters
    int stateSize = states_.size() + 2; // Include wait and final states
    int stateBits = int(stateSize / 2); // This is zero-based, so a 3 would be 4 bits...

    fout_ << std::endl;
    fout_ << "\treg [" << stateBits << ":0] State;";
    fout_ << std::endl << std::endl;

    fout_ << "\tparameter [" << stateBits << ":0] ";
    // Don't print the last state param here, print it at the end and hope it works
    for(int i = 0; i < stateSize-1; i++)
    {
        fout_ << "S" << i << "=" << i << ", ";
    }
    // Last line for dat semicolon
    fout_ << "S" << stateBits << "=" << stateBits << ";" << std::endl;

    // Write always begin
    fout_ << "\talways @(posedge Clk) begin" << std::endl << std::endl;

    // Start with if Rst, else...
    fout_ << "\tif (Rst == 1) begin" << std::endl;
    fout_ << "\t\tDone <= 0;" << std::endl;
    fout_ << "\tend" << std::endl;
    fout_ << "\telse begin" << std::endl;

    // Start State case statement
    fout_ << "\t\tcase (State)" << std::endl << std::endl;

    // Print wait state
    fout_ << "\t\tS0: begin" << std::endl;
    fout_ << "\t\t\tif (Start == 1) begin" << std::endl;
    fout_ << "\t\t\t\tState <= S1;" << std::endl;
    fout_ << "\t\t\tend" << std::endl;
    fout_ << "\t\t\telse begin" << std::endl;
    fout_ << "\t\t\t\tState <= S0;" << std::endl;
    fout_ << "\t\t\tend" << std::endl;
    fout_ << "\t\tend" << std::endl << std::endl;

    // Loop through the rest of the states
    std::vector<int> currState;
    int compNum = 0;
    for( int i = 0; i < states_.size(); i++)
    {
        currState = states_[i];
        // Print start of state
        fout_ << "\t\tS" << i+1 << ": begin" << std::endl;

        for( int j = 0; j < currState.size(); j++ )
        {
            compNum = currState[j];
            if( compNum >= compVec_.size() )
            {
                std::cout << std::endl << "State vector contains a non-existent component" << std::endl;
                continue;
            }
            component currComp(compVec_[compNum]);
            fout_ << "\t\t\t" << currComp.writeLine() << std::endl;
        }
        // Print end of state
        fout_ << "\t\t\tState <= S" << i+2 << ":" << std::endl;
        fout_ << "\t\tend" << std::endl << std::endl;

    }

    // Print final state
    fout_ << "\t\tS" << stateSize-1 <<": begin" << std::endl;
    fout_ << "\t\t\tDone <= 1;" << std::endl;
    fout_ << "\t\t\tState <= S0;" << std::endl;
    fout_ << "\t\tend" << std::endl ;
    fout_ << "\t\tendcase" << std::endl << std::endl;
    fout_ << "\tend" << std::endl;
    fout_ << "\tend" << std::endl;


    // End
    fout_ << std::endl;
    fout_ << "endmodule";
}

void filewriter::writeIf(int ifNum)
{

}