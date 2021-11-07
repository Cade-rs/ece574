
`timescale 1ns / 1ps

module circuit1_out(a,b,c,z,x,Clk,Rst);
	input Clk,Rst;
	input [7:0] a,b,c;
	output wire [7:0] z;
	output wire [15:0] x;
	wire [7:0] d,e;
	wire [15:0] f,g;
	wire [15:0] xwire;
	wire [7:0] z_temp;
	SADD	#(.DATAWIDTH(8)) SADD6(a,b,d);
	SADD	#(.DATAWIDTH(8)) SADD7(a,c,e);
	SCOMP	#(.DATAWIDTH(8)) SCOMP8(d,e,g[0], , );
	SMUX2x1	#(.DATAWIDTH(8)) SMUX2x110(g[7:0],d,e,z_temp);
	SREG	#(.DATAWIDTH(8)) SREG11(z_temp,Clk,Rst,z);
	SMUL	#(.DATAWIDTH(16)) SMUL12($signed(a),$signed(c),f);
	SSUB	#(.DATAWIDTH(16)) SSUB13(f,$signed(d),xwire);
	SREG	#(.DATAWIDTH(16)) SREG14(xwire,Clk,Rst,x);
endmodule