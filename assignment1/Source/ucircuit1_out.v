
`timescale 1ns / 1ps

module ucircuit1_out(a,b,c,Clk,Rst);
	input Clk,Rst;
	input [7:0] a,b;
	output wire [7:0] c;
	wire [7:0] cwire;
	ADD	#(.DATAWIDTH(8)) ADD3(a,b,cwire);
	REG	#(.DATAWIDTH(8)) REG4(cwire,Clk,Rst,c);
endmodule