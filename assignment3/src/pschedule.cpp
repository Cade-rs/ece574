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
pschedule::pschedule(int latencyConstraint){
    latconstrnt_ = latencyConstraint;
}


// -------------------------------------------------------------------------------
//
// -------------------------------------------------------------------------------
void pschedule::performScheduling(std::vector<component>& compVec){

    compVec_ = compVec;

    asap();

    alap();

    FDS();

    outputDebug();

    return;
}


void pschedule::asap(){

    if (DEBUG){
        compVec_[4].asapFrame_ = -1;//1
        compVec_[4].child_.push_back(8);

        compVec_[5].asapFrame_ = -1;//1
        compVec_[5].child_.push_back(8);

        compVec_[6].asapFrame_ = -1;//1
        compVec_[6].child_.push_back(7);

        compVec_[7].asapFrame_ = -1;//2
        compVec_[7].parent_.push_back(6);
        compVec_[7].child_.push_back(8);

        compVec_[8].asapFrame_ = -1;//4
        compVec_[8].parent_.push_back(4);
        compVec_[8].parent_.push_back(5);
        compVec_[8].parent_.push_back(7);
    }

    std::vector <int> firstnodes;

    //iterate through the nodes to find the initial nodes. These nodes will have two inputs that are NOT outputs of any other node
    for (int compidx=0; compidx < compVec_.size(); compidx++){
        if (compVec_[compidx].compNum_ >= 0 && (compVec_[compidx].parent_.size() == 0 || compVec_[compidx].parent_.empty())){
            firstnodes.push_back(compidx);
            std::cout<<firstnodes.size()<<endl;
        }
    }
    
    //Start at initial nodes. Recurse through children to determine time frames
    for (int i=0; i < firstnodes.size(); i++){
        std::vector<int> foo_path;
        recurse_firstNodes(firstnodes[i]);
    }

    return;
}


// -------------------------------------------------------------------------------
/*
The idea behind alap is to start with the end nodes by setting their time frame 
to the latency constraint. Next, go to the parent node and set it's ALAP time frame
to the preceding time frame of the end node. Repeat this process recursively until
we've mapped out all the upstream nodes
*/
// -------------------------------------------------------------------------------
void pschedule::alap()
{

    if (DEBUG) //ASAP test case for circuit 5
    {
        compVec_[4].asapFrame_ = -1;
        compVec_[4].child_.push_back(8);

        compVec_[5].asapFrame_ = -1;
        compVec_[5].child_.push_back(8);

        compVec_[6].asapFrame_ = -1;
        compVec_[6].child_.push_back(7);

        compVec_[7].asapFrame_ = -1;
        compVec_[7].parent_.push_back(6);
        compVec_[7].child_.push_back(8);

        compVec_[8].asapFrame_ = -1;
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
            endnodes.push_back(compidx);
        }
    }

    //Start at endnodes. Recurse through parents to determine time frames
    for (int i=0; i < endnodes.size(); i++)
    {
        recurse(endnodes[i]);
    }

    return;
}
//--------------------------------------------------------------------------------
//Writing the Recursion Function For Initial Nodes
void pschedule::recurse_firstNodes(int nodeidx){
    std::cout<<"Another time frame down"<<endl;
    
    for(int i=0; compVec_[nodeidx].child_.size();i++){
        std::cout<<i<<endl;
        std::cout<<nodeidx<<endl;
        if(compVec_[nodeidx].parent_.empty()||compVec_[nodeidx].parent_.size()==0){ //Handling if the input to the recusion is from the firstnode array of time =1
            compVec_[nodeidx].asapFrame_=1;
        }
        else if (compVec_[nodeidx].asapFrame_>0){
            std::cout<<"A child was already accounted for"<<endl;
        }
        else{
            std::cout<<"Current time is:"<<compVec_[nodeidx].asapFrame_;
            compVec_[nodeidx].asapFrame_=(compVec_[nodeidx].restype_, compVec_[nodeidx].asapFrame_);  
            std::cout<<"New time is:"<<compVec_[nodeidx].asapFrame_;
        }
    }

    //Go on to child nodes. If no children, we're done!
    for (int i = 0; i< compVec_[nodeidx].child_.size(); i++){
        recurse_firstNodes(compVec_[nodeidx].child_[i]);
    }
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
// Force Directed Scheduling
// -------------------------------------------------------------------------------
void pschedule::FDS(){

    //FDS scheduling, 1 frame at a time
    for (int TF = 1; TF < latconstrnt_; TF++)
    {        
        //Run ASAP

            //If node has already been scheduled (check time frame?), set ASAP frame to scheduled time frame

        //Run ALAP

        //Update node resource vectors, only considering non-scheduled nodes

        //Calculate forces

        //Set FDS time frames/cycle numbers for winning nodes

    }

    //build individual resource compVecs
    std::vector<int> addVec;
    std::vector<int> multVec;
    std::vector<int> logicVec;
    std::vector<int> divVec;

    //iterate through compvec, looking for components with ASAP/ALAP times (ie nodes). Fill out the node vectors (filtered by resource type) as we go.
    for (int i=0; i< compVec_.size(); i++)
    {
        if (compVec_[i].alapFrame_ > 0 && compVec_[i].asapFrame_ > 0 && compVec_[i].restype_ == resource::ADD_SUB)
        {
            addVec.push_back(i);
        }
        else if (compVec_[i].alapFrame_ > 0 && compVec_[i].asapFrame_ > 0 && compVec_[i].restype_ == resource::MULT)
        {
            multVec.push_back(i);
        }
        else if (compVec_[i].alapFrame_ > 0 && compVec_[i].asapFrame_ > 0 && compVec_[i].restype_ == resource::LOGIC)
        {
            logicVec.push_back(i);
        }
        else if (compVec_[i].alapFrame_ > 0 && compVec_[i].asapFrame_ > 0 && compVec_[i].restype_ == resource::DIV_MOD)
        {
            divVec.push_back(i);
        }
    }
    
    //By passing member vectors by reference, this function updates the vectors internally
    buildFDSTable(addTable_, addProbs_, addVec);
    buildFDSTable(multTable_, multProbs_, multVec);
    buildFDSTable(logicTable_, logicProbs_, logicVec);
    buildFDSTable(divTable_, divProbs_, divVec);


    //debug prints- Leaving these in until ASAP + ALAP verified together
    for (int nodeidx = 0; nodeidx < addVec.size(); nodeidx++)
    {
        std::cout << "add printing new row= " << nodeidx << ": ";
        for (int j = 0; j < latconstrnt_; j++)
        {
            std::cout << std::fixed << addTable_[nodeidx * latconstrnt_ + j] << "  ";
        }
        std::cout << std::endl;
    }
    for (int nodeidx = 0; nodeidx < multVec.size(); nodeidx++)
    {
        std::cout << "mult printing new row= " << nodeidx << ": ";
        for (int j = 0; j < latconstrnt_; j++)
        {
            std::cout << std::fixed << multTable_[nodeidx * latconstrnt_ + j] << "  ";
        }
        std::cout << std::endl;
    }
    for (int nodeidx = 0; nodeidx < logicVec.size(); nodeidx++)
    {
        std::cout << "logic printing new row= " << nodeidx << ": ";
        for (int j = 0; j < latconstrnt_; j++)
        {
            std::cout << std::fixed << logicTable_[nodeidx * latconstrnt_ + j] << "  ";
        }
        std::cout << std::endl;
    }
    for (int nodeidx = 0; nodeidx < divVec.size(); nodeidx++)
    {
        std::cout << "div printing new row= " << nodeidx << ": ";
        for (int j = 0; j < latconstrnt_; j++)
        {
            std::cout << std::fixed << divTable_[nodeidx * latconstrnt_ + j] << "  ";
        }
        std::cout << std::endl;
    }

    std::cout << "add printing probs: " << std::endl;
    for (int nodeidx = 0; nodeidx < addProbs_.size(); nodeidx++)
    {
            std::cout << std::fixed << addProbs_[nodeidx] << "  ";
    }
    std::cout << std::endl;
    std::cout << "mult printing probs: " << std::endl;
    for (int nodeidx = 0; nodeidx < multProbs_.size(); nodeidx++)
    {
            std::cout << std::fixed << multProbs_[nodeidx] << "  ";
    }
    std::cout << std::endl;
    std::cout << "logic printing probs: " << std::endl;
    for (int nodeidx = 0; nodeidx < logicProbs_.size(); nodeidx++)
    {
            std::cout << std::fixed << logicProbs_[nodeidx] << "  ";
    }
    std::cout << std::endl;
    std::cout << "div printing probs: " << std::endl;
    for (int nodeidx = 0; nodeidx < divProbs_.size(); nodeidx++)
    {
            std::cout << std::fixed << divProbs_[nodeidx] << "  ";
    }
    std::cout << std::endl;

    return;
}


// -------------------------------------------------------------------------------
// Create the operation probabilities table and the resource distributions vector
// -------------------------------------------------------------------------------
void pschedule::buildFDSTable(std::vector<double>& FDSTable, std::vector<double>& probVec, std::vector<int> nodeVec){

    double prob = 0.0;
    std::cout.precision( 3 ); //float/double precision for couts

    //Determine operator probabilities for each node
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
        }

        //Add probabilities to correct Time Frames. They're are 1-based, not 0-based
        for (int TF = 1; TF <= latconstrnt_; TF++)
        {
            if ( (TF >= compVec_[nodeVec[nodeidx]].asapFrame_) && 
                (TF <= compVec_[nodeVec[nodeidx]].alapFrame_) )
            {
                FDSTable.push_back( prob );
            }
            else
            {
                FDSTable.push_back( 0.0 );
            }            
        }
    }

    // Build vector of resource distributions. Vector size equal to latency constraint
    for (int TF = 0; TF < latconstrnt_; TF++)
    {
        double sumTF = 0.0;
        for (int nodeidx = 0; nodeidx < nodeVec.size(); nodeidx++)
        {
            sumTF += FDSTable[nodeidx*latconstrnt_ + TF];
        }

        probVec.push_back(sumTF);
    }

    return;
}

// -------------------------------------------------------------------------------
// This was moved from fileparser
// -------------------------------------------------------------------------------
void pschedule::outputDebug()
{
    std::string outfile="./debug_out.txt";
    std::ofstream fout;

    if (DEBUG)
    {
        fout.open(outfile);

        fout << "Scheduler Component Order: " << std:: endl;
        for( int i = 0; i< compVec_.size(); i++ )
        {
            fout << "------------------------------------" << std::endl;
            compVec_[i].printComponent(fout);
        }
    }

    fout.close();

    return;
}