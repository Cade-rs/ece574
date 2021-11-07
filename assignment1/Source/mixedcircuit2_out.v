
`timescale 1ns / 1ps

module mixedcircuit2_out(a,b,c,Clk,Rst);
	input Clk,Rst;
	input [7:0] a;
	input [15:0] b;
	output wire [31:0] c;
	wire [31:0] cwire;
	ADD	#(.DATAWIDTH(32)) ADD4({{31-8{1'b0}},a},{{31-16{1'b0}},b},cwire);
	SREG	#(.DATAWIDTH(32)) SREG5(cwire,Clk,Rst,c);
endmodule