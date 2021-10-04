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
    
    ADD     #(.DATAWIDTH(8))  ADD1(a, b, d);            // d = a + b, 0 + 6.384 = 6.384
    ADD     #(.DATAWIDTH(8))  ADD2(a, c, e);            // e = a + c, 0 + 6.384 = 6.384
    COMP    #(.DATAWIDTH(8))  COMP1(d, e, g[0], , );    // g = d > e, 6.384 + 6.820 = 13.204
    // Added zwire, unsure about order for ternary operator
    MUX2x1  #(.DATAWIDTH(8))  MUX1(d, e, g[0], z);      // z = g ? d : e, 13.204 + 5.361 = 18.565
    MUL     #(.DATAWIDTH(16)) MUL1(a, c, f);            // f = a * c, 0 + 9.052 = 9.052
    SUB     #(.DATAWIDTH(16)) SUB1(f, d, xwire);        // xwire = f - d, 9.052 + 6.618 = 15.67
    REG     #(.DATAWIDTH(16)) REG1(xwire, Clk, Rst, x); // x = xwire, 15.67 + 4.090 = 19.76
    
endmodule