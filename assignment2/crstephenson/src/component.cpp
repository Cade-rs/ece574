#include "component.h"
#include "latency.h"
#include <string>

int main(void){
    return 0;
}

component::component(COMPONENT type, SIZE datawidth, std::string in, std::string out)
{
    type_ = type;
    dw_ = datawidth;
    in_ = in;
    out_ = out;
    lat_ = findLatency();
}

double component::findLatency(void)
{
    lat_ = latlist[type_][dw_];
    return(0);
}