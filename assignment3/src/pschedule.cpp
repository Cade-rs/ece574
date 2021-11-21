#include "pschedule.h"
#include "fileparser.h"
#include "latencycalculator.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

pschedule::pschedule(std::vector<component>& compVec){
    std::vector<component> cV=compVec;
    
}

void pschedule::asap(std::vector<component> cV){
    std::vector<component> ccV;
    for(int i=0; i < cV.size(); i++){   
        if( cV[i].type_ >= comp_type::REG){
            ccV.push_back( cV[i]);
        }
    }

    //Find components that uses output as input?
    for(int i=0; i<cV.size(); i++){
        //loop through outputs
        for(int outnum=0; outnum < cV[compnum].out_.size(); outnum++){    
            if( complist[i].containsInput(complist[compnum].out_[outnum].name_) ){
                matches.push_back( i );

                //exit output loop to avoid double counting component that uses two or more of the source nodes outputs
                break;
            }
        }
    }
}





