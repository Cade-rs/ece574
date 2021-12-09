#include "filewriter.h"
#include "common.h"
#include "component.h"


#include <iostream>
#include <regex>
#include <string>

void fillStates(std::vector<std::vector<int>>& states);

// -------------------------------------------------------------------------------
// 
// -------------------------------------------------------------------------------
filewriter::filewriter(std::string outfile, int latConstraint, std::vector<component> compVec, std::vector<ifStatement> ifStatements)
{
    outfile_        = outfile;
    latConstraint_  = latConstraint;
    compVec_        = compVec;
    //states_         = states;
    ifStatements_   = ifStatements;
    error_          = false;

    createStateVector();

    if( error_ )
    {
        return;
    }

    fout_.open(outfile);

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
    fout_ << "S" << stateSize-1 << "=" << stateSize-1 << ";" << std::endl;

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

            // Check for if statements
            if( compVec_[compNum].alreadyPrinted_ )
            {
                fout_ << "\t\t\t" << "// Placeholder for " << compVec_[compNum].writeLine() << std::endl;
            }
            else if ( compVec_[compNum].withinIf_ >= 0 )
            {
                writeIf(compVec_[compNum].withinIf_, compNum);
            }
            else
            {
                fout_ << "\t\t\t" << compVec_[compNum].writeLine() << std::endl;
            }
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

void filewriter::writeIf(int ifNum, int compNum)
{
    //std::cout << "in function" << std::endl;
    //std::cout << "if num " << ifNum << std::endl;
    static int recurseNum = 0;
    ifStatement currIf = ifStatements_[ifNum];

    if( currIf.withinIf >= 0 )
    {
        //std::cout << "recurse" << std::endl;
        writeIf(currIf.withinIf);
        recurseNum++;
    }

    if(currIf.isElse)
    {
        //std::cout << "is else" << std::endl;
        ifStatement pairedIf =  ifStatements_[currIf.correspondingIfElse];
        fout_ << "\t\t\t" << "if ( " << pairedIf.condition << " ) begin"<< std::endl;
        fout_ << "\t\t\t" << "end" << std::endl;
        fout_ << "\t\t\t" << "else begin" << std::endl;
        if( compNum >= 0)
        {
            fout_ << "\t\t\t\t" << compVec_[compNum].writeLine() << std::endl;
            fout_ << "\t\t\t" << "end" << std::endl;
        }
    }
    else
    {
        //std::cout << "not else" << std::endl;
        fout_ << "\t\t\t" << "if ( " << currIf.condition << " ) begin"<< std::endl;
        if( compNum >= 0 )
        {
            fout_ << "\t\t\t\t" << compVec_[compNum].writeLine() << std::endl;
            fout_ << "\t\t\t" << "end" << std::endl;
        }
    }

    while( recurseNum>0 && compNum >= 0 )
    {
        fout_ << "\t\t\t" << "end" << std::endl;
        recurseNum--;
    }

}


void filewriter::createStateVector()
{
    // Create a vector of vectors of ints stating which state contains which components
    for( int i=0; i < latConstraint_; i++ )
    {
        std::vector<int> state;
        for( int j = 0; j < compVec_.size(); j++ )
        {
            if( ( compVec_[j].fdsFrame_ == i+1 ) ||
                ( compVec_[j].fdsFrame_ == i && compVec_[j].restype_ == resource::MULT ) || 
                ( compVec_[j].fdsFrame_ == i && compVec_[j].restype_ == resource::DIV_MOD ) || 
                ( compVec_[j].fdsFrame_ == i-1 && compVec_[j].restype_ == resource::DIV_MOD ) )
            {
                state.push_back(j);
            }
            else if( compVec_[j].fdsFrame_ > latConstraint_ )
            {
                std::cout << "Error: Component not scheduled within latency constraint: " << j << std::endl;
                error_ = true;
            }
            else if( compVec_[j].fdsFrame_ == -1 && compVec_[j].type_ >= comp_type::REG )
            {
                std::cout << "Error: Component not scheduled: " << j << std::endl;
                error_ = true;
                if( DEBUG )
                {
                    continue;
                }
                break;
            }
        }
        
        if( state.size() > 0 )
        {
            states_.push_back(state);
        }
    }

    if( error_  )
    {
        if( DEBUG )
        {
            std::cout << "Falling back on pre-canned scheduling" << std::endl;
            states_.clear();
            fillStates(states_);
        }
        else 
        {
            std::cout << "Scheduling failed. Exiting..." << std::endl;
        }
    }
}





void fillStates(std::vector<std::vector<int>>& states)
{
    std::vector<int> state1;
    state1.push_back(4);
    state1.push_back(5);
    state1.push_back(6);
    state1.push_back(7);

    std::vector<int> state2;
    state2.push_back(8);
    state2.push_back(9);
    state2.push_back(10);

    std::vector<int> state3;
    state3.push_back(11);
    state3.push_back(12);
    state3.push_back(13);
    state3.push_back(14);
    state3.push_back(15);
    state3.push_back(16);
    state3.push_back(17);
    state3.push_back(18);

    states.push_back(state1);
    states.push_back(state2);
    states.push_back(state3);

}