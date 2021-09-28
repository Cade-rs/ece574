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

module circuit3 (a, b, c, d, e, f, g, h, Clk, Rst, sa, avg);
    input [15:0] a, b, c, d, e, f, g, h;
    input [7:0] sa;
    input  Clk, Rst;
    
    output wire [15:0] avg;
    
    wire [31:0] l00, l01, l02, l03, l10, l11, l2, l2div2, l2div4, l2div8;
    
    ADD #(.DATAWIDTH(32)) ADD1(a, b, l00);              // l00 = a + b
    ADD #(.DATAWIDTH(32)) ADD2(c, d, l01);              // l01 = c + d
    ADD #(.DATAWIDTH(32)) ADD3(e, f, l02);              // l02 = e + f
    ADD #(.DATAWIDTH(32)) ADD4(g, h, l03);              // l03 = g + h
    ADD #(.DATAWIDTH(32)) ADD5(l00, l01, l10);          // l10 = l00 + l01
    ADD #(.DATAWIDTH(32)) ADD6(l02, l03, l11);          // l11 = l02 + l03
    ADD #(.DATAWIDTH(32)) ADD7(l10, l11, l2);           // l2 = l10 + l11
    SHR #(.DATAWIDTH(32)) SHR1(l2, sa, l2div2);         // l2div2 = l2 >> sa
    SHR #(.DATAWIDTH(32)) SHR2(l2div2, sa, l2div4);     // l2div4 = l2div2 >> sa
    SHR #(.DATAWIDTH(32)) SHR3(l2div4, sa, l2div8);     // l2div8 = l2div4 >> sa
    REG #(.DATAWIDTH(16)) REG1(l2div8[15:0], Clk, Rst, avg);  // avg = l2div8
    
endmodule
