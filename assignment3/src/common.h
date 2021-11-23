#ifndef COMMON_H
#define COMMON_H

static const bool DEBUG = true;

enum comp_type{
    Variables = -50,
    Registers = -40,
    Wires = -30,
    Inputs = -20,
    Outputs = -10,
    REG = 0,
    ADD,
    SUB,
    MUL,
    COMP,
    MUX,
    SHR,
    SHL,
    DIV,
    MOD,
    INC,
    DEC,
};

enum resource{
    UNINIT = -1,
    ADD_SUB = 0,
    MULT,
    LOGIC,
    DIV_MOD
};

enum comp_size{
    ONE = 0,
    TWO,
    EIGHT,
    SIXTEEN,
    THIRTYTWO,
    SIXTYFOUR
};

comp_size int2size(int size);

const double latlist[12][6] = 
{//      1      2      8     16     32     64
    {2.616, 2.644, 2.879, 3.061, 3.602, 3.966},      //REG
    {2.704, 3.713, 4.924, 5.638, 7.270, 9.566},      //ADD
    {3.024, 3.412, 4.890, 5.569, 7.253, 9.566},      //SUB
    {2.438, 3.651, 7.453, 7.811, 12.395, 15.354},    //MUL
    {3.031, 3.934, 5.949, 6.256, 7.264, 8.416},      //COMP
    {4.083, 4.115, 4.815, 5.623, 8.079, 8.766},      // MUX2x1
    {3.644, 4.007, 5.178, 6.460, 8.819, 11.095},     //SHR
    {3.614, 3.980, 5.152, 6.549, 8.565, 11.220},     //SHL
    {0.619, 2.144, 15.439, 33.093, 86.312, 243.233}, //DIV
    {0.758, 2.149, 16.078, 35.563, 88.142, 250.583}, //MOD
    {1.792, 2.218, 3.111, 3.471, 4.347, 6.200},      //INC
    {1.792, 2.218, 3.108, 3.701, 4.685, 6.503}       //DEC
};

inline comp_size int2size(int size)
{
    switch( size )
    {
        case 1  : return comp_size::ONE;
        case 2  : return comp_size::TWO;
        //case 4  : return comp_size::FOUR;
        case 8  : return comp_size::EIGHT;
        case 16 : return comp_size::SIXTEEN;
        case 32 : return comp_size::THIRTYTWO;
        case 64 : return comp_size::SIXTYFOUR;
        default : return comp_size::ONE;
    }
}

inline std::string size2str(comp_size size)
{
    switch( size )
    {
        case comp_size::ONE  : return "ONE";
        case comp_size::TWO  : return "TWO";
        case comp_size::EIGHT  : return "EIGHT";
        case comp_size::SIXTEEN : return "SIXTEEN";
        case comp_size::THIRTYTWO : return "THIRTYTWO";
        case comp_size::SIXTYFOUR : return "SIXTYFOUR";
        default : return "ONE";
    }
}


inline std::string type2str(comp_type type)
{
    switch( type )
    {
        case comp_type::Registers  : return "Registers";
        case comp_type::Wires  : return "Wires";
        case comp_type::Inputs  : return "Inputs";
        case comp_type::Outputs : return "Outputs";
        case comp_type::REG : return "REG";
        case comp_type::ADD : return "ADD";
        case comp_type::SUB  : return "SUB";
        case comp_type::MUL  : return "MUL";
        case comp_type::COMP : return "COMP";
        case comp_type::MUX : return "MUX";
        case comp_type::SHR : return "SHR";
        case comp_type::SHL  : return "SHL";
        case comp_type::DIV  : return "DIV";
        case comp_type::MOD : return "MOD";
        case comp_type::INC : return "INC";
        case comp_type::DEC : return "DEC";
        default : return "UNKNOWN";
    }
}

#endif