
`timescale 1ns / 1ps

module mixedcircuit1_out(a,b,c,Clk,Rst);
	input Clk,Rst;
	input [7:0] a;
	input [7:0] b;
	output wire [7:0] c;
	wire [7:0] cwire;
	ADD	#(.DATAWIDTH(8)) ADD4(a,b,cwire);
	SREG	#(.DATAWIDTH(8)) SREG5(cwire,Clk,Rst,c);
endmodule