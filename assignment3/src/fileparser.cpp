#include "fileparser.h"
#include "common.h"


#include <iostream>
#include <regex>
#include <string>


// -------------------------------------------------------------------------------
// 
// -------------------------------------------------------------------------------
fileparser::fileparser(std::string infile, std::string outfile)
{
    error_ = false;
    lastIfLeft_ = 0;
    fin_.open(infile);
    
    outfile_="./debug_out.txt";
    if( DEBUG )
    {
        fout_.open(outfile_);
    }
    
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
}

// -------------------------------------------------------------------------------
// 
// -------------------------------------------------------------------------------
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

    fin_.close();
    fout_.close();

    return error_;
}

// -------------------------------------------------------------------------------
// 
// -------------------------------------------------------------------------------
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
        constructVariables(line);
    }
    else if( line.rfind("register", 0) == 0 )
    {
        // Register
        constructVariables(line);
    }
    else if( line.rfind("variable", 0) == 0 )
    {
        // Register
        constructVariables(line);
    }
    else if ( line.rfind("if", 0) == 0 )
    {
        // what do?
        std::cout << "I got to IF! What do?" << std::endl << line << std::endl;
        constructIfElse(line);
    }
    else if ( line.rfind("else", 0) == 0 )
    {
        // what do?
        std::cout << "I got to ELSE! What do?" << std::endl << line << std::endl;
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
    else if( line.find("}") != std::string::npos )
    {
        // End if statement, handle later
    }
    else if( line.find("{") != std::string::npos )
    {
        // Start if, do nothing
    }
    else if( line == "" )
    {
        //Empty line
        //std::cout << "I am empty!" << std::endl << line << std::endl;
    }
    else
    {
        //TODO: use this as error reporting for invalid command characters
        std::cout << "ERROR: Unrecognized command: " << std::endl << line << std::endl;
        
        if( !DEBUG )
        {
            error_ = true;
        }
    }

    if( line.find("}") != std::string::npos )
    {
        // End if statement
        lastIfLeft_ = currentIfs_[currentIfs_.size()-1];
        currentIfs_.pop_back();
    }

    return;
}

// -------------------------------------------------------------------------------
// 
// -------------------------------------------------------------------------------
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

// -------------------------------------------------------------------------------
// 
// -------------------------------------------------------------------------------
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

// -------------------------------------------------------------------------------
// 
// -------------------------------------------------------------------------------
void fileparser::constructVariables(std::string& line)
{
    std::vector<std::string> splitLine = stringSplit(line);
    std::vector<variable> wires;
    std::vector<variable> outputs;

    // update varVec_ with only wires
    wires = buildVarVec(splitLine, true); // true denotes this is a register

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

// -------------------------------------------------------------------------------
// 
// -------------------------------------------------------------------------------
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

// -------------------------------------------------------------------------------
// 
// -------------------------------------------------------------------------------
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

// -------------------------------------------------------------------------------
// 
// -------------------------------------------------------------------------------
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
        // Do nothing
        //inputs.push_back( variable( varVec_[varIdx] ) );
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

// -------------------------------------------------------------------------------
// 
// -------------------------------------------------------------------------------
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

// -------------------------------------------------------------------------------
// 
// -------------------------------------------------------------------------------
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
    type = comp_type::DIV;

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

// -------------------------------------------------------------------------------
// 
// -------------------------------------------------------------------------------
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

// -------------------------------------------------------------------------------
// 
// -------------------------------------------------------------------------------
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

// -------------------------------------------------------------------------------
// 
// -------------------------------------------------------------------------------
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
        std::cout << "ERROR: Invalid line: " << line << std::endl;
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

// -------------------------------------------------------------------------------
// 
// -------------------------------------------------------------------------------
void fileparser::constructIfElse(std::string& line)
{
    
    // std::vector<ifStatement> ifStatements_;
    // std::vector<int> currentIfs_;

    /*struct ifStatement
    {
        int ifNumber;
        bool isElse;
        std::vector<int> components;
        std::string condition;
        int correspondingIfElse;
        int withinIf;
    };*/

    bool isElse = (line.rfind("else", 0) == 0);

    // find what's within the parentheses
    // if ( ARG ) {
    std::vector<std::string> splitLine = stringSplit(line);
    std::string condition = splitLine[2];

    ifStatement newIf;

    newIf.ifNumber = ifStatements_.size();
    newIf.isElse = isElse;
    newIf.condition = condition;

    if ( isElse )
    {
        newIf.correspondingIfElse = lastIfLeft_;
        ifStatements_[lastIfLeft_].correspondingIfElse = newIf.ifNumber;
    }

    if( currentIfs_.size() > 0)
    {
        newIf.withinIf = currentIfs_[currentIfs_.size()-1];
    }
    else
    {
        newIf.withinIf = -1;
    }

    ifStatements_.push_back(newIf);
    currentIfs_.push_back(newIf.ifNumber);

}

// -------------------------------------------------------------------------------
// 
// -------------------------------------------------------------------------------
std::vector<std::string> fileparser::stringSplit(std::string line, std::string re)
{
    std::regex delim(re);
    std::vector<std::string> result {std::sregex_token_iterator(line.begin(), line.end(), delim, -1), {} };
    return result;
}

// -------------------------------------------------------------------------------
// 
// -------------------------------------------------------------------------------
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

// -------------------------------------------------------------------------------
// 
// -------------------------------------------------------------------------------
bool fileparser::finalizeComponent(comp_type type, comp_size datawidth, 
              vector<variable> in, vector<variable> out, bool isSigned, int outputPos)
{
    
    
    // Find what number component this should be
    int compnum = compVec_.size();

    int withinIf = -1;

    // Add info if we're in an if statement
    if( currentIfs_.size() > 0)
    {
        withinIf = currentIfs_[currentIfs_.size()-1];
        ifStatements_[ currentIfs_[currentIfs_.size()-1] ].components.push_back(compnum);
    }

    //build and append component to compvec
    //component temp(type, datawidth, in, out, compnum, outputPos);
    /*component(comp_type type, comp_size datawidth, 
              vector<variable> in, vector<variable> out, 
              bool isSigned=false, int compNum=0, int outputPos=0);*/
    component temp(type, datawidth, in, out, isSigned, compnum, outputPos);
    compVec_.push_back(temp);
    
    if (DEBUG)
    {
        //temp.printComponent(fout_); //cade removed this to prevent double printing
    }

    return true;
}

// -------------------------------------------------------------------------------
// 
// -------------------------------------------------------------------------------
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

// -------------------------------------------------------------------------------
// 
// -------------------------------------------------------------------------------
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

