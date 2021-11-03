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
        std::cout << "I am empty!" << std::endl << line << std::endl;
    }
    else
    {
        //TODO: use this as error reporting for invalid command characters
        std::cout << "I went nowhere!" << std::endl << line << std::endl;
    }
}

void fileparser::constructInputs(std::string& line)
{
    bool isSigned = false;
    std::cout << "I got to Inputs!" << std::endl << line << std::endl;
    std::vector<std::string> splitLine = stringSplit(line);
    std::vector<variable> inputs;
    std::vector<variable> outputs;

    for( int i =0; i < splitLine.size(); i++ )
    {
        std::cout << splitLine[i] << std::endl;
    }

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

    bool didItWork = finalizeComponent(type, dw, inputs, outputs);

    return;
}

void fileparser::constructOutputs(std::string& line)
{
    std::cout << "I got to Outputs!" << std::endl << line << std::endl;
    std::vector<std::string> splitLine = stringSplit(line);
    std::vector<variable> inputs;
    std::vector<variable> outputs;

    for( int i =0; i < splitLine.size(); i++ )
    {
        std::cout << splitLine[i] << std::endl;
    }

    // update varVec_ with only outputs
    outputs = buildVarVec(splitLine);

    for( int i=0; i < outputs.size(); i++)
    {
        varVec_.push_back( outputs[i] );
    }

    //all outputs from one line should have same size
    comp_type type = comp_type::Outputs;
    comp_size dw = outputs[0].size_;
    bool isSigned = outputs[0].isSigned_;

    bool didItWork = finalizeComponent(type, dw, inputs, outputs);
    return;
}

void fileparser::constructWires(std::string& line)
{
    std::cout << "I got to Wires!" << std::endl << line << std::endl;
    std::vector<std::string> splitLine = stringSplit(line);
    std::vector<variable> wires;
    std::vector<variable> outputs;

    for( int i =0; i < splitLine.size(); i++ )
    {
        std::cout << splitLine[i] << std::endl;
    }

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

    bool didItWork = finalizeComponent(type, dw, wires, outputs);

    return;
}

void fileparser::constructRegisters(std::string& line)
{
    std::cout << "I got to Registers!" << std::endl << line << std::endl;
    std::vector<std::string> splitLine = stringSplit(line);
    std::vector<variable> inputs;
    std::vector<variable> registers;

    for( int i =0; i < splitLine.size(); i++ )
    {
        std::cout << splitLine[i] << std::endl;
    }

    // update varVec_ with only registers
    registers = buildVarVec(splitLine);

    for( int i=0; i < registers.size(); i++)
    {
        varVec_.push_back( registers[i] );
    }

    //all registers from one line should have same size
    comp_type type = comp_type::Registers;
    comp_size dw = registers[0].size_;
    bool isSigned = registers[0].isSigned_;

    bool didItWork = finalizeComponent(type, dw, inputs, registers);
    return;

    // The error line containing an invalid character currently goes here. 
    // Need to handle this:
    // d = a $ b
}

void fileparser::constructShift(std::string& line)
{
    // Example line:
    // SHR: out = in1 >> in2
    // SHL: out = in1 << in2

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

    // Determine size
    comp_size datawidth = outputs[0].size_;

    // Call finalizeComponent to determine signed/unsigned, compNum, handle register creation
    bool didItWork = finalizeComponent(type, datawidth, inputs, outputs);
    
    return;
}

void fileparser::constructCOMP(std::string& line)
{
    std::cout << "I got to COMP!" << std::endl << line << std::endl;
    
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
        outputPos = 0;
    }
    else if( splitLine[3] == "<" )
    {
        outputPos = 1;
    }
    else // equal to
    {
        outputPos = 2;
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

    // Determine size
    comp_size datawidth = maxInputSize;

    // Call finalizeComponent to determine signed/unsigned, compNum, handle register creation
    bool didItWork = finalizeComponent(type, datawidth, inputs, outputs);
    
    return;
}

void fileparser::constructADDorSUB(std::string& line)
{
    std::cout << "I got to ADD/INC/SUB/DEC!" << std::endl << line << std::endl;

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
        std::cout << "I got to INC!" << std::endl;
        type = comp_type::INC;
    }
    else if( splitLine[3] == "+" )
    {
        std::cout << "I got to ADD!" << std::endl;
        type = comp_type::ADD;
    }
    else if( splitLine[3] == "-" && splitLine[4] == "1" )
    {
        std::cout << "I got to DEC!" << std::endl;
        type = comp_type::DEC;
    }
    else if( splitLine[3] == "-")
    {
        std::cout << "I got to SUB!" << std::endl;
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

    // Determine size
    comp_size datawidth = outputs[0].size_;

    // Call finalizeComponent to determine signed/unsigned, compNum, handle register creation
    bool didItWork = finalizeComponent(type, datawidth, inputs, outputs);
    
    return;
}

void fileparser::constructMUL(std::string& line)
{
    std::cout << "I got to MUL!" << std::endl << line << std::endl;

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

    // Call finalizeComponent to determine signed/unsigned, compNum, handle register creation
    bool didItWork = finalizeComponent(type, datawidth, inputs, outputs);
    
    return;
}
void fileparser::constructDIV(std::string& line)
{
    std::cout << "I got to DIV!" << std::endl << line << std::endl;

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

    // Call finalizeComponent to determine signed/unsigned, compNum, handle register creation
    bool didItWork = finalizeComponent(type, datawidth, inputs, outputs);
    
    return;
}
void fileparser::constructMOD(std::string& line)
{
    std::cout << "I got to MOD!" << std::endl << line << std::endl;

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
void fileparser::constructMUX(std::string& line)
{
    std::cout << "I got to MUX!" << std::endl << line << std::endl;

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

    // Determine size
    comp_size datawidth = outputs[0].size_;

    // Call finalizeComponent to determine signed/unsigned, compNum, handle register creation
    bool didItWork = finalizeComponent(type, datawidth, inputs, outputs);
    
    return;
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

std::vector<variable> fileparser::buildVarVec(std::vector<std::string>& inputLine)
{
    bool isSigned = false;
    std::string varSize;
    std::vector<variable> varVec;

    //extract sign from part of 2nd element
    if (inputLine[1].find("U") != std::string::npos)
    {
        isSigned = true;
    }

    //extract size from part of 2nd element
    int numIdx = inputLine[1].find_first_of("0123456789");
    varSize = inputLine[1].substr(numIdx);

    //IO always listed as 3rd to end elements
    for( int i=2; i < inputLine.size(); i++)
    {
        varVec.push_back( variable(inputLine[i], std::stoi(varSize), isSigned ));
        std::cout << "varvec= " << inputLine[i] << ", " << varSize << ", " << isSigned << std::endl;
    }
    return varVec;
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

    //TODO: If output is a register and the component is not REG, call handleRegOutput
    //TODO: Determine component type? I think this is done.
    //TODO: Determine Comparator DW - nope, DONE
    //TODO: Add outputPos for comparator

    //build and append component to compvec
    //component temp(type, datawidth, in, out, compnum, outputPos);
    component temp(type, datawidth, in, out, compnum);
    compVec_.push_back(temp);
    
    if (DEBUG)
    {
        temp.printComponent(fout_);
    }

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