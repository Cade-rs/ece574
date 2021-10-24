#include "fileparser.h"

#include <iostream>
#include <string>


fileparser::fileparser(std::string infile, std::string outfile)
{
    error_ = false;

    fin_.open(infile);
    fout_.open(outfile);
    
    if ( !fin_.is_open() )
    {
        std::cout << "Unable to read file: " << infile << "\n";
        error_ =  true;
    }
    else if ( !fout_.is_open() )
    {
        std::cout << "Unable to read file: " << outfile << "\n";
        error_ =  true;
    }
    else
    {
        std::cout << infile << " going to " << outfile << "\n";
    }
}

bool fileparser::run()
{
    
    std::string line;

    while( getline(fin_, line) )
    {
        parseLine(line);

        if (error_) break;
    }
    
    return error_;
}

void fileparser::parseLine(std::string line)
{
    // Remove comments
    line = line.substr(0, line.find("//"));
    std::cout << line << "\n";

    // Search keywords/chars and send to proper handler
    if( line.find("input") != std::string::npos )
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