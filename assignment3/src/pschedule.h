#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class pschedule{
public:
    pschedule(std::vector<component>& compVec);
    void DFS(std::vector<component> compVec);
};

