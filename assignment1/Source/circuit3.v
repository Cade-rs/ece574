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
    
    ADD #(.DATAWIDTH(32)) ADD1(a, b, l00);              // l00 = a + b, 0 + 7.086 = 7.086
    ADD #(.DATAWIDTH(32)) ADD2(c, d, l01);              // l01 = c + d, 0 + 7.086 = 7.086
    ADD #(.DATAWIDTH(32)) ADD3(e, f, l02);              // l02 = e + f, 0 + 7.086 = 7.086
    ADD #(.DATAWIDTH(32)) ADD4(g, h, l03);              // l03 = g + h, 0 + 7.086 = 7.086
    ADD #(.DATAWIDTH(32)) ADD5(l00, l01, l10);          // l10 = l00 + l01, 7.086 + 7.086 = 14.172
    ADD #(.DATAWIDTH(32)) ADD6(l02, l03, l11);          // l11 = l02 + l03, 7.086 + 7.086 = 14.172
    ADD #(.DATAWIDTH(32)) ADD7(l10, l11, l2);           // l2 = l10 + l11, 14.172 + 7.086 = 21.258
    SHR #(.DATAWIDTH(32)) SHR1(l2, sa, l2div2);         // l2div2 = l2 >> sa, 21.258 + 7.044 = 28.302
    SHR #(.DATAWIDTH(32)) SHR2(l2div2, sa, l2div4);     // l2div4 = l2div2 >> sa, 28.302 + 7.044 = 35.346
    SHR #(.DATAWIDTH(32)) SHR3(l2div4, sa, l2div8);     // l2div8 = l2div4 >> sa, 35.346 + 7.044 = 42.39
    REG #(.DATAWIDTH(16)) REG1(l2div8[15:0], Clk, Rst, avg);  // avg = l2div8, 42.39 + 4.090 = 46.48
    
endmodule
