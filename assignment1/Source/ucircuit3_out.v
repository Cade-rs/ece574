
`timescale 1ns / 1ps

module ucircuit3_out(a,b,c,Clk,Rst);
	input Clk,Rst;
	input [31:0] a;
	input [15:0] b;
	output wire [7:0] c;
	wire [7:0] cwire;
	ADD	#(.DATAWIDTH(8)) ADD4(a[7:0],b[7:0],cwire);
	REG	#(.DATAWIDTH(8)) REG5(cwire,Clk,Rst,c);
endmodule