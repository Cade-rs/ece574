#include "pschedule.h"
#include "component.h"
#include "fileparser.h"
#include "common.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <numeric>
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
bool pschedule::performScheduling(std::vector<component>& compVec, std::vector<ifStatement>& ifStatements){

    compVec_ = compVec;
    ifStatements_ = ifStatements;
    error_ = false;

    buildFamily();

    //Should this go here?
    what_if_branch();

    FDS();

    //outputDebug();

    return error_;
}

// -------------------------------------------------------------------------------
//
// -------------------------------------------------------------------------------
void pschedule::buildFamily()
{
    for (int i=0; i < compVec_.size(); i++)
    {
        compVec_[i].parent_.clear();
        compVec_[i].child_.clear();
        //determine if valid component (ie no I/O/Reg/Wire)
        if (compVec_[i].type_ >= 0)
        {
            //Find parents
            for (int j=0; j < compVec_[i].in_.size(); j++) //check all inputs
            {
                for (int k=0; k < compVec_.size(); k++) //check all other comps
                {
                    for (int l=0; l < compVec_[k].out_.size(); l++) //check other comp outs
                    {
                        //check if potential parent is valid component, has outputs, and is match
                        if (compVec_[k].type_ >= 0 &&
                            compVec_[i].in_[j].name_ == compVec_[k].out_[l].name_)
                        {
                            compVec_[i].parent_.push_back ( compVec_[k].compNum_ );
                        }
                    }
                }
            }

            //Find children
            for (int j=0; j < compVec_[i].out_.size(); j++) //check all inputs
            {
                for (int k=0; k < compVec_.size(); k++) //check all other comps
                {
                    for (int l=0; l < compVec_[k].in_.size(); l++) //check other comp outs
                    {
                        //check if potential parent is valid component, and is match
                        if (compVec_[k].type_ >= 0 &&
                            compVec_[i].out_[j].name_ == compVec_[k].in_[l].name_)
                        {
                            compVec_[i].child_.push_back ( compVec_[k].compNum_ );
                            //std::cout << "setting child as " << compVec_[k].compNum_ << std::endl;
                        }
                    }
                }
            }
        }
    }
}

void pschedule::asap(int TF){
/*
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
*/
    std::vector <int> firstnodes, prevnodes;
    firstnodes.clear();
    prevnodes.clear();

    //std::cout << "Inside ASAP, TF = " << TF << std::endl;

    //reset asap frames
    for (int i=0; i<compVec_.size(); i++)
    {
        compVec_[i].asapFrame_ = -1;

        //std::cout << "asap begin. Comp, parent size, child size =" << compVec_[i].compNum_ << ", " << compVec_[i].parent_.size() << ", " << compVec_[i].child_.size() << std::endl;

    }

    //std::cout << "Finding previously scheduled nodes: " ;
    //Find previously scheduled nodes
    for (int i=0; i < compVec_.size(); i++)
    {
        if (compVec_[i].fdsFrame_ > 0 && ( compVec_[i].fdsFrame_ < TF ))
        {
            prevnodes.push_back( i );
            //std::cout << i << ", " ;
            
        }
    }
    //std::cout << std::endl;

    //iterate through the nodes to find headnodes
    for (int compidx=0; compidx < compVec_.size(); compidx++)
    {
        //Only consider true components (ie no I/O/reg/wire) and non-scheduled nodes
        if (compVec_[compidx].type_ >= 0 && compVec_[compidx].fdsFrame_ < 0 )
        {
            //Look for initial headnodes (ie no parents)
            if ( (compVec_[compidx].parent_.size() == 0 || compVec_[compidx].parent_.empty()) ) 
            {
                //std::cout << "Printing initial node : " << compidx << std::endl;


                compVec_[compidx].asapFrame_=TF;
                firstnodes.push_back(compidx);
            }
            //Look for children of previously scheduled nodes
            else
            {
                //std::cout << "Looking for children out of for loop" << std::endl;

                for (int i=0; i<prevnodes.size(); i++)
                {
                    //Looking for children at 
                    int newframe = -1;

                    //add children to headnodes but don't repeat
                    for(int j=0; j < compVec_[prevnodes[i]].child_.size(); j++)
                    {

                        int ifexists = 0;
                        int successor = compVec_[prevnodes[i]].child_[j];


                        newframe = findasaptf( compVec_[prevnodes[i]].restype_, compVec_[prevnodes[i]].fdsFrame_ );


                        compVec_[successor].asapFrame_ = (newframe > compVec_[successor].asapFrame_) ?
                                newframe : compVec_[successor].asapFrame_;

                        if (compVec_[successor].fdsFrame_ < 0)
                        {
                            ifexists = std::find(firstnodes.begin(), firstnodes.end(),successor)!=firstnodes.end();
                        }

                        if (!ifexists)
                        {
                            firstnodes.push_back( compVec_[prevnodes[i]].child_[j] );
                        }
                    }
                }

                //compVec_[compidx].asapFrame_=compVec_[compidx].fdsFrame_;
            }
        }
        /*else if(compVec_[compidx].type_>=0 && 
                 compVec_[compidx].fdsFrame_ < 0 &&
                 (compVec_[compidx].parent_.size()!=0 || !compVec_[compidx].parent_.empty()))
        {
            compVec_[compidx].asapFrame_=0;
        }
        

       std::cout << "comp num, asap = " << compVec_[compidx].compNum_ << ", " << compVec_[compidx].asapFrame_ << std::endl;

       if (compVec_[compidx].asapFrame_ > latconstrnt_)
       {
           error_ =  true;
       }

       return;*/
    }
/*
    std::cout << "Printing prevnodes: " ;
    for (int i=0; i < prevnodes.size(); i++)
    {
        std::cout << prevnodes[i] << ", " ;
    }
    std::cout << std::endl;

    std::cout << "Printing firstnodes: " ;
    for (int i=0; i < firstnodes.size(); i++)
    {
        std::cout << firstnodes[i] << ", " ;
    }
    std::cout << std::endl;
*/
    //Start at initial nodes. Recurse through children to determine time frames
    for (int i=0; i < firstnodes.size(); i++)
    {
        std::vector<int> foo_path;
        recurse_firstNodes(firstnodes[i]);
    }

    return;
}


//--------------------------------------------------------------------------------
//Writing the Recursion Function For Initial Nodes
void pschedule::recurse_firstNodes(int nodeidx)
{
    int child;
    int newframe;

    for(int i=0; i<compVec_[nodeidx].child_.size(); i++)
    {
        //std::cout << "comp, child= " << nodeidx << ", " << compVec_[nodeidx].child_[i] << std::endl;
    }

    for(int i=0; i < compVec_[nodeidx].child_.size(); i++)
    {
        child = compVec_[nodeidx].child_[i];

        //std::cout << "New child in question is: " << child << std::endl;

        if (compVec_[child].fdsFrame_ > 0)
        {
            compVec_[child].asapFrame_ = compVec_[child].fdsFrame_;
            //std::cout<<"New child asap frame as FDS frame = " << compVec_[child].asapFrame_ <<endl;

        }
        else
        {
            newframe = findasaptf( compVec_[nodeidx].restype_, compVec_[nodeidx].asapFrame_);

            compVec_[child].asapFrame_ = (newframe > compVec_[child].asapFrame_) ? 
                        newframe : compVec_[child].asapFrame_;

            //std::cout<<"New child asap frame = " << compVec_[child].asapFrame_ <<endl;
            //break;
        }
    }

    //Go on to child nodes. If no children, we're done!
    if(compVec_[nodeidx].child_.size() > 0)
    {
        //std::cout << "inside check for childies" << std::endl;
        for (int i = 0; i< compVec_[nodeidx].child_.size(); i++){
            recurse_firstNodes(compVec_[nodeidx].child_[i]);
        }
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
/*
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
*/
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
        int age = -1;
        int youngestage = -1;
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
// Find the ASAP time frame
// -------------------------------------------------------------------------------
int pschedule::findasaptf( resource restype, int parenttf){

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

    newframe = parenttf + delay;

    return newframe;
}

/* -------------------------------------------------------------------------------
  Force Directed Scheduling Hierarchy
  FDS
    -asap
    -alap
      -recurse
        -findalaptf
    -buildFDSTable
    -calculateForces
      -calculateSelfForce
        -calcSelfForce
        -calcPrePostForce
   ------------------------------------------------------------------------------- */
void pschedule::FDS(){

    //build/reset individual resource compVecs
    

    //FDS scheduling, 1 frame at a time
    for (int TF = 1; TF <= latconstrnt_; TF++)
    //for (int TF = 1; TF < 2; TF++)
    {   
        //reset resource compVecs, tables, probabilities, and nodes to be scheduled
        addVec_.clear(); multVec_.clear(); logicVec_.clear(); divVec_.clear();
        addTable_.clear(); multTable_.clear(); logicTable_.clear(); divTable_.clear();
        addProbs_.clear(); multProbs_.clear(); logicProbs_.clear(); divProbs_.clear();
        chosenOnes_.clear();

        //std::cout << "On Time Frame " << TF << std::endl;

        //Run ASAP
        asap(TF);

        //std::cout << "Now running ALAP" << std::endl;

        //Run ALAP. Shouldn't need to rerun this every time but might as well
        alap();

        for (int i=0; i< compVec_.size(); i++)
        {
            if (compVec_[i].asapFrame_ > compVec_[i].alapFrame_)
            {
                error_ = true;
                return;
            }
        }

        //Update node resource vectors, only considering non-scheduled nodes (ignoring non-nodal components ie I/O/Reg)
        for (int i=0; i< compVec_.size(); i++)
        {
            if (compVec_[i].alapFrame_ > 0 && compVec_[i].asapFrame_ > 0 && compVec_[i].fdsFrame_ <= 0)
            {
                switch (compVec_[i].restype_)
                {
                    case resource::ADD_SUB: 
                        addVec_.push_back(i);
                        break;
                    case resource::MULT:
                        multVec_.push_back(i);
                        break;
                    case resource::LOGIC:
                        logicVec_.push_back(i);
                        break;
                    case resource::DIV_MOD:
                        divVec_.push_back(i);
                        break;
                }    

            }
        }

        //Determine resource distributions. By passing member vectors by reference, this function updates the vectors internally
        //NOTE: can remove the tables from member variables if wanted
        if (addVec_.size() > 0)    buildFDSTable(addTable_, addProbs_, addVec_);
        if (multVec_.size() > 0)   buildFDSTable(multTable_, multProbs_, multVec_);
        if (logicVec_.size() > 0)  buildFDSTable(logicTable_, logicProbs_, logicVec_);
        if (divVec_.size() > 0)    buildFDSTable(divTable_, divProbs_, divVec_);

        //If possible to schedule node at current time frame, calculate forces and find the minimum
        for (int i=0; i< compVec_.size(); i++)
        {
            if (compVec_[i].alapFrame_ > 0 && compVec_[i].asapFrame_ > 0 && compVec_[i].asapFrame_ <= TF 
                 && compVec_[i].fdsFrame_ < 0)
            {
                int bestFrame = 0;
                //If we've reached our max frame (ALAP), schedule the node
                if (compVec_[i].alapFrame_ == TF)
                {
                    bestFrame = TF;
                    //std::cout << "TF == ALAP Frame" << std::endl;
                }
                else
                {
                    //std::cout << "Calculating forces" << std::endl;
                    bestFrame = calculateForces(TF, i);
                }

                //Set FDS time frames/cycle numbers if the least force frame matches current time frame
                if (bestFrame == TF) compVec_[i].fdsFrame_=  bestFrame;
            }
        }   

        outputDebug(TF); 
    }
    
    //debug prints- Leaving these in until ASAP + ALAP verified together. Doesn't work well after adding time frame loop
    //debugPrints();

    return;
}


/*we need these things: 
-comp type
-which index of the resourceVec_ to use
-which predecessors
-which successors
*/
int pschedule::calculateForces(int TF, int n)
{
    int bestFrame, bestFrameIdx;
    std::vector<double> totalForces;

    //std::cout << "calcForce: asap, alap = " << compVec_[n].asapFrame_ << ", " << compVec_[n].alapFrame_ << std::endl;

    for (int frame=compVec_[n].asapFrame_; frame <= compVec_[n].alapFrame_; frame++ )
    {
        //Reset forces
        forces_.clear();

        //calculate self force for one time frame
        calcSelfForce(frame, n);

        //Call Recursive function through predecessors/sucessors, calculate force and return
        for( int i = 0; i < compVec_[n].parent_.size(); i++ )
        {
            //calcPredecessorForces( frame, compVec_[n].parent_[i] );
        }
        for( int i = 0; i < compVec_[n].child_.size(); i++ )
        {
            //Check for implicitly scheduled successors
            int child = compVec_[n].child_[i];
            if (compVec_[child].asapFrame_ == frame + 1)
            {
                calcSuccessorForces( frame + 1, child );
            }
        }

        //Store off total force
        totalForces.push_back( std::accumulate(forces_.begin(), forces_.end(), 0.0) );
    }

    if (totalForces.size() > 1)
    {
        bestFrameIdx = min_element(totalForces.begin(), totalForces.end()) - totalForces.begin();
    }
    else
    {
        bestFrameIdx = 0;
    }

    bestFrame = compVec_[n].asapFrame_ + bestFrameIdx;

    return bestFrame;
}

void pschedule::calcPredecessorForces(int frame, int n)
{
    //if component doesn't have to move, set force to zero
    // calc self force
    calcSelfForce(frame, n);

    // recurse
    for( int i = 0; i < compVec_[n].parent_.size(); i++ )
    {
        calcPredecessorForces( frame, compVec_[n].parent_[i] );
    }
}


void pschedule::calcSuccessorForces(int frame, int n)
{

    // calc self force
    calcSelfForce(frame, n);

    // recurse
    for( int i = 0; i < compVec_[n].child_.size(); i++ )
    {
        //Check for implicitly scheduled successors
        int child = compVec_[n].child_[i];
        if (compVec_[child].asapFrame_ == frame + 1)
        {
            calcSuccessorForces( frame + 1, child );
        }
    }
}


void pschedule::calcSelfForce(int frame, int n)
{
    double oldcon, newcon, weight, force;
    force = 0.0;
    newcon = 0.0;
    oldcon = 0.0;

    //find old contributions
    oldcon = 1 / static_cast<double>(compVec_[n].alapFrame_ - compVec_[n].asapFrame_ + 1);

    for  (int i=compVec_[n].asapFrame_; i <= compVec_[n].alapFrame_ ; i++)
    {
        //find weight of operation distribution at current frame
        switch (compVec_[n].restype_)
        {
            case resource::ADD_SUB:
            {
                weight = addProbs_[i - 1];
                break;
            }
            case resource::MULT:
            {
                weight = multProbs_[i - 1];
                break;
            }
            case resource::LOGIC:
            {
                weight = logicProbs_[i - 1];
                break;
            }
            case resource::DIV_MOD:
            {
                weight = divProbs_[i - 1];
                break;
            }
        }

        // new contribution value to time frame distribution is 1.0 for current frame of interest
        newcon = i == frame ? 1.0 : 0.0;

        force += weight * (newcon - oldcon);
        //std::cout.precision( 3 ); //float/double precision for couts

        //std::cout << "? frame, Frame, ASAP, ALAP, weight, newcon, oldcon, force = " << i << ", " << frame << ", " << compVec_[n].asapFrame_ << ", " << compVec_[n].alapFrame_ << ", " << weight << ", " << newcon << ", " << oldcon << ", " << force << std::endl;
    }

    //build vector of individual forces to sum later
    forces_.push_back( force );

    //std::cout.precision( 3 ); //float/double precision for couts
    //std::cout << "Frame " << frame << ": Force calculated as " << force << std::endl;

    return;

}


// -------------------------------------------------------------------------------
// Create the operation probabilities table and the resource distributions vector
// -------------------------------------------------------------------------------
void pschedule::buildFDSTable(std::vector<double>& FDSTable, std::vector<double>& probVec, std::vector<int> nodeVec){

    FDSTable.clear(); probVec.clear();

    double prob = 0.0;

    //std::cout.precision( 3 ); //float/double precision for couts

    //Determine operator probabilities for each node
    for (int nodeidx = 0; nodeidx < nodeVec.size(); nodeidx++)
    {
        //ASAP = ALAP -> 1.0 probability
        if ( (compVec_[nodeVec[nodeidx]].alapFrame_ - compVec_[nodeVec[nodeidx]].asapFrame_) == 0)
        {
            prob = 1.0;
            //std::cout << "Printing prob = 1.0 for comp" << nodeVec[nodeidx] << std::endl;
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

    //std::cout << "Printing probs. FDSTable size = " << FDSTable.size() <<  ", NumProbs = " << probVec.size() << ", NodeVec size = " << nodeVec.size() << std::endl;
/*
    for (int i = 0; i < probVec.size(); i ++)
    {
        std::cout << probVec[i] << ", ";
    }
    std::cout << std::endl;
*/
    return;
}

//--------------------------------------------------------------------------------
//Handle adding the if statement parents
//--------------------------------------
int pschedule::findConditionParent(std::string condition, int compNum)
{
    for( int i = compNum - 1; i >= 0; i--)
    {
        if( compVec_[i].out_.size() > 0 && compVec_[i].out_[0] == condition )
        {
            return i;
        }
    }
    std::cout << "Couldn't find the parent of the condition: " << condition << " with comp num " << compNum << std::endl; 
    return -1;
}

void pschedule::what_if_branch()
{
    int if_node = -1;
    for(int i=0;i<compVec_.size();i++)
    {
        if(compVec_[i].withinIf_>=0)
        {
            if_node = i;
            std::string condition = ifStatements_[compVec_[i].withinIf_].condition;

            if( ifStatements_[compVec_[i].withinIf_].isElse )
            {
                condition = ifStatements_[ifStatements_[compVec_[i].withinIf_].correspondingIfElse].condition;
            }

            int parentNode = findConditionParent(condition, if_node);
            if( parentNode >= 0 )
            {
                compVec_[i].parent_.push_back(parentNode);
                compVec_[parentNode].child_.push_back(i);
            }
            /*for (int j = if_node+1; j<compVec_.size(); j++)
            {
                if( compVec_[j].withinIf_ < compVec_[if_node].withinIf_ )
                {
                    compVec_[j].parent_.push_back(compVec_[if_node].compNum_);
                }
            }*/
        }
    }
}   
// -------------------------------------------------------------------------------
// This was moved from fileparser
// -------------------------------------------------------------------------------
void pschedule::outputDebug(int TF)
{
    std::string outfile="./debug_out" + std::to_string(TF) + ".txt";
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


void pschedule::debugPrints()
{

    for (int nodeidx = 0; nodeidx < addVec_.size(); nodeidx++)
    {
        std::cout << "add printing new row= " << nodeidx << ": ";
        for (int j = 0; j < latconstrnt_; j++)
        {
            std::cout << std::fixed << addTable_[nodeidx * latconstrnt_ + j] << "  ";
        }
        std::cout << std::endl;
    }
    for (int nodeidx = 0; nodeidx < multVec_.size(); nodeidx++)
    {
        std::cout << "mult printing new row= " << nodeidx << ": ";
        for (int j = 0; j < latconstrnt_; j++)
        {
            std::cout << std::fixed << multTable_[nodeidx * latconstrnt_ + j] << "  ";
        }
        std::cout << std::endl;
    }
    for (int nodeidx = 0; nodeidx < logicVec_.size(); nodeidx++)
    {
        std::cout << "logic printing new row= " << nodeidx << ": ";
        for (int j = 0; j < latconstrnt_; j++)
        {
            std::cout << std::fixed << logicTable_[nodeidx * latconstrnt_ + j] << "  ";
        }
        std::cout << std::endl;
    }
    for (int nodeidx = 0; nodeidx < divVec_.size(); nodeidx++)
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
    std::cout << "div printing probs. numProbs = " << divProbs_.size() << std::endl;
    for (int nodeidx = 0; nodeidx < divProbs_.size(); nodeidx++)
    {
            std::cout << std::fixed << divProbs_[nodeidx] << "  ";
    }
    std::cout << std::endl;

}