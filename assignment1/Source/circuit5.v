`timescale 1ns / 1ps

/*
input Int64 a, b, c, d, zero

output Int64 z

wire Int64 e, f, g, zwire
wire Int1 gEQz

e = a / b
f = c / d
g = a % b
gEQz = g == zero
zwire = gEQz ? e : f
z = zwire
*/

module circuit5 (a, b, c, d, zero, Clk, Rst, z);
    input [63:0] a, b, c, d, zero;
    input  Clk, Rst;
    
    output reg [63:0] z;
    
    wire [63:0] e, f, g, zwire;
    wire gEQz;
    
    DIV     #(.DATAWIDTH(64)) DIV1(a, b, e);            // e = a / b
    DIV     #(.DATAWIDTH(64)) DIV2(c, d, f);            // f = c / d
    MOD     #(.DATAWIDTH(64)) MOD1(a, b, g);            // g = a % b
    COMP    #(.DATAWIDTH(64)) COMP1(g, zero, , , gEQz); // gEQz = g == zero
    MUX2x1  #(.DATAWIDTH(64)) MUX1(e, f, gEQz, zwire);  // zwire = gEQz ? e : f
    REG     #(.DATAWIDTH(64)) REG1(zwire, Clk, Rst, z); // z = zwire
    
endmodule