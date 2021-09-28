`timescale 1ns / 1ps

/*
input Int8 a, b, c

output Int8 z
output Int16 x

wire Int8 d, e
wire Int16 f, g
wire Int16 xwire

d = a + b
e = a + c
g = d > e
z = g ? d : e
f = a * c
xwire = f - d
x = xwire
*/

module circuit1 (a, b, c, Clk, Rst, z, x);
    input [7:0] a, b, c;
    input  Clk, Rst;
    
    output wire [7:0] z;
    output wire [15:0] x;
    
    wire [7:0] d, e;
    wire [15:0] f, g;
    wire [15:0] xwire;
    
    ADD     #(.DATAWIDTH(8))  ADD1(a, b, d);            // d = a + b
    ADD     #(.DATAWIDTH(8))  ADD2(a, c, e);            // e = a + c
    COMP    #(.DATAWIDTH(8))  COMP1(d, e, g[0], , );    // g = d > e
    // Added zwire, unsure about order for ternary operator
    MUX2x1  #(.DATAWIDTH(8))  MUX1(d, e, g[0], z);  // z = g ? d : e
    MUL     #(.DATAWIDTH(16)) MUL1(a, c, f);            // f = a * c
    SUB     #(.DATAWIDTH(16)) SUB1(f, d, xwire);        // xwire = f - d
    REG     #(.DATAWIDTH(16)) REG1(xwire, Clk, Rst, x); // x = xwire
    
endmodule