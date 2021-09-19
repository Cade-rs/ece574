`timescale 1ns / 1ps

/*
input Int16 a, b, c, d, e, f, g, h
input Int8 sa

output Int16 avg

wire Int32 l00, l01, l02, l03, l10, l11, l2, l2div2, l2div4, l2div8

l00 = a + b
l01 = c + d
l02 = e + f
l03 = g + h
l10 = l00 + l01
l11 = l02 + l03
l2 = l10 + l11
l2div2 = l2 >> sa
l2div4 = l2div2 >> sa 
l2div8 = l2div4 >> sa
avg = l2div8
*/

module circuit (a, b, c, d, e, f, g, h, sa, avg);
    input [15:0] a, b, c, d, e, f, g, h;
    input [7:0] sa;
    
    output reg [15:0] avg;
    
    wire [31:0] l00, l01, l02, l03, l10, l11, l2, l2div2, l2div4, l2div8;
    
    always @() begin
        
    end
endmodule
