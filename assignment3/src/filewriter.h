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
    std::vector<ifStatement> ifStatements_;
    int latConstraint_;

    void createStateVector();
    void writeIf(int ifNum, int compNum = -1);

public:
    filewriter(std::string outfile, int latConstraint, std::vector<component> compVec, std::vector<ifStatement> ifStatements);
    void writeFile();
    bool error_;

};

#endif