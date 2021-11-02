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

bool fileparser::containsVariable(std::string var)
{
    for( int i=0; i < varVec_.size(); i++ )
    {
        if (varVec_[i] == var)
        {
            return true;
        }
    }
    return false;
}

bool fileparser::containsVariable(variable& var)
{
    for( int i=0; i < varVec_.size(); i++ )
    {
        if (varVec_[i] == var)
        {
            return true;
        }
    }
    return false;
}

bool fileparser::run()
{
    
    std::string line;

    while( getline(fin_, line) )
    {
        parseLine(line);

        if (error_) break;
    }
    
    if (!error_)
    {
        writeFile();
    }

    return error_;
}

void fileparser::parseLine(std::string line)
{
    // Remove comments
    line = line.substr(0, line.find("//"));



    // Search keywords/chars and send to proper handler
    if( line.find("input") != std::string::npos )
    {
        // Input
    }
    else if( line.find("output") != std::string::npos )
    {
        // Output
    }
    else if( line.find("wire") != std::string::npos )
    {
        // Wire
    }
    else if( line.find("register") != std::string::npos )
    {
        // Register
    }
    else if( line.find(">>") != std::string::npos )
    {
        // Shift Right
    }
    else if( line.find("<<") != std::string::npos )
    {
        // Shift Left
    }
    else if( line.find(">") != std::string::npos 
             || line.find("<") != std::string::npos 
             || line.find("==") != std::string::npos ) //or > or <
    {
        // Comparator
        
        //for (int i=0; i<in_.size(); i++)
        //{
        //    largestinput = (in_[i].size_ > largestinput) ? i : largestinput;
        //}

        //largestsize = in_[largestinput].size_;
    }
    else if( line.find("+") != std::string::npos )
    {
        // Add/Increment
    }
    else if( line.find("-") != std::string::npos )
    {
        // Subtract/Decrement
    }
    else if( line.find("*") != std::string::npos )
    {
        // Multiply
    }
    else if( line.find("/") != std::string::npos )
    {
        // Divide
    }
    else if( line.find("%") != std::string::npos )
    {
        // Modulo
    }
    else if( line.find("?") != std::string::npos )
    {
        // Mux
    }
    else if( line.find("=") != std::string::npos )
    {
        // Register
    }
}









void fileparser::writeFile()
{
    for (int i=0; i<compVec_.size(); i++)
    {
        fout_ << compVec_[i].writeLine();
    }
}