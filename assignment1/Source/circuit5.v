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

module circuit5 (a, b, c, d, zero, z);
    input [63:0] a, b, c, d, zero;
    
    output reg [63:0] z;
    
    wire [63:0] e, f, g, zwire;
    wire gEQz;
    
    always @() begin
        
    end
endmodule
