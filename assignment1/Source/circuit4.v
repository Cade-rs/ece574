`timescale 1ns / 1ps

/*
input Int64 a, b, c

output Int32 z, x

wire Int64 d, e, f, g, h 
wire Int1 dLTe, dEQe 
wire Int64 xrin, zrin
register Int64 greg, hreg

d = a + b
e = a + c
f = a - b  
dEQe = d == e
dLTe = d < e
g = dLTe ? d : e 
h = dEQe ? g : f 
greg = g
hreg = h
xrin = hreg << dLTe
zrin = greg >> dEQe
x = xrin
z = zrin
*/

module circuit (a, b, c, z, x);
    input [63:0] a, b, c;
    
    output reg [31:0] z, x;
    
    wire[63:0] d, e, f, g, h;
    wire dLTe, dEQe;
    wire [63:0] xrin, zrin;
    reg [63:0] greg, hreg;
    
    always @() begin
        
    end
endmodule
