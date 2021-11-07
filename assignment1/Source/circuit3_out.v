
`timescale 1ns / 1ps

module circuit3_out(a,b,c,d,e,f,g,h,sa,avg,Clk,Rst);
	input Clk,Rst;
	input [15:0] a,b,c,d,e,f,g,h;
	input [7:0] sa;
	output wire [15:0] avg;
	wire [31:0] l00,l01,l02,l03,l10,l11,l2,l2div2,l2div4,l2div8;
	SADD	#(.DATAWIDTH(32)) SADD4($signed(a),$signed(b),l00);
	SADD	#(.DATAWIDTH(32)) SADD5($signed(c),$signed(d),l01);
	SADD	#(.DATAWIDTH(32)) SADD6($signed(e),$signed(f),l02);
	SADD	#(.DATAWIDTH(32)) SADD7($signed(g),$signed(h),l03);
	SADD	#(.DATAWIDTH(32)) SADD8(l00,l01,l10);
	SADD	#(.DATAWIDTH(32)) SADD9(l02,l03,l11);
	SADD	#(.DATAWIDTH(32)) SADD10(l10,l11,l2);
	SSHR	#(.DATAWIDTH(32)) SSHR11(l2,$signed(sa),l2div2);
	SSHR	#(.DATAWIDTH(32)) SSHR12(l2div2,$signed(sa),l2div4);
	SSHR	#(.DATAWIDTH(32)) SSHR13(l2div4,$signed(sa),l2div8);
	SREG	#(.DATAWIDTH(16)) SREG14(l2div8[15:0],Clk,Rst,avg);
endmodule