#include "pschedule.h"
#include "fileparser.h"
#include "latencycalculator.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

pschedule::pschedule(std::vector<component>& compVec){
    DFS(compVec);
}
class Node{
    public:
        Node();
        int time=1;
        int vertexNum;
        std::vector<int> parents, children;
        component comp;
        void find_path(int, int);
};

void Node::find_path(int meh1, int meh2){
}


void pschedule::DFS(std::vector<component> compVec){
    std::vector<component> clean_complist;
    std::vector<Node> pathMap;
    for (int i=0;i<compVec.size();i++){
        if(compVec[i].type_>=comp_type::REG){
            clean_complist.push_back(compVec[i]);
        }        
    }
    for (int i=0;i<clean_complist.size();i++){
        Node vertex;
        vertex.vertexNum=i;
        vertex.comp=clean_complist[i];
        pathMap.push_back(vertex);
        
        //Saving this for later. Might need to fill the inputs and outputs but these are not the parents
        //the parents and children will be the vertexes 
        // for(int j;j<clean_complist[i].in_.size();j++){
        //     vertex.parents.push_back(clean_complist[i].in_[j].name_);
        // }
        // for(int j;j<clean_complist[i].out_.size();j++){
        //     vertex.children.push_back(clean_complist[i].out_[j].name_);
        // }
    }
    std::string vedges = {};
    for (int i;i<pathMap.size();i++){
        for(int z;z<pathMap.size();z++){
            for(int j;j<pathMap[i].comp.out_.size();j++){
                for (int k; k<pathMap[i].comp.in_.size();k++){
                    if(pathMap[i].comp.in_.empty()){
                        pathMap[i].parents.push_back(0);
                    }
                    else if(pathMap[i].comp.out_[j]==pathMap[z].comp.in_[k]){
                        pathMap[i].children.push_back(pathMap[z].vertexNum);
                        pathMap[z].parents.push_back(pathMap[i].vertexNum);
                    }
                    else{
                        pathMap[i].children.push_back(0);
                    }
                }
            }
        }
    }
}