#include <iostream>
#include <fstream>

void handleLines(std::string line);

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

    bool inBlockComment = 0;

    while( getline(fin, line) )
    {
        // Strip comments
        handleLines(line);

    }

    return 0;
}

void handleLines(std::string line)
{
    // Search keywords/chars and send to proper handler
    if( line.rfind("//") == 0)
    {
        return;
    }
    else if( line.find("input") != std::string::npos )
    {
        //Handle inputs
    }
    else if( line.find("output") != std::string::npos )
    {
        //Handle outputs
    }
    else if( line.find("wire") != std::string::npos )
    {
        //Handle wire
    }
    else if( line.find("+") != std::string::npos )
    {
        //Handle add/increment
    }



}