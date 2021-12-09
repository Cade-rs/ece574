//This is a test file

#include <string>
#include <vector>

#include "component.h"
#include "fileparser.h"
#include "filewriter.h"
#include "common.h"
#include "variable.h"
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

    pschedule pscheduler(latConstraint);
    error = pscheduler.performScheduling(fp.compVec_);

    if (error)
    {
        std::cout << "Encountered error: Latency constraint insufficient" << std:: endl;
        return 1;
    }

    std::vector<std::vector<int>> testStates;

    fillStates(testStates);

    filewriter fw(outfile, latConstraint, pscheduler.compVec_, fp.ifStatements_);

    fw.writeFile();

    std::cout << std::endl << std::endl << outfile << " Verilog file successfully created" << std::endl;

    return 0;
}
