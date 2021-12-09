//This is a test file

#include <string>
#include <vector>

#include "component.h"
#include "fileparser.h"
#include "filewriter.h"
#include "common.h"
#include "variable.h"
#include "pschedule.h"


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

    std::cout << "Converting " << infile << " to " << outfile << " with latency constraint " << latStr << "..." << std::endl;

    int latConstraint   = std::stoi(latStr);

    if ( latConstraint <= 0 )
    {
        std::cout << "Encountered error converting " << infile << " to " << outfile << ": Latency constraint is zero or negative" << std:: endl;
        return 1;
    }

    fileparser fp(infile, outfile);
    

    bool error = fp.run();

    if (error)
    {
        std::cout << "Encountered error converting " << infile << " to " << outfile << std:: endl;
        return 1;
    }

    pschedule pscheduler(latConstraint);
    error = pscheduler.performScheduling(fp.compVec_, fp.ifStatements_);

    if (error)
    {
        std::cout << "Encountered error converting " << infile << " to " << outfile << ": ASAP > ALAP" << std:: endl;
        return 1;
    }

    filewriter fw(outfile, latConstraint, pscheduler.compVec_, fp.ifStatements_);

    fw.writeFile();

    if ( fw.error_ )
    {
        std::cout << "Encountered error converting " << infile << " to " << outfile << std:: endl;
        return 1;
    }
    std::cout << std::endl << outfile << " Verilog file successfully created!" << std::endl << std::endl;

    return 0;
}
