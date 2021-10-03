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

module circuit4 (a, b, c, Clk, Rst, z, x);
    input [63:0] a, b, c;
    input  Clk, Rst;
    
    output wire [31:0] z, x;
    
    wire[63:0] d, e, f, g, h;
    wire dLTe, dEQe;
    wire [63:0] xrin, zrin;
    wire [63:0] greg, hreg;
    
    ADD     #(.DATAWIDTH(64)) ADD1(a, b, d);                    // d = a + b, 0 + 8.022 = 8.022
    ADD     #(.DATAWIDTH(64)) ADD2(a, c, e);                    // e = a + c, 0 + 8.022 = 8.022
    SUB     #(.DATAWIDTH(64)) SUB1(a, b, f);                    // f = a - b, 0 + 8.022 = 8.022
    COMP    #(.DATAWIDTH(64)) COMP1(d, e, , dLTe, dEQe);        // dEQe = d == e, 8.022 + 7.639 = 15.661
                                                                // dLTe = d < e
    MUX2x1  #(.DATAWIDTH(64)) MUX1(d, e, dLTe, g);              // g = dLTe ? d : e, 15.661 + 5.361 = 21.022
    MUX2x1  #(.DATAWIDTH(64)) MUX2(g, f, dEQe, h);              // h = dEQe ? g : f, 21.022 + 5.361 = 23.926
    REG     #(.DATAWIDTH(64)) REG1(g, Clk, Rst, greg);          // greg = g, 21.022 + 4.090 = 25.112
    REG     #(.DATAWIDTH(64)) REG2(h, Clk, Rst, hreg);          // hreg = h, 23.926 + 4.090 = 28.016
    SHL     #(.DATAWIDTH(64)) SHL1(hreg, dLTe, xrin);           // xrin = hreg << dLTe, 28.016 + 8.015 = 36.031
    SHR     #(.DATAWIDTH(64)) SHR1(greg, dEQe, zrin);           // zrin = greg >> dEQe, 25.112 + 7.708 = 32.82
    REG     #(.DATAWIDTH(32)) REG3(xrin[31:0], Clk, Rst, x);    // x = xrin, 36.031 + 4.090 = 40.121
    REG     #(.DATAWIDTH(32)) REG4(zrin[31:0], Clk, Rst, z);    // z = zrin, 32.82 + 4.090 = 36.91
    
endmodule