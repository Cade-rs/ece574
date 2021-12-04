//This is a test file

#include <string>
#include <vector>

#include "component.h"
#include "fileparser.h"
#include "filewriter.h"
#include "common.h"
#include "variable.h"
#include "latencycalculator.h"
#include "pschedule.h"


void fillStates(std::vector<std::vector<int>>& states);

int main(int argc, char *argv[])
{
    if( (argc-1) != 3 ) // First input is exe name, handle that
    {
        std::cout << "ERROR: Expecting 3 inputs, received " << (argc-1) << ". Exiting..." << std::endl;
        return 1;
    }

    std::string infile  = argv[1];
    std::string latStr  = argv[2];
    std::string outfile = argv[3];

    int latConstraint   = std::stoi(latStr);

    fileparser fp(infile, outfile);
    

    bool error = fp.run();

    if (error)
    {
        std::cout << "Encountered error" << std:: endl;
        return 1;
    }

    // critical path calculations (and test component list)
    //latencycalculator lc(fp.compVec_);

    pschedule pscheduler(latConstraint);
    pscheduler.performScheduling(fp.compVec_);

    std::vector<std::vector<int>> testStates;

    fillStates(testStates);

    filewriter fw(outfile, pscheduler.compVec_, testStates, fp.ifStatements_);

    fw.writeFile();

    std::cout << std::endl << std::endl << outfile << " Verilog file successfully created" << std::endl;

    return 0;
}


void fillStates(std::vector<std::vector<int>>& states)
{
    std::vector<int> state1;
    state1.push_back(4);
    state1.push_back(5);
    state1.push_back(6);
    state1.push_back(7);

    std::vector<int> state2;
    state2.push_back(8);
    state2.push_back(9);
    state2.push_back(10);

    std::vector<int> state3;
    state3.push_back(10);
    state3.push_back(11);
    state3.push_back(12);
    state3.push_back(13);
    state3.push_back(14);
    state3.push_back(15);

    states.push_back(state1);
    states.push_back(state2);
    states.push_back(state3);

}