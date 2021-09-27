`timescale 1ns / 1ps

/*
input Int32 a, b, c

output Int32 z, x

wire Int32 d, e, f, g, h
wire Int1 dLTe, dEQe  
wire Int32 zwire, xwire

d = a + b
e = a + c
f = a - b  
dEQe = d == e
dLTe = d < e
g = dLTe ? d : e 
h = dEQe ? g : f 
xwire = g << dLTe
zwire = h >> dEQe
x = xwire
z = zwire
*/

module circuit (a, b, c, z, x);
    input [31:0] a, b, c;
    
    output reg [31:0] z, x;
    
    wire [31:0] d, e, f, g, h;
    wire dLTe, dEQe;
    wire [31:0] zwire, xwire;
    
    ADD  #(.DATAWIDTH(8))  ADD1(a, b, d);// d = a + b
    ADD  #(.DATAWIDTH(8))  ADD2(a, c, e);// e = a + c
    SUB  #(.DATAWIDTH(8))  SUB1(a, b, f);// f = a - b  
    COMP #(.DATAWIDTH(8))  COMP1(d, e, , );// dEQe = d == e
    // dLTe = d < e
    // g = dLTe ? d : e 
    // h = dEQe ? g : f 
    // xwire = g << dLTe
    // zwire = h >> dEQe
    // x = xwire
    // z = zwire
endmodule
