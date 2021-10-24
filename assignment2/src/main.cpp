//This is a test file

#include <string>
#include <vector>
#include <iostream>
#include "component.h"
#include "latency.h"
using namespace std;
using std::vector;

int main(void){
    std::vector<string> in, out;
    in.push_back ("a");
    out.push_back("b");
    std::cout << in[0] << ", " << out[0] << comp_type::COMP << "\n";

    component 
        comp1(comp_type::MUL,comp_size::TWO,in,out);

    return 0;
}