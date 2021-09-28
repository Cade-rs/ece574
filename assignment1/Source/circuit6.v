`timescale 1ns / 1ps

/*
input Int64 a, b, c, zero

output Int64 z

wire Int64 e, f, g, zwire
wire Int1 gEQz

e = a - 1
f = c + 1
g = a % c
gEQz = g == zero
zwire = gEQz ? e : f
z = zwire
*/

module circuit6 (a, b, c, zero, Clk, Rst, z);
    input [63:0] a, b, c, zero;
    input  Clk, Rst;
    
    output wire [63:0] z;
    
    wire [63:0] e, f, g, zwire;
    wire gEQz;
    
    DEC     #(.DATAWIDTH(64)) DEC1(a, e);               // e = a - 1
    INC     #(.DATAWIDTH(64)) INC1(c, f);               // f = c + 1
    MOD     #(.DATAWIDTH(64)) MOD1(a, c, g);            // g = a % c
    COMP    #(.DATAWIDTH(64)) COMP1(g, zero, , , gEQz); // gEQz = g == zero
    MUX2x1  #(.DATAWIDTH(64)) MUX1(e, f, gEQz, zwire);  // zwire = gEQz ? e : f
    REG     #(.DATAWIDTH(64)) REG1(zwire, Clk, Rst, z); // z = zwire
    
endmodule