#include "pschedule.h"
#include "component.h"
#include "fileparser.h"
#include "latencycalculator.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// -------------------------------------------------------------------------------
// 
// -------------------------------------------------------------------------------
pschedule::pschedule(){
    latconstrnt_ = 6;

    //alap(compVec);
}


// -------------------------------------------------------------------------------
// 
// -------------------------------------------------------------------------------
void pschedule::performScheduling(std::vector<component>& compVec){

    compVec_ = compVec;

    asap();

    alap();

    //NOTE: Need to add array cleanup
    buildFDSTable();

    outputDebug();

    return;
}


void pschedule::asap(){
    return;
}


// -------------------------------------------------------------------------------
/*
The idea behind alap is to start with the end nodes by setting their time frame to the latency constraint. Next, go to the parent node and set it's ALAP time frame to the preceding time frame of the end node. Repeat this process recursively until we've mapped out all the upstream nodes
*/
// -------------------------------------------------------------------------------
void pschedule::alap(){

    if (DEBUG) //ASAP test case for circuit 5
    {
        compVec_[4].asapFrame_ = 1;
        compVec_[4].child_.push_back(8);

        compVec_[5].asapFrame_ = 1;
        compVec_[5].child_.push_back(8);

        compVec_[6].asapFrame_ = 1;
        compVec_[6].child_.push_back(7);

        compVec_[7].asapFrame_ = 2;
        compVec_[7].parent_.push_back(6);
        compVec_[7].child_.push_back(8);

        compVec_[8].asapFrame_ = 4;
        compVec_[8].parent_.push_back(4);
        compVec_[8].parent_.push_back(5);
        compVec_[8].parent_.push_back(7);
    }

    std::vector<int> endnodes;

    //iterate through components and find the end nodes. End nodes will have zero children
    for (int compidx=0; compidx < compVec_.size(); compidx++)
    {
        if (compVec_[compidx].asapFrame_ > 0 && compVec_[compidx].child_.size() <= 0)
        {
            endnodes.push_back( compidx );
        }
    }

    //Start at endnodes. Recurse through parents to determine time frames
    for (int i=0; i < endnodes.size(); i++)
    {
        recurse(endnodes[i]);
    }

    return;
}


// -------------------------------------------------------------------------------
// 
// -------------------------------------------------------------------------------
void pschedule::recurse(int nodeidx)
{

    //set alap time based on succeeding nodes. If end node, set to latency constraint
    if (compVec_[nodeidx].child_.size() <= 0)
    {
        //trick the function into thinking end node has successor 1 frame after latency constraint
        compVec_[nodeidx].alapFrame_ = findalaptf(compVec_[nodeidx].restype_, latconstrnt_+1);
    }
    else
    {
        //find the youngest frame of possible children
        int age = 0;
        int youngestage = 0;
        int newframe = 0;

        for (int i=0; i < compVec_[nodeidx].child_.size(); i++)
        {
            age = (compVec_[compVec_[nodeidx].child_[i]].alapFrame_ > 0) ? compVec_[compVec_[nodeidx].child_[i]].alapFrame_ : 0;

            youngestage = ( ( compVec_[compVec_[nodeidx].child_[i]].alapFrame_ < age ) &&
                            ( compVec_[compVec_[nodeidx].child_[i]].alapFrame_ > 0 ) )
                         ? compVec_[compVec_[nodeidx].child_[i]].alapFrame_ : age;
        }

        //Determine what the ALAP time frame should be based on youngest child and resource type
        compVec_[nodeidx].alapFrame_ = findalaptf(compVec_[nodeidx].restype_, youngestage);

    }

    //Go on to parent nodes. If no parents, we're done!
    for (int i = 0; i< compVec_[nodeidx].parent_.size(); i++)
    {
        recurse( compVec_[nodeidx].parent_[i] );
    }

    return;
}


// -------------------------------------------------------------------------------
// Find the ALAP time frame
// -------------------------------------------------------------------------------
int pschedule::findalaptf( resource restype, int childtf){

    int delay;
    int newframe;

    switch (restype)
    {
        case resource::ADD_SUB: delay = 1; break;
        case resource::MULT: delay = 2; break;
        case resource::DIV_MOD: delay = 3; break;
        case resource::LOGIC: delay = 1; break;
        default: delay = 100; break;
    }

    newframe = childtf - delay;

    return newframe;
}


// -------------------------------------------------------------------------------
// TODO: -Make most of the code below modular, so that we can call single function
//        for all 4 resource types
//       -Better handle the pointer cleanup below (I don't think I did this correctly
//        anyways)
//       -Sum the probabilities (or handle in separate function). One way to do it
//        is to add an extra row to the table for total values
// -------------------------------------------------------------------------------
void pschedule::buildFDSTable(){

    std::vector<int> nodeVec;

    //iterate through compvec, looking for components with ASAP/ALAP times (ie nodes). Fill out the FDS table as we go
    for (int i=0; i< compVec_.size(); i++)
    {
        if (compVec_[i].alapFrame_ > 0 && compVec_[i].asapFrame_ > 0) nodeVec.push_back(i);
    }

    for (int i=0; i<nodeVec.size(); i++){
        std::cout << "node " << nodeVec[i] << ", ";
    }
    std::cout << std::endl;

    //instantiate FDS table of nodes x time frame
    //auto FDSTable [nodes.size()][latconstrnt_];
    //std::vector<std::vector<int>> FDSTable
    
    double prob = 0.0;
    double* FDSTable = new double[nodeVec.size() * latconstrnt_];

    //std::cout << "FDSTable size= " << sizeof(FDSTable)/sizeof(*FDSTable) << std::endl;
    std::cout << "FDSTable size= " << sizeof(FDSTable) << "nodevecsize = " << nodeVec.size() << "latency = " << latconstrnt_ << std::endl;

    //Initialize all values to 0.0
    for (int i=0; i < (nodeVec.size() * latconstrnt_); i++)
    {
        *(FDSTable + i) = 0.0;
    }

    std::cout.precision( 3 ); //float/double precision for couts

    for (int nodeidx = 0; nodeidx < nodeVec.size(); nodeidx++)
    {   
        //ASAP = ALAP -> 1.0 probability
        if ( (compVec_[nodeVec[nodeidx]].alapFrame_ - compVec_[nodeVec[nodeidx]].asapFrame_) == 0)
        {
            prob = 1.0;
            std::cout << "Printing prob = 1.0 for comp" << nodeVec[nodeidx] << std::endl;
        }
        else
        {
            //Don't forget to cast your integers
            prob = 1 / static_cast<double> (compVec_[nodeVec[nodeidx]].alapFrame_ - compVec_[nodeVec[nodeidx]].asapFrame_ + 1);
            
            std::cout << "Printing prob = " << std::fixed << prob << ", ALAP =" << compVec_[nodeVec[nodeidx]].alapFrame_ << std::endl;

            std::cout << "Diff = " << (compVec_[nodeVec[nodeidx]].alapFrame_ - compVec_[nodeVec[nodeidx]].asapFrame_ + 1) << std::endl;
        }

        for (int TF = compVec_[nodeVec[nodeidx]].asapFrame_ -1; TF < compVec_[nodeVec[nodeidx]].alapFrame_; TF++)
        {
            //FDSTable[ nodeidx * latconstrnt_ + TF] = prob;
            *(FDSTable + nodeidx * latconstrnt_ + TF) = prob;
        }
    }

    std::cout << "FDSTable size= " << sizeof(FDSTable)/sizeof(*FDSTable) << std::endl;

    //debug prints
    for (int nodeidx = 0; nodeidx < nodeVec.size(); nodeidx++)
    {
        std::cout << "printing new row= " << nodeidx << ": ";
        for (int j = 0; j < latconstrnt_; j++)
        {
            //std::cout << FDSTable[nodeidx * latconstrnt_ + j];
            std::cout << std::fixed << *(FDSTable + nodeidx * latconstrnt_ + j) << "  ";
        }
        std::cout << std::endl;
    }

    delete[] FDSTable;

    return;
}

// -------------------------------------------------------------------------------
// 
// -------------------------------------------------------------------------------
void pschedule::outputDebug()
{
    std::string outfile="./debug_out.txt";

    if (DEBUG)
    {
        fout_.open(outfile);

        fout_ << "Scheduler Component Order: " << std:: endl;
        for( int i = 0; i< compVec_.size(); i++ )
        {
            fout_ << "------------------------------------" << std::endl;
            compVec_[i].printComponent(fout_);
        }
    }

    fin_.close();
    fout_.close();

    return;
}