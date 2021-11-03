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
    void parseLine(std::string& line);
    void writeFile();

    void constructInputs(std::string& line);
    void constructOutputs(std::string& line);
    void constructWires(std::string& line);
    void constructRegisters(std::string& line);
    void constructShift(std::string& line);
    void constructCOMP(std::string& line);
    void constructADDorSUB(std::string& line);
    void constructMUL(std::string& line);
    void constructDIV(std::string& line);
    void constructMOD(std::string& line);
    void constructMUX(std::string& line);
    void constructREG(std::string& line);
    
    // Helpers
    std::vector<std::string> stringSplit(std::string line, std::string re = "\\s+");
    comp_size findSize(std::string var);
    bool finalizeComponent(comp_type type, comp_size datawidth, 
              vector<variable> in, vector<variable> out, bool isSigned, int outputPos = 0);
    int findVariableIndex(std::string& varName);
    bool checkCompForSignedVariable(std::vector<variable>& varVec);
    std::vector<variable> buildVarVec(std::vector<std::string>& inputLine);

    // I don't know what needs to go into these yet
    void handleRegOutput(); 

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