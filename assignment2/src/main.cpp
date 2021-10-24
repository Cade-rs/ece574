//This is a test file

#include <string>
#include <vector>

#include "component.h"
#include "fileparser.h"
#include "latency.h"
#include "variable.h"

int main2(void){
    std::vector<variable> in, out;
    in.push_back (variable("alpha", 1));
    in.push_back (variable("bravo", 2));
    out.push_back(variable("charlie", 8));
    out.push_back(variable("delta", 32));
    out.push_back(variable("echo", 64));

    component comp1(comp_type::MUL,comp_size::TWO,in,out);

    return 0;
}

int main(int argc, char *argv[])
{
    // You can run this by changing the name from main2 to main
    // then using the following command from the build folder:
    // ./pleaseWork.exe ../assignment_2_circuits/474a_circuit1.txt ../testfile.txt

    std::string infile  = argv[1];
    std::string outfile = argv[2];
    
    fileparser fp(infile, outfile);

    bool error = fp.run();

    if (error)
    {
        std::cout << "Encountered error";
        return 1;
    }

    return 0;
}