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
    
    output reg [31:0] z, x;
    
    wire[63:0] d, e, f, g, h;
    wire dLTe, dEQe;
    wire [63:0] xrin, zrin;
    reg [63:0] greg, hreg;
    
    ADD     #(.DATAWIDTH(64)) ADD1(a, b, d);                    // d = a + b
    ADD     #(.DATAWIDTH(64)) ADD2(a, c, e);                    // e = a + c
    SUB     #(.DATAWIDTH(64)) SUB1(a, b, f);                    // f = a - b
    COMP    #(.DATAWIDTH(64)) COMP1(d, e, , dLTe, dEQe);        // dEQe = d == e
                                                                // dLTe = d < e
    MUX2x1  #(.DATAWIDTH(64)) MUX1(d, e, dLTe, g);              // g = dLTe ? d : e
    MUX2x1  #(.DATAWIDTH(64)) MUX2(g, f, dEQe, h);              // h = dEQe ? g : f
    REG     #(.DATAWIDTH(64)) REG1(g, Clk, Rst, greg);          // greg = g
    REG     #(.DATAWIDTH(64)) REG2(h, Clk, Rst, hreg);          // hreg = h
    SHL     #(.DATAWIDTH(64)) SHL1(hreg, dLTe, xrin);           // xrin = hreg << dLTe
    SHR     #(.DATAWIDTH(64)) SHR1(greg, dLTe, zrin);           // zrin = greg >> dEQe
    REG     #(.DATAWIDTH(32)) REG3(xrin[31:0], Clk, Rst, x);    // x = xrin
    REG     #(.DATAWIDTH(32)) REG4(zrin[31:0], Clk, Rst, z);    // z = zrin
    
endmodule