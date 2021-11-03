#include "fileparser.h"

#include <iostream>
#include <regex>
#include <string>

#define DEBUG 1

fileparser::fileparser(std::string infile, std::string outfile)
{
    error_ = false;

    fin_.open(infile);
    fout_.open(outfile);
    
    if ( !fin_.is_open() )
    {
        std::cout << "ERROR: Unable to read file: " << infile << "\n";
        error_ =  true;
    }
    else if( fin_.peek() == std::ifstream::traits_type::eof() )
    {
        std::cout << "ERROR: Input file is empty: " << infile << "\n";
        error_ =  true;
    }
    else if ( !fout_.is_open() )
    {
        std::cout << "ERROR: Unable to read file: " << outfile << "\n";
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

    if (DEBUG)
    {
        fout_ << "Final Component Order: " << std:: endl;
        for( int i = 0; i< compVec_.size(); i++ )
        {
            fout_ << "------------------------------------" << std::endl;
            compVec_[i].printComponent(fout_);
        }
    }
    
    if (!error_)
    {
        writeFile();
    }

    return error_;
}

void fileparser::parseLine(std::string& line)
{
    // Debug print line to file
    if(DEBUG)
    {
        fout_ << "------------------------------------" << std::endl;
        fout_ << "New line:" << std::endl << line << std::endl;
    }
    
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
    else if( line.find("+") != std::string::npos 
             || line.find("-") != std::string::npos )
    {
        // Add/Increment/Sub/Decrement
        constructADDorSUB(line);
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
        //Empty line
    }
    else
    {
        //TODO: use this as error reporting for invalid command characters
        std::cout << "ERROR: Unrecognized command: " << std::endl << line << std::endl;
        error_ = true;
    }
    return;
}

void fileparser::constructInputs(std::string& line)
{
    bool isSigned = false;
    std::vector<std::string> splitLine = stringSplit(line);
    std::vector<variable> inputs;
    std::vector<variable> outputs;

    // update varVec_ with only inputs
    inputs = buildVarVec(splitLine);

    for( int i=0; i < inputs.size(); i++)
    {
        varVec_.push_back( inputs[i] );
    }

    //all inputs from one line should have same size
    comp_type type = comp_type::Inputs;
    comp_size dw = inputs[0].size_;
    isSigned = inputs[0].isSigned_;

    bool didItWork = finalizeComponent(type, dw, inputs, outputs, isSigned);

    return;
}

void fileparser::constructOutputs(std::string& line)
{
    std::vector<std::string> splitLine = stringSplit(line);
    std::vector<variable> inputs;
    std::vector<variable> outputs;

    // update varVec_ with only outputs
    outputs = buildVarVec(splitLine, true); // true denotes this is a register

    for( int i=0; i < outputs.size(); i++)
    {
        varVec_.push_back( outputs[i] );
    }

    //all outputs from one line should have same size
    comp_type type = comp_type::Outputs;
    comp_size dw = outputs[0].size_;
    bool isSigned = outputs[0].isSigned_;

    bool didItWork = finalizeComponent(type, dw, inputs, outputs, isSigned);
    return;
}

void fileparser::constructWires(std::string& line)
{
    std::vector<std::string> splitLine = stringSplit(line);
    std::vector<variable> wires;
    std::vector<variable> outputs;

    // update varVec_ with only wires
    wires = buildVarVec(splitLine);

    for( int i=0; i < wires.size(); i++)
    {
        varVec_.push_back( wires[i] );
    }

    //all wires from one line should have same size
    comp_type type = comp_type::Wires;
    comp_size dw = wires[0].size_;
    bool isSigned = wires[0].isSigned_;

    bool didItWork = finalizeComponent(type, dw, wires, outputs, isSigned);

    return;
}

void fileparser::constructRegisters(std::string& line)
{
    std::vector<std::string> splitLine = stringSplit(line);
    std::vector<variable> inputs;
    std::vector<variable> registers;

    // update varVec_ with only registers
    registers = buildVarVec(splitLine, true); // true denotes this is a register

    for( int i=0; i < registers.size(); i++)
    {
        varVec_.push_back( registers[i] );
    }

    //all registers from one line should have same size
    comp_type type = comp_type::Registers;
    comp_size dw = registers[0].size_;
    bool isSigned = registers[0].isSigned_;

    bool didItWork = finalizeComponent(type, dw, inputs, registers, isSigned);
    return;
}

void fileparser::constructShift(std::string& line)
{
    // Example line:
    // SHR: out = in1 >> in2
    // SHL: out = in1 << in2

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
        type = comp_type::SHR;
    }
    else if( splitLine[3] == "<<" )
    {
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
    }
    else
    {
        std::cout << "ERROR: Output variable used but not defined: " << varName << std::endl;
        std::cout << "    On line: " << line << std::endl;
        error_ = true;
        return;
    }
    
    // Find inputs
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

    // Determine size and sign
    comp_size datawidth = outputs[0].size_;
    bool isSigned = checkCompForSignedVariable(inputs);

    // Call finalizeComponent to determine signed/unsigned, compNum, handle register creation
    bool didItWork = finalizeComponent(type, datawidth, inputs, outputs, isSigned);
    
    return;
}

void fileparser::constructCOMP(std::string& line)
{
    //std::cout << "I got to COMP!" << std::endl << line << std::endl;
    
    // Example line:
    // [GT, LT, EQ] = in1 [>,<,==] in2

    std::vector<std::string> splitLine = stringSplit(line);

    if( splitLine.size() != 5)
    {
        std::cout << "ERROR: Received different number of values than expected: " << line << std::endl;
        error_ = true;
        return;
    }

    // Instantiate variables
    comp_type type;
    comp_size maxInputSize = comp_size::ONE;
    vector<variable> outputs;
    vector<variable> inputs;
    int varIdx = -1;
    std::string varName = "";
    
    // Set type and determine which type of comparison
    type = comp_type::COMP;
    int outputPos;

    //this could be handled here (write to component class) or by the file writing part
    if( splitLine[3] == ">" )
    {
        outputPos = 1;
    }
    else if( splitLine[3] == "<" )
    {
        outputPos = 2;
    }
    else // equal to
    {
        outputPos = 3;
    }

    // Find output
    // Output is first token in splitLine
    varName = splitLine[0];
    varIdx = findVariableIndex(varName);
    if( varIdx >= 0 )
    {
        outputs.push_back( variable( varVec_[varIdx] ) );
    }
    else
    {
        std::cout << "ERROR: Output variable used but not defined: " << varName << std::endl;
        std::cout << "    On line: " << line << std::endl;
        error_ = true;
        return;
    }
    
    // Find  inputs and determine biggest input size for later
    //  Inputs are 3rd and 5th token
    varName = splitLine[2];
    varIdx = findVariableIndex(varName);
    if( varIdx >= 0 )
    {
        inputs.push_back( variable( varVec_[varIdx] ) );
        maxInputSize = (varVec_[varIdx].size_ > maxInputSize) ? varVec_[varIdx].size_ : maxInputSize;
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
        maxInputSize = (varVec_[varIdx].size_ > maxInputSize) ? varVec_[varIdx].size_ : maxInputSize;
    }
    else
    {
        std::cout << "ERROR: Input variable used but not defined: " << varName << std::endl;
        std::cout << "    On line: " << line << std::endl;
        error_ = true;
        return;
    }

    // Determine size and sign
    comp_size datawidth = maxInputSize;
    bool isSigned = checkCompForSignedVariable(inputs);

    // Call finalizeComponent to determine signed/unsigned, compNum, handle register creation
    bool didItWork = finalizeComponent(type, datawidth, inputs, outputs, isSigned, outputPos);
    
    return;
}

void fileparser::constructADDorSUB(std::string& line)
{
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
    if( splitLine[3] == "+" && splitLine[4] == "1" )
    {
        type = comp_type::INC;
    }
    else if( splitLine[3] == "+" )
    {
        type = comp_type::ADD;
    }
    else if( splitLine[3] == "-" && splitLine[4] == "1" )
    {
        type = comp_type::DEC;
    }
    else if( splitLine[3] == "-")
    {
        type = comp_type::SUB;
    }
    else
    {
        std::cout << "ERROR: ADD/SUB operator doesn't match options: " << line << std::endl;
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

    // Find  inputs
    //  INC and DEC just save off a 1
    varName = splitLine[4];
    
    if( (type == comp_type::INC || type == comp_type::DEC) && varName == "1" )
    {
        inputs.push_back( variable( varVec_[varIdx] ) );
    }
    else if( type == comp_type::INC || type == comp_type::DEC)
    {
        std::cout << "ERROR: Increment or Decrement expecting 2nd input of 1. Received:" << varName << std::endl;
        std::cout << "    On line: " << line << std::endl;
        error_ = true;
        return;
    }
    else //ADD or SUB - proceed as normal
    {    
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
    }

    // Determine size and sign
    comp_size datawidth = outputs[0].size_;
    bool isSigned = checkCompForSignedVariable(inputs);

    // Call finalizeComponent to determine signed/unsigned, compNum, handle register creation
    bool didItWork = finalizeComponent(type, datawidth, inputs, outputs, isSigned);
    
    return;
}

void fileparser::constructMUL(std::string& line)
{
    // Example line:
    // out = in1 ? in2 : in3

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
    type = comp_type::MUL;

    // Find output
    // Output is first token in splitLine
    varName = splitLine[0];
    varIdx = findVariableIndex(varName);
    if( varIdx >= 0 )
    {
        outputs.push_back( variable( varVec_[varIdx] ) );
    }
    else
    {
        std::cout << "ERROR: Output variable used but not defined: " << varName << std::endl;
        std::cout << "    On line: " << line << std::endl;
        error_ = true;
        return;
    }
    
    // Find  inputs
    //  Inputs are 3rd, 5th, and 7th token
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

    // Determine size and sign
    comp_size datawidth = outputs[0].size_;
    bool isSigned = checkCompForSignedVariable(inputs);

    // Call finalizeComponent to determine signed/unsigned, compNum, handle register creation
    bool didItWork = finalizeComponent(type, datawidth, inputs, outputs, isSigned);
    
    return;
}
void fileparser::constructDIV(std::string& line)
{
    // Example line:

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
    type = comp_type::MUX;

    // Find output
    // Output is first token in splitLine
    varName = splitLine[0];
    varIdx = findVariableIndex(varName);
    if( varIdx >= 0 )
    {
        outputs.push_back( variable( varVec_[varIdx] ) );
    }
    else
    {
        std::cout << "ERROR: Output variable used but not defined: " << varName << std::endl;
        std::cout << "    On line: " << line << std::endl;
        error_ = true;
        return;
    }
    
    // Find  inputs
    //  Inputs are 3rd, 5th, and 7th token
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
    bool isSigned = checkCompForSignedVariable(inputs);

    // Call finalizeComponent to determine signed/unsigned, compNum, handle register creation
    bool didItWork = finalizeComponent(type, datawidth, inputs, outputs, isSigned);
    
    return;
}
void fileparser::constructMOD(std::string& line)
{
        // Example line:
    
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
    type = comp_type::MOD;

    // Find output
    // Output is first token in splitLine
    varName = splitLine[0];
    varIdx = findVariableIndex(varName);
    if( varIdx >= 0 )
    {
        outputs.push_back( variable( varVec_[varIdx] ) );
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

    // Determine size and sign
    comp_size datawidth = outputs[0].size_;
    bool isSigned = checkCompForSignedVariable(inputs);

//TODO issigned

    // Call finalizeComponent to determine signed/unsigned, compNum, handle register creation
    bool didItWork = finalizeComponent(type, datawidth, inputs, outputs, isSigned);
    
    return;
}
void fileparser::constructMUX(std::string& line)
{
    // Example line:
    // out = in1 ? in2 : in3

    std::vector<std::string> splitLine = stringSplit(line);

    if( splitLine.size() != 7)
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
    type = comp_type::MUX;

    // Find output
    // Output is first token in splitLine
    varName = splitLine[0];
    varIdx = findVariableIndex(varName);
    if( varIdx >= 0 )
    {
        outputs.push_back( variable( varVec_[varIdx] ) );
    }
    else
    {
        std::cout << "ERROR: Output variable used but not defined: " << varName << std::endl;
        std::cout << "    On line: " << line << std::endl;
        error_ = true;
        return;
    }
    
    // Find  inputs
    //  Inputs are 3rd, 5th, and 7th token
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

    varName = splitLine[6];
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

    // Determine size and sign
    comp_size datawidth = outputs[0].size_;
    bool isSigned = checkCompForSignedVariable(inputs);

    // Call finalizeComponent to determine signed/unsigned, compNum, handle register creation
    bool didItWork = finalizeComponent(type, datawidth, inputs, outputs, isSigned);
    
    return;
}
void fileparser::constructREG(std::string& line)
{
    // example line: out = in
    // Instantiate variables
    comp_type type;
    vector<variable> outputs;
    vector<variable> inputs;
    int varIdx = -1;
    std::string varName = "";

    std::vector<std::string> splitLine = stringSplit(line);

    if( splitLine.size() != 3)
    {
        std::cout << "ERROR: Received different number of values than expected for REG: " << line << std::endl;
        error_ = true;
        return;
    }

    
    // Set type
    type = comp_type::REG;

    // Find output
    // Output is first token in splitLine
    varName = splitLine[0];
    varIdx = findVariableIndex(varName);
    if( varIdx >= 0 )
    {
        outputs.push_back( variable( varVec_[varIdx] ) );
    }
    else
    {
        std::cout << "ERROR: Output variable used but not defined: " << varName << std::endl;
        std::cout << "    On line: " << line << std::endl;
        error_ = true;
        return;
    }
    
    // Find input
    // Input is 3rd token
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

    // Determine size and sign
    comp_size datawidth = outputs[0].size_;
    bool isSigned = checkCompForSignedVariable(inputs);

    // Call finalizeComponent to determine signed/unsigned, compNum, handle register creation
    bool didItWork = finalizeComponent(type, datawidth, inputs, outputs, isSigned);
    
    return;
}



// Helpers
std::vector<std::string> fileparser::stringSplit(std::string line, std::string re)
{
    std::regex delim(re);
    std::vector<std::string> result {std::sregex_token_iterator(line.begin(), line.end(), delim, -1), {} };
    return result;
}

std::vector<variable> fileparser::buildVarVec(std::vector<std::string>& inputLine, bool isReg)
{
    bool isSigned = false;
    std::string varSize;
    std::vector<variable> varVec;

    //extract sign from part of 2nd element
    if (inputLine[1].find("U") == std::string::npos)
    {
        isSigned = true;
    }

    //extract size from part of 2nd element
    int numIdx = inputLine[1].find_first_of("0123456789");
    varSize = inputLine[1].substr(numIdx);

    //IO always listed as 3rd to end elements
    for( int i=2; i < inputLine.size(); i++)
    {
        varVec.push_back( variable(inputLine[i], std::stoi(varSize), isSigned, isReg ));
    }
    return varVec;
}

bool fileparser::finalizeComponent(comp_type type, comp_size datawidth, 
              vector<variable> in, vector<variable> out, bool isSigned, int outputPos)
{
    
    // If output is a register and the component is not REG, handle it
    // Need temp vector of REG components to fill in here, will append at the end
    std::vector<component> tempRegVec;

    // Skip all this if we're in Inputs, Outputs, Wires, Registers, or REG
    if( type > comp_type::REG ) 
    {
        for( int i=0; i < out.size(); i++ )
        {
            if( out[i].isReg_ == true  ) 
            {
                // Make new dummy variable, add it to varVec_
                variable dummyVar(out[i]);
                dummyVar.name_.append("_temp");
                
                varVec_.push_back(dummyVar);

                std::vector<variable> tempIn;
                tempIn.push_back(dummyVar);
                std::vector<variable> tempOut;
                tempOut.push_back(out[i]);
                std::vector<variable> tempEmpty;

                // Create new Wire component for dummy, insert between last in/out/wire/reg 
                // and before first real component
                component tempWire(comp_type::Wires, dummyVar.size_, tempIn, tempEmpty, dummyVar.isSigned_ );

                int insertIndex = 0;

                for( int j = 0; j < compVec_.size(); j++ )
                {
                    // This will set insertIndex to the first location of a component type
                    if( compVec_[j].type_ >= comp_type::REG )
                    {
                        insertIndex = j;
                        break;
                    }
                }

                compVec_.insert(compVec_.begin() + insertIndex, tempWire);

                // Replace current output with dummy
                out.at(i) = dummyVar;

                // Create REG with dummy as input, current var as output, add to tempCompVec
                component tempReg(comp_type::REG, tempOut[0].size_, tempIn, tempOut, tempOut[0].isSigned_, compVec_.size()+i+1, outputPos);
                tempRegVec.push_back(tempReg);
            }
        }
    }

    // Find what number component this should be
    int compnum = compVec_.size();

    //build and append component to compvec
    //component temp(type, datawidth, in, out, compnum, outputPos);
    /*component(comp_type type, comp_size datawidth, 
              vector<variable> in, vector<variable> out, 
              bool isSigned=false, int compNum=0, int outputPos=0);*/
    component temp(type, datawidth, in, out, isSigned, compnum, outputPos);
    compVec_.push_back(temp);

    // Add any needed REG components that were added
    for( int i = 0; i< tempRegVec.size(); i++ )
    {
        compVec_.push_back(tempRegVec[i]);
    }
    
    if (DEBUG)
    {
        temp.printComponent(fout_);
        for( int i = 0; i< tempRegVec.size(); i++ )
        {
            tempRegVec[i].printComponent(fout_);
        }
    }

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

bool fileparser::checkCompForSignedVariable(std::vector<variable>& varVec)
{
    for( int i=0; i < varVec.size(); i++)
    {
        for( int j=0; j < varVec_.size(); j++)
        {
            if( varVec_[j] == varVec[i].name_ )
            {
                // Check if unsigned
                if( !varVec_[j].isSigned_)
                {
                    return false;
                }
            }
        }
    }

    //If no unsigned inputs, return signed
    return true;
}

void fileparser::writeFile()
{
    for (int i=0; i<compVec_.size(); i++)
    {
        fout_ << compVec_[i].writeLine();
    }
}