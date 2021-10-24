#include "component.h"
#include "latency.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;
using std::vector;

//int main(void){
//    return 0;
//}

component::component(int type, int datawidth, vector<string> in, vector<string> out)
{
    type_ = type;
    dw_ = datawidth;

    for (int i=0; i<in.size(); i++)
    {
        in_ = in;
    }

    for (int i=0; i<out.size(); i++)
    {
        out_ = out;
    }

    lat_ = findLatency();
}

double component::findLatency(void)
{
    lat_ = latlist[type_][dw_];
    return(0);
}