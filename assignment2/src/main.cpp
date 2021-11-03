//This is a test file

#include <string>
#include <vector>

#include "component.h"
#include "fileparser.h"
#include "latency.h"
#include "variable.h"
#include "latencycalculator.h"

int main(int argc, char *argv[])
{
    // You can run this by changing the name from main2 to main
    // then using the following command from the build folder:
    // ./pleaseWork.exe ../assignment_2_circuits/474a_circuit1.txt ../testfile.txt
    
    if( (argc-1) != 2 ) // First input is exe name, handle that
    {
        std::cout << "ERROR: Expecting 2 inputs, received " << (argc-1) << ". Exiting..." << std::endl;
        return 1;
    }

    std::string infile  = argv[1];
    std::string outfile = argv[2];
    
    fileparser fp(infile, outfile);

    bool error = fp.run();

    if (error)
    {
        std::cout << "Encountered error";
        return 1;
    }

    // critical path calculations (and test component list)
    latencycalculator lc(fp.compVec_);

    return 0;
}