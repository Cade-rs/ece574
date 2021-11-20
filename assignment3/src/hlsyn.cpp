//This is a test file

#include <string>
#include <vector>

#include "component.h"
#include "fileparser.h"
#include "filewriter.h"
#include "common.h"
#include "variable.h"
#include "latencycalculator.h"


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
    latencycalculator lc(fp.compVec_);

    filewriter fw(outfile, fp.compVec_);

    fw.writeFile();

    std::cout << std::endl << std::endl << outfile << " Verilog file successfully created" << std::endl;

    return 0;
}