#include "latencycalculator.h"

#include <algorithm>
#include <string>
#include <vector>

#include "component.h"
#include "latency.h"

latencycalculator::latencycalculator(){
    
    criticalpath_ = 0.00;
    delays_.push_back( 0.0 );

    std::vector<component> complist {examplecomps()};
    sumPathLatencies(complist);
}

void latencycalculator::sumPathLatencies(std::vector<component> complist){

    int branch = 0;

    //loop through each component
    for(int i=0; i < complist.size(); i++)
    {   
        recursivesearch(complist, i, branch);
    }

    //determine critical path
    criticalpath_ = *max_element(delays_.begin(), delays_.end());
    
    
    /////////// DEBUGGING ///////////

    std::cout << "The critical path is " << std::to_string(criticalpath_) << std::endl;

    for (int i = 0; i < delays_.size(); i++)
    {
        std::cout << "delay = " << std::to_string(delays_[i]) << std::endl;
    }

}

void latencycalculator::recursivesearch(std::vector<component> complist, int compnum, int branch){
    
    vector<int> matches;    

    //add component delay
    delays_[branch] += complist[compnum].lat_;
    
    std::cout << std::to_string(complist[compnum].lat_) << std::endl;

    //Find components that uses output as input?
    for(int i=0; i<complist.size(); i++)
    {
        for(int outnum=0; outnum < complist[compnum].out_.size(); outnum++)
        {    
            if( complist[i].containsInput(complist[compnum].out_[outnum].name_) )
            {
                //TODO: add check for multiple outputs used at same component -- don't double count
                
                matches.push_back( i );
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
            std::cout << "got here 20" << std::endl;

        //new branch
        if( branchiter > 0)
        {
            //copy current branchs delay and update branch number
            delays_.push_back( delays_[branch] );
            branch = delays_.size();
        }

        recursivesearch(complist, matches[branchiter], branch);
        std::cout << "got here 30" << std::endl;
    }

}


//build test vector of components for building latency calculator using
// 474_circuit1.txt
std::vector<component> latencycalculator::examplecomps(){

    //Define in, out and use vector::clear to clear and reset vector size. Although,
    // memory reallocation isn't guarunteed
    std::vector<variable> in, out;
    std::vector<component> complist;


    //d = a + b
    in.push_back (variable("a", 8));
    in.push_back (variable("b", 8));
    out.push_back (variable("d", 8));
    component temp1(comp_type::ADD,comp_size::EIGHT,in,out);
    complist.push_back(temp1);

    //example accessing vector info
    //std::cout << complist[0].type_ << std::endl;
    //std::cout << complist[0].in_[0].name_ << std::endl;
    
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
    component temp3(comp_type::COMP,comp_size::SIXTEEN,in,out);
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
    in.push_back (variable("f", 8));
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

    //std::cout << complist[4].in_[1].name_ << std::endl << std::endl;
    //std::cout << in[0].name_ << std::endl;
    //std::cout << complist.size() << std::endl;
    //std::cout << complist[4].findLatency() << std::endl;

    return complist;
}

