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

        //std::cout << "test thing equals" << std::to_string(compVec_[8].parent_[1]) << std::endl;
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
    //std::cout << "amount of endnodes= " << endnodes.size() << std::endl;

    for (int i=0; i < endnodes.size(); i++)
    {
        recurse(endnodes[i]);
    }

    return;
}


// -------------------------------------------------------------------------------
// This is pretty unefficient seeing as we pass in the entire comp vec every time, 
// but it makes things easier
// -------------------------------------------------------------------------------
void pschedule::recurse(int nodeidx)
{
    //std::cout << "Entering recurse. node = " << nodeidx << "childnum = " << compVec_[nodeidx].child_.size() << std::endl;

    //set alap time based on succeeding nodes. If end node, set to latency constraint
    if (compVec_[nodeidx].child_.size() <= 0)
    {
        //trick the function into thinking end node has successor 1 frame after latency constraint
        compVec_[nodeidx].alapFrame_ = findalaptf(compVec_[nodeidx].restype_, latconstrnt_+1);

        //std::cout << "recurse1: node = " << nodeidx << ", alapFrame = " << compVec_[nodeidx].alapFrame_ << std::endl;
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

            //std::cout << "recurse2: node = " << nodeidx << ", youngest = " << youngestage << std::endl;
        }

    //std::cout << "recurse3: node = " << nodeidx << ", resource = " << compVec_[nodeidx].restype_ << ", comp type = " << compVec_[nodeidx].type_ << std::endl;

        //Determine what the ALAP time frame should be based on youngest child and resource type
        newframe = findalaptf(compVec_[nodeidx].restype_, youngestage);

        //Check if this node has been previously processed and determine the earliest of the two time frames - THIS IS UNNECESSARY WHY DID YOU DO THIS STUPID STUPID STUPID STUPID STUPID STU
        if (compVec_[nodeidx].alapFrame_ > 0)
        {
            compVec_[nodeidx].alapFrame_ = (newframe < compVec_[nodeidx].alapFrame_) ? newframe : compVec_[nodeidx].alapFrame_;
        }
        else
        {
            compVec_[nodeidx].alapFrame_ = newframe;
        }

        //std::cout << "recurse4: node = " << nodeidx << ", alapFrame = " << compVec_[nodeidx].alapFrame_ << std::endl;
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

    //std::cout << "findalaptf: resource = " << restype << ", delay = " << delay << ", childframe = " << childtf << std::endl;

    newframe = childtf - delay;

    return newframe;
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