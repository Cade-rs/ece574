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
    std::cout << in[0] << ", " << out[0] << "\n";

    component 
        comp1(3,2,in,out);

    return 0;
}