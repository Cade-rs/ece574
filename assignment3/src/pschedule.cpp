#include "pschedule.h"
#include "component.h"
#include "fileparser.h"
#include "latencycalculator.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

pschedule::pschedule(std::vector<component>& compVec){
    latconstrnt_ = 6;

    alap(compVec);
}

void pschedule::asap(std::vector<component> cV){
    return;
}

/*
The idea behind alap is to start with the end nodes by setting their time frame to the latency constraint. Next, go to the parent node and set it's ALAP time frame to the preceding time frame of the end node. Repeat this process recursively until we've mapped out all the upstream nodes
*/
void pschedule::alap(std::vector<component> cV){

    std::vector<int> endnodes;

    //iterate through components and find the end nodes. End nodes will have zero children
    for (int compidx=0; compidx < cV.size(); compidx++)
    {
        if (cV[compidx].asapFrame_ > 0 && cV[compidx].child_.size() > 0)
        {
            endnodes.push_back( compidx );
        }
    }

    for (int i; i < endnodes.size(); i++)
    {
        recurse( cV, endnodes[i]);
    }

    return;
}

//This is pretty unefficient seeing as we pass in the entire comp vec every time, but it makes things easier
void pschedule::recurse(std::vector<component> cV, int nodeidx)
{
    //set alap time based on succeeding nodes. If end node, set to latency constraint
    if (cV[nodeidx].child_.size() <= 0)
    {
        //trick the function into thinking end node has successor 1 frame after latency constraint
        cV[nodeidx].alapFrame_ = findalaptf(cV[nodeidx].restype_, latconstrnt_+1);
    }
    else
    {
        //find the youngest frame of possible children
        int youngestage = 0;
        int newframe = 0;

        for (int i=0; i < cV[nodeidx].child_.size(); i++)
        {
            youngestage = (cV[cV[nodeidx].child_[i]].alapFrame_ < youngestage) ? cV[cV[nodeidx].child_[i]].alapFrame_ : youngestage;
        }

        newframe = findalaptf(cV[nodeidx].restype_, youngestage);

        //Check if this node has been previously processed and determine the earliest of the two time frames
        if (cV[nodeidx].alapFrame_ > 0)
        {
            cV[nodeidx].alapFrame_ = (newframe < cV[nodeidx].alapFrame_) ? newframe : cV[nodeidx].alapFrame_;
        }
        else
        {
            cV[nodeidx].alapFrame_ = newframe;
        }
    }

    //Go on to parent nodes. If no parents, we're done!
    for (int i = 0; i< cV[nodeidx].parent_.size(); i++)
    {
        recurse( cV, cV[nodeidx].parent_[i] );
    }

    return;
}

//Find the ALAP time frame
int pschedule::findalaptf( resource restype, int childtf){

    int delay;
    int newframe;

    switch (restype)
    {
        case resource::ADD_SUB: delay = 1;
        case resource::MULT: delay = 2;
        case resource::DIV_MOD: delay = 3;
        case resource::LOGIC: delay = 1;
    }

    newframe = childtf - delay;

    return newframe;
}