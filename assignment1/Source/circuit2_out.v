
`timescale 1ns / 1ps

module circuit2_out(a,b,c,z,x,Clk,Rst);
	input Clk,Rst;
	input [31:0] a,b,c;
	output wire [31:0] z,x;
	wire [31:0] d,e,f,g,h;
	wire  dLTe,dEQe;
	wire [31:0] zwire,xwire;
	SADD	#(.DATAWIDTH(32)) SADD5(a,b,d);
	SADD	#(.DATAWIDTH(32)) SADD6(a,c,e);
	SSUB	#(.DATAWIDTH(32)) SSUB7(a,b,f);
	SCOMP	#(.DATAWIDTH(32)) SCOMP8(d,e, , ,dEQe);
	SCOMP	#(.DATAWIDTH(32)) SCOMP9(d,e, ,dLTe, );
	SMUX2x1	#(.DATAWIDTH(32)) SMUX2x110($signed(dLTe),d,e,g);
	SMUX2x1	#(.DATAWIDTH(32)) SMUX2x111($signed(dEQe),g,f,h);
	SSHL	#(.DATAWIDTH(32)) SSHL12(g,$signed(dLTe),xwire);
	SSHR	#(.DATAWIDTH(32)) SSHR13(h,$signed(dEQe),zwire);
	SREG	#(.DATAWIDTH(32)) SREG14(xwire,Clk,Rst,x);
	SREG	#(.DATAWIDTH(32)) SREG15(zwire,Clk,Rst,z);
endmodule