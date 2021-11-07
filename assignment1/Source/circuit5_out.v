
`timescale 1ns / 1ps

module circuit5_out(a,b,c,d,zero,z,Clk,Rst);
	input Clk,Rst;
	input [63:0] a,b,c,d,zero;
	output wire [63:0] z;
	wire [63:0] e,f,g,zwire;
	wire  gEQz;
	SMUX2x1	#(.DATAWIDTH(64)) SMUX2x14(a,b,e);
	SMUX2x1	#(.DATAWIDTH(64)) SMUX2x15(c,d,f);
	SMOD	#(.DATAWIDTH(64)) SMOD6(a,b,g);
	SCOMP	#(.DATAWIDTH(64)) SCOMP7(g,zero, , ,gEQz);
	SMUX2x1	#(.DATAWIDTH(64)) SMUX2x18($signed(gEQz),e,f,zwire);
	SREG	#(.DATAWIDTH(64)) SREG9(zwire,Clk,Rst,z);
endmodule