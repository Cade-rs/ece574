#include "fileparser.h"

#include <iostream>
#include <regex>
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
    // TODO: Also need to handle if file is empty

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
    
    if (!error_)
    {
        writeFile();
    }

    return error_;
}

void fileparser::parseLine(std::string& line)
{
    // Remove comments
    line = line.substr(0, line.find("//"));

    // Remove leading/trailing whitespace
    line = std::regex_replace(line, std::regex("^\\s+"), std::string(""));
    line = std::regex_replace(line, std::regex("\\s+$"), std::string(""));

    // Remove commas
    line.erase(std::remove(line.begin(), line.end(), ','), line.end());

    // Search keywords/chars and send to proper handler
    if( line.rfind("input", 0) == 0 )
    {
        // Input
        constructInputs(line);
    }
    else if( line.rfind("output", 0) == 0 )
    {
        // Output
        constructOutputs(line);
    }
    else if( line.rfind("wire", 0) == 0 )
    {
        // Wire
        constructWires(line);
    }
    else if( line.rfind("register", 0) == 0 )
    {
        // Register
        constructRegisters(line);
    }
    else if( line.find(">>") != std::string::npos 
             || line.find("<<") != std::string::npos )
    {
        // Shift Right or Left
        constructShift(line);
    }
    else if( line.find(">") != std::string::npos 
             || line.find("<") != std::string::npos 
             || line.find("==") != std::string::npos ) //or > or <
    {
        // Comparator
        constructCOMP(line);
    }
    else if( line.find("+") != std::string::npos )
    {
        // Add/Increment
        constructADDorINC(line);
    }
    else if( line.find("-") != std::string::npos )
    {
        // Subtract/Decrement
        constructSUBorDEC(line);
    }
    else if( line.find("*") != std::string::npos )
    {
        // Multiply
        constructMUL(line);
    }
    else if( line.find("/") != std::string::npos )
    {
        // Divide
        constructDIV(line);
    }
    else if( line.find("%") != std::string::npos )
    {
        // Modulo
        constructMOD(line);
    }
    else if( line.find("?") != std::string::npos )
    {
        // Mux
        constructMUX(line);
    }
    else if( line.find("=") != std::string::npos )
    {
        // Register
        constructREG(line);
    }
    else if( line == "" )
    {
        std::cout << "I am empty!" << std::endl << line << std::endl;
    }
    else
    {
        std::cout << "I went nowhere!" << std::endl << line << std::endl;
    }
}

void fileparser::constructInputs(std::string& line)
{
    std::cout << "I got to Inputs!" << std::endl << line << std::endl;
    std::vector<std::string> splitLine = stringSplit(line);
    for( int i =0; i < splitLine.size(); i++ )
    {
        std::cout << splitLine[i] << std::endl;
    }

    buildVarVec(splitLine);

    return;
}

void fileparser::constructOutputs(std::string& line)
{
    std::cout << "I got to Outputs!" << std::endl << line << std::endl;
    std::vector<std::string> splitLine = stringSplit(line);
    for( int i =0; i < splitLine.size(); i++ )
    {
        std::cout << splitLine[i] << std::endl;
    }

    buildVarVec(splitLine);

    return;
}

void fileparser::constructWires(std::string& line)
{
    std::cout << "I got to Wires!" << std::endl << line << std::endl;
    std::vector<std::string> splitLine = stringSplit(line);
    for( int i =0; i < splitLine.size(); i++ )
    {
        std::cout << splitLine[i] << std::endl;
    }

    buildVarVec(splitLine);

    return;
}

void fileparser::constructRegisters(std::string& line)
{
    std::cout << "I got to Registers!" << std::endl << line << std::endl;
    std::vector<std::string> splitLine = stringSplit(line);
    for( int i =0; i < splitLine.size(); i++ )
    {
        std::cout << splitLine[i] << std::endl;
    }

    buildVarVec(splitLine);

    return;

    // The error line containing an invalid character currently goes here. 
    // Need to handle this:
    // d = a $ b
}

void fileparser::constructShift(std::string& line)
{
    // Example line:
    // out = in1 >> in2

    std::cout << "I got to Shift!" << std::endl << line << std::endl;

    std::vector<std::string> splitLine = stringSplit(line);

    if( splitLine.size() != 5)
    {
        std::cout << "ERROR: Received different number of values than expected: " << line << std::endl;
        error_ = true;
        return;
    }

    // Instantiate variables
    comp_type type;
    vector<variable> outputs;
    vector<variable> inputs;
    int varIdx = -1;
    std::string varName = "";

    // Set type
    if( splitLine[3] == ">>" )
    {
        std::cout << "I got to SHR!" << std::endl;
        type = comp_type::SHR;
    }
    else if( splitLine[3] == "<<" )
    {
        std::cout << "I got to SHL!" << std::endl;
        type = comp_type::SHL;
    }
    else
    {
        std::cout << "ERROR: Shifter operator doesn't match SHR or SHL: " << line << std::endl;
        error_ = true;
        return;
    }

    // Find output
    // Output is first token in splitLine
    varName = splitLine[0];
    varIdx = findVariableIndex(varName);
    if( varIdx >= 0 )
    {
        outputs.push_back( variable( varVec_[varIdx] ) );
        std::cout << "setting output: " << outputs[0].name_ << ", " << std::to_string(outputs[0].size_) << std::endl;
    }
    else
    {
        std::cout << "ERROR: Output variable used but not defined: " << varName << std::endl;
        std::cout << "    On line: " << line << std::endl;
        error_ = true;
        return;
    }
    
    // Find  inputs
    //  Inputs are 3rd and 5th token
    varName = splitLine[2];
    varIdx = findVariableIndex(varName);
    if( varIdx >= 0 )
    {
        inputs.push_back( variable( varVec_[varIdx] ) );
    }
    else
    {
        std::cout << "ERROR: Input variable used but not defined: " << varName << std::endl;
        std::cout << "    On line: " << line << std::endl;
        error_ = true;
        return;
    }

    varName = splitLine[4];
    varIdx = findVariableIndex(varName);
    if( varIdx >= 0 )
    {
        inputs.push_back( variable( varVec_[varIdx] ) );
    }
    else
    {
        std::cout << "ERROR: Input variable used but not defined: " << varName << std::endl;
        std::cout << "    On line: " << line << std::endl;
        error_ = true;
        return;
    }

    // Determine size
    comp_size datawidth = outputs[0].size_;

    // Call finalizeComponent to determine signed/unsigned, compNum, handle register creation
    bool didItWork = finalizeComponent(type, datawidth, inputs, outputs);
    
    return;
}

void fileparser::constructCOMP(std::string& line)
{
    std::cout << "I got to COMP!" << std::endl << line << std::endl;
    
    //for (int i=0; i<in_.size(); i++)
    //{
    //    largestinput = (in_[i].size_ > largestinput) ? i : largestinput;
    //}

    //largestsize = in_[largestinput].size_;
}

void fileparser::constructADDorINC(std::string& line)
{
    std::cout << "I got to ADDorINC!" << std::endl << line << std::endl;
}
void fileparser::constructSUBorDEC(std::string& line)
{
    std::cout << "I got to SUBorDEC!" << std::endl << line << std::endl;
}
void fileparser::constructMUL(std::string& line)
{
    std::cout << "I got to MUL!" << std::endl << line << std::endl;
}
void fileparser::constructDIV(std::string& line)
{
    std::cout << "I got to DIV!" << std::endl << line << std::endl;
}
void fileparser::constructMOD(std::string& line)
{
    std::cout << "I got to MOD!" << std::endl << line << std::endl;
}
void fileparser::constructMUX(std::string& line)
{
    std::cout << "I got to MUX!" << std::endl << line << std::endl;
}
void fileparser::constructREG(std::string& line)
{
    std::cout << "I got to REG!" << std::endl << line << std::endl;
}



// Helpers
std::vector<std::string> fileparser::stringSplit(std::string line, std::string re)
{
    std::regex delim(re);
    std::vector<std::string> result {std::sregex_token_iterator(line.begin(), line.end(), delim, -1), {} };
    return result;
}

void fileparser::buildVarVec(std::vector<std::string>& inputLine)
{
    bool isSigned = false;

    //std::vector<variable> testvec;
    std::string varSize;

    //extract sign is part of 2nd element
    if (inputLine[1].find("U") != std::string::npos)
    {
        isSigned = true;
    }

    //extract sign is part of 2nd element
    int numIdx = inputLine[1].find_first_of("0123456789");
    varSize = inputLine[1].substr(numIdx);

    //IO always listed as 3rd to end elements
    for( int i=2; i < inputLine.size(); i++)
    {
        varVec_.push_back( variable(inputLine[i], std::stoi(varSize), isSigned ));
        std::cout << "varvec= " << inputLine[i] << ", " << varSize << ", " << isSigned << std::endl;
        std::cout << "varvec= " << inputLine[i] << ", " << std::to_string(std::stoi(varSize)) << ", " << isSigned << std::endl;

    }
    return;
}

bool fileparser::finalizeComponent(comp_type type, comp_size datawidth, 
              vector<variable> in, vector<variable> out, int outputPos)
{
    std::cout << "got to finalize component" << std::endl;

    // Find what number component this should be
    int compnum = compVec_.size();

    std::cout << "got to finalize component" << std::endl;
    std::cout << type << std::endl;
    std::cout << datawidth << std::endl;
    std::cout << compnum << std::endl;
    //std::cout << outputPos << std::endl;

    // If output is a register and the component is not REG, call handleRegOutput

    //TODO: Determine component type
    //build and append component to compvec
    //component temp(type, datawidth, in, out, compnum, outputPos);
    component temp(type, datawidth, in, out, compnum);
    compVec_.push_back(temp);

    std::cout << "got to finalize component" << std::endl;

    std::cout << "comp params: " << type << ", " << datawidth << std::endl;

    return true;
}

int fileparser::findVariableIndex(std::string& varName)
{
    // Loop through existing variables
    for( int i=0; i< varVec_.size(); i++ )
    {
        if( varVec_[i] == varName )
        {
            // Variable exists
            return i;
        }
    }

    // All variables searched, variable does not exist
    return -1;
}

bool fileparser::checkForSignedVariable(std::string& varName)
{
    // Loop through existing variables
    for( int i=0; i< varVec_.size(); i++ )
    {
        // See if we found the variable
        if( varVec_[i] == varName )
        {
            // Check if signed
            if( varVec_[i].isSigned_)
            {
                return true;
            }
            else
            {
                return false;
            }
            
        }
    }
    // Shouldn't get here but there was a warning
    return false;
}

void handleRegOutput()
{
    // Call me in the case that the output is a register, but the component you're making is not a REG
    // Also has to happen when something that is Output type is set from something that is not REG
}





void fileparser::writeFile()
{
    for (int i=0; i<compVec_.size(); i++)
    {
        fout_ << compVec_[i].writeLine();
    }
}