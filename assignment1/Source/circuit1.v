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

module circuit1 (a, b, c, z, x);
    input [7:0] a, b, c;
    
    output reg [7:0] z;
    output reg [15:0] x;
    
    wire [7:0] d, e;
    wire [15:0] f, g;
    wire [15:0] xwire;
    
    always @(a, b, c) begin
        
        SUM #(.DATAWIDTH(8)) ROUNDER_1(a, b, d);
        
        
    end
endmodule
