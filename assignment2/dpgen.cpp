#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
    std::string inFile  = argv[1];
    std::string outFile = argv[2];
    std::string line;

    std::ifstream fin;
    std::ofstream fout;

    fin.open(inFile);
    fout.open(outFile);
    
    if ( !fin.is_open() )
    {
        std::cout << "Unable to read file: " << inFile << "\n";
        return 1;
    }
    else if ( !fout.is_open() )
    {
        std::cout << "Unable to read file: " << outFile << "\n";
        return 1;
    }
    else
    {
        std::cout << inFile << " going to " << outFile << "\n";
    }

    while( getline(fin, line) )
    {
        std::cout << line << "\n";
        // Strip out comments

        // Hardcode the different key words or characters
        
    }

    return 0;
}