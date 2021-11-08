#include "latencycalculator.h"

#include <algorithm>
#include <string>
#include <vector>

#include "component.h"
#include "fileparser.h"
#include "common.h"

latencycalculator::latencycalculator(std::vector<component>& compVec){

    criticalpath_ = 0.00;
    delays_.push_back( -1.0 );

    //Test benches for debugging purposes
    //std::vector<component> compVec {examplecomps1()};
    //std::vector<component> complist {examplecomps4()};
    //sumPathLatencies(complist);

    //Find latencies for each path
    sumPathLatencies(compVec);

    //determine and report critical path
    criticalpath_ = *max_element(delays_.begin(), delays_.end());

    std::cout << "Critical path : " << std::to_string(criticalpath_) << " ns" << std::endl;
}


/*
The idea of the critical path calculation is to loop through each component, defining a path as the mapping of each component's output to another component's input. Whenever we come to a split( one component maps to multiple other components), there is a branch-off. We use recursion to fully map out a path before returning to the split to pursue the next path
*/
void latencycalculator::sumPathLatencies(std::vector<component> complist){

    int branch = 0;
    std::vector<component> redComplist;

    //reduce list to only component nodes (no I/O)
    for(int i=0; i < complist.size(); i++)
    {   
        if( complist[i].type_ >= comp_type::REG)
        {
            redComplist.push_back( complist[i]);
        }
    }

    //loop through each component
    for(int i=0; i < redComplist.size(); i++)
    {   

        recursivesearch(redComplist, i, branch);

        //for each new component (unless finished), declare new branch. zero-based so set new branch to one less than size. Negative number was for debugging purposes
        if( i < redComplist.size() -1 )
        {
            delays_.push_back( -1.0 );
            branch = delays_.size()-1;
        }

    }

    //Temporary cout for displaying all paths to provide confidence in calculation as we continue
    /*
    for(int i=0; i<delays_.size(); i++)
    {
        std::cout << "Path" << i << ": " << std::to_string(delays_[i]) << std::endl;
    }
    */
}

void latencycalculator::recursivesearch(std::vector<component> complist, int compnum, int branch){
    double currentlat;
    vector<int> matches;    

    //Update branch number if necessary (OBE: this was primarily for debugging)
    if (delays_.back() <= 0.0)
    {
        delays_[branch] = 0.0;
    }

    //add component delay and store off for recursive purposes later
    delays_[branch] += complist[compnum].lat_;
    currentlat = delays_[branch];

    //Find components that uses output as input?
    for(int i=0; i<complist.size(); i++)
    {
        //loop through outputs
        for(int outnum=0; outnum < complist[compnum].out_.size(); outnum++)
        {    
            if( complist[i].containsInput(complist[compnum].out_[outnum].name_) )
            {
                matches.push_back( i );

                //exit output loop to avoid double counting component that uses two or more of the source nodes outputs
                break;
            }
        }
    }

    //is matches empty? If so, done with path
    if( matches.size() == 0)
    {
        return;
    }

    //Recurse!
    for (int branchiter = 0; branchiter < matches.size(); branchiter++)
    {
        //if more than one path available, need to branch off but retain previous latency
        if( branchiter > 0)
        {
            //copy current branchs delay and update branch number
            delays_.push_back( currentlat );
            branch = delays_.size()-1;
        }

        recursivesearch(complist, matches[branchiter], branch);
    }

    return;
}


//build test vector of components for building latency calculator using
// 474_circuit1.txt
std::vector<component> latencycalculator::examplecomps1(){

    //Define in and out. Use vector::clear to clear and reset vector size and content.
    // --Although, memory reallocation isn't guarunteed
    std::vector<variable> in, out;
    std::vector<component> complist;


    //d = a + b
    in.push_back (variable("a", 8));
    in.push_back (variable("b", 8));
    out.push_back (variable("d", 8));
    component temp1(comp_type::ADD,comp_size::EIGHT,in,out);
    complist.push_back(temp1);

    //e = a + c
    in.clear(); out.clear();
    in.push_back (variable("a", 8));
    in.push_back (variable("c", 8));
    out.push_back (variable("e", 8));
    component temp2(comp_type::ADD,comp_size::EIGHT,in,out);
    complist.push_back(temp2);

    //NOTE: STRANGE THAT G IS 16b
    //g = d > e
    in.clear(); out.clear();
    in.push_back (variable("d", 8));
    in.push_back (variable("e", 8));
    out.push_back (variable("g", 16));
    component temp3(comp_type::COMP,comp_size::EIGHT,in,out);
    complist.push_back(temp3);

    //z = g ? d : e
    in.clear(); out.clear();
    in.push_back (variable("d", 8));
    in.push_back (variable("e", 8));
    in.push_back (variable("g", 16));
    out.push_back (variable("z", 8));
    component temp4(comp_type::MUX,comp_size::EIGHT,in,out);
    complist.push_back(temp4);

    //f = a * c
    in.clear(); out.clear();
    in.push_back (variable("a", 8));
    in.push_back (variable("c", 8));
    out.push_back (variable("f", 16));
    component temp5(comp_type::MUL,comp_size::SIXTEEN,in,out);
    complist.push_back(temp5);

    //xwire = f - d
    in.clear(); out.clear();
    in.push_back (variable("f", 16));
    in.push_back (variable("d", 8));
    out.push_back (variable("xwire", 16));
    component temp6(comp_type::SUB,comp_size::SIXTEEN,in,out);
    complist.push_back(temp6);

    //x = xwire
    in.clear(); out.clear();
    in.push_back (variable("xwire", 16));
    out.push_back (variable("x", 16));
    component temp7(comp_type::REG,comp_size::SIXTEEN,in,out);
    complist.push_back(temp7);

    //example accessing vector info
    //std::cout << complist[0].type_ << std::endl;
    //std::cout << complist[0].in_[0].name_ << std::endl;
    //std::cout << complist[4].in_[1].name_ << std::endl;
    //std::cout << in[0].name_ << std::endl;
    //std::cout << complist.size() << std::endl;  //probably needs std::to_string()
    //std::cout << complist[4].lat_ << std::endl; //probably needs std::to_string()

    return complist;
}

//build test vector of components for building latency calculator using
// 474_circuit4.txt
std::vector<component> latencycalculator::examplecomps4(){

    //Define in and out. Use vector::clear to clear and reset vector size and content.
    // --Although, memory reallocation isn't guarunteed
    std::vector<variable> in, out;
    std::vector<component> complist;


    //d = a + b
    in.push_back (variable("a", 64));
    in.push_back (variable("b", 64));
    out.push_back (variable("d", 64));
    component temp1(comp_type::ADD,comp_size::SIXTYFOUR,in,out);
    complist.push_back(temp1);

    //e = a + c
    in.clear(); out.clear();
    in.push_back (variable("a", 64));
    in.push_back (variable("c", 64));
    out.push_back (variable("e", 64));
    component temp2(comp_type::ADD,comp_size::SIXTYFOUR,in,out);
    complist.push_back(temp2);

    //f = a - c
    in.clear(); out.clear();
    in.push_back (variable("a", 64));
    in.push_back (variable("b", 64));
    out.push_back (variable("f", 64));
    component temp3(comp_type::SUB,comp_size::SIXTYFOUR,in,out);
    complist.push_back(temp3);

    //NOTE: STRANGE THAT G IS 16b
    //dEQe = d == e
    in.clear(); out.clear();
    in.push_back (variable("d", 64));
    in.push_back (variable("e", 64));
    out.push_back (variable("dEQe", 1));
    component temp4(comp_type::COMP,comp_size::SIXTYFOUR,in,out);
    complist.push_back(temp4);

    //dLTe = d < e
    in.clear(); out.clear();
    in.push_back (variable("d", 64));
    in.push_back (variable("e", 64));
    out.push_back (variable("dLTe", 1));
    component temp5(comp_type::COMP,comp_size::SIXTYFOUR,in,out);
    complist.push_back(temp5);

    //g = dLTe ? d : e
    in.clear(); out.clear();
    in.push_back (variable("d", 64));
    in.push_back (variable("e", 64));
    out.push_back (variable("g", 64));
    component temp6(comp_type::COMP,comp_size::SIXTYFOUR,in,out);
    complist.push_back(temp6);

    //h = dEQe ? g : f
    in.clear(); out.clear();
    in.push_back (variable("g", 64));
    in.push_back (variable("f", 64));
    out.push_back (variable("h", 64));
    component temp7(comp_type::COMP,comp_size::SIXTYFOUR,in,out);
    complist.push_back(temp7);

    //greg = g
    in.clear(); out.clear();
    in.push_back (variable("g", 64));
    out.push_back (variable("greg", 64));
    component temp8(comp_type::REG,comp_size::SIXTYFOUR,in,out);
    complist.push_back(temp8);

    //hreg = h
    in.clear(); out.clear();
    in.push_back (variable("h", 64));
    out.push_back (variable("hreg", 64));
    component temp9(comp_type::REG,comp_size::SIXTYFOUR,in,out);
    complist.push_back(temp9);

    //xrin = hreg << dLTe
    in.clear(); out.clear();
    in.push_back (variable("hreg", 64));
    in.push_back (variable("dLTe", 64));
    out.push_back (variable("xrin", 64));
    component temp10(comp_type::SHL,comp_size::SIXTYFOUR,in,out);
    complist.push_back(temp10);

    //zrin = greg << dEQe
    in.clear(); out.clear();
    in.push_back (variable("ghreg", 64));
    in.push_back (variable("dEQe", 64));
    out.push_back (variable("zrin", 64));
    component temp11(comp_type::SHR,comp_size::SIXTYFOUR,in,out);
    complist.push_back(temp11);

    //x = xrin
    in.clear(); out.clear();
    in.push_back (variable("xrin", 64));
    out.push_back (variable("x", 32));
    component temp12(comp_type::REG,comp_size::THIRTYTWO,in,out);
    complist.push_back(temp12);

    //z = zrin
    in.clear(); out.clear();
    in.push_back (variable("zrin", 64));
    out.push_back (variable("z", 32));
    component temp13(comp_type::REG,comp_size::THIRTYTWO,in,out);
    complist.push_back(temp13);

    //example accessing vector info
    //std::cout << complist[0].type_ << std::endl;
    //std::cout << complist[0].in_[0].name_ << std::endl;
    //std::cout << complist[4].in_[1].name_ << std::endl;
    //std::cout << in[0].name_ << std::endl;
    //std::cout << complist.size() << std::endl;  //probably needs std::to_string()
    //std::cout << complist[4].lat_ << std::endl; //probably needs std::to_string()

    return complist;
}