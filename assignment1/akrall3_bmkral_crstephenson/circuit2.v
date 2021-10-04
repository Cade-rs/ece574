`timescale 1ns / 1ps

/*
input Int32 a, b, c

output Int32 z, x

wire Int32 d, e, f, g, h
wire Int1 dLTe, dEQe
wire Int32 zwire, xwire

d = a + b
e = a + c
f = a - b
dEQe = d == e
dLTe = d < e
g = dLTe ? d : e
h = dEQe ? g : f
xwire = g << dLTe
zwire = h >> dEQe
x = xwire
z = zwire
*/

module circuit2 (a, b, c, Clk, Rst, z, x);
    input [31:0] a, b, c;
    input  Clk, Rst;
    output wire [31:0] z, x;
    
    wire [31:0] d, e, f, g, h;
    wire dLTe, dEQe;
    wire [31:0] zwire, xwire;
    
    ADD     #(.DATAWIDTH(32)) ADD1(a, b, d);            // d = a + b, 0 + 7.086
    ADD     #(.DATAWIDTH(32)) ADD2(a, c, e);            // e = a + c, 0 + 7.086
    SUB     #(.DATAWIDTH(32)) SUB1(a, b, f);            // f = a - b, 0 + 7.086
    COMP    #(.DATAWIDTH(32)) COMP1(d, e, , dLTe, dEQe);// dEQe = d == e
                                                        // dLTe = d < e, 7.086 + 7.171 = 14.257
    MUX2x1  #(.DATAWIDTH(32)) MUX1(d, e, dLTe, g);      // g = dLTe ? d : e, 14.257 + 5.361 = 19.618
    MUX2x1  #(.DATAWIDTH(32)) MUX2(g, f, dEQe, h);      // h = dEQe ? g : f, 19.618 + 5.361 = 24.979
    SHL     #(.DATAWIDTH(32)) SHL1(g, dLTe, xwire);     // xwire = g << dLTe, 19.618 + 7.044 = 26.662
    SHR     #(.DATAWIDTH(32)) SHR1(h, dEQe, zwire);     // zwire = h >> dEQe, 24.979 + 7.044 = 32.023
    REG     #(.DATAWIDTH(32)) REG1(xwire, Clk, Rst, x); // x = xwire, 26.662 + 4.090 = 30.752
    REG     #(.DATAWIDTH(32)) REG2(zwire, Clk, Rst, z); // z = zwire, 32.023 + 4.090 = 36.113
    
endmodule