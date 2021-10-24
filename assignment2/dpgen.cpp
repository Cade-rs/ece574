#include <iostream>
#include <fstream>

#include "fileparser.h"

int main2(int argc, char *argv[])
{
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

