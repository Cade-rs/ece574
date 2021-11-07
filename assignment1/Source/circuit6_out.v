
`timescale 1ns / 1ps

module circuit6_out(a,b,c,zero,z,Clk,Rst);
	input Clk,Rst;
	input [63:0] a,b,c,zero;
	output wire [63:0] z;
	wire [63:0] e,f,g,zwire;
	wire  gEQz;
	SDEC	#(.DATAWIDTH(64)) SDEC4(a,e);
	SINC	#(.DATAWIDTH(64)) SINC5(c,f);
	SMOD	#(.DATAWIDTH(64)) SMOD6(a,c,g);
	SCOMP	#(.DATAWIDTH(64)) SCOMP7(g,zero, , ,gEQz);
	SMUX2x1	#(.DATAWIDTH(64)) SMUX2x18($signed(gEQz),e,f,zwire);
	SREG	#(.DATAWIDTH(64)) SREG9(zwire,Clk,Rst,z);
endmodule