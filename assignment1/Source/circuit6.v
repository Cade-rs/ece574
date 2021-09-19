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

module circuit6 (a, b, c, zero, z);
    input [63:0] a, b, c, zero;
    
    output reg [63:0] z;
    
    wire [63:0] e, f, g, zwire;
    wire gEQz;
    
    always @() begin
        
    end
endmodule
