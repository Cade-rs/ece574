#include "latencycalculator.h"

#include <string>
#include <vector>
#include <iostream> //for flush

#include "latency.h"
#include "component.h"


latencycalculator::latencycalculator(){
    
    criticalpath_ = 0.00;

    const std::vector<component> complist {examplecomps()};
    sumPathLatencies(complist);
}

void latencycalculator::sumPathLatencies(const std::vector<component> complist){

    vector<double> pathdelays;
    int pathnum = 0;
    bool pathopen = false;

    //loop through each component
    for(int i=0; i < complist.size(); i++)
    {
        //add component delay
        
        //is there another component that uses output as input?

            //yes - go to that component

            //no - break, you've found that path's delay
    }

    //determine critical path

}

//double latencycalculator::recursivesearch(){}

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

    std::cout << complist[4].in_[1].name_ << std::endl << std::endl;
    //std::cout << in[0].name_ << std::endl;
    std::cout << complist.size() << std::endl;

    return complist;
}

