#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <fstream>
#include <string>
#include <vector>

#include "component.h"
#include "latency.h"
#include "variable.h"


class fileparser {
private:

    bool containsVariable(string var);
    void parseLine(std::string line);

    std::ifstream fin_;
    std::ofstream fout_;

    bool error_;

public:
    fileparser(std::string infile, std::string outfile);
    bool run();

    std::vector<component> compVec_;
    std::vector<variable>  varVec_;

};


#endif