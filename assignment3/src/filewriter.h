#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <fstream>
#include <string>
#include <vector>

#include "component.h"
#include "common.h"
#include "variable.h"


class filewriter {
private:
    std::string outfile_;
    std::ofstream fout_;
    std::vector<component> compVec_;
    std::vector<std::vector<int>> states_;
    bool error_;

    void writeIf(int ifNum);

public:
    filewriter(std::string outfile, std::vector<component> compVec, std::vector<std::vector<int>> states);
    void writeFile();

};

#endif