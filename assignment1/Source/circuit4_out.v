
`timescale 1ns / 1ps

module circuit4_out(a,b,c,z,x,Clk,Rst);
	input Clk,Rst;
	input [63:0] a,b,c;
	output wire [31:0] z,x;
	wire [63:0] d,e,f,g,h;
	wire  dLTe,dEQe;
	wire [63:0] xrin,zrin;
	wire [63:0] greg,hreg;
	SADD	#(.DATAWIDTH(64)) SADD6(a,b,d);
	SADD	#(.DATAWIDTH(64)) SADD7(a,c,e);
	SSUB	#(.DATAWIDTH(64)) SSUB8(a,b,f);
	SCOMP	#(.DATAWIDTH(64)) SCOMP9(d,e, , ,dEQe);
	SCOMP	#(.DATAWIDTH(64)) SCOMP10(d,e, ,dLTe, );
	SMUX2x1	#(.DATAWIDTH(64)) SMUX2x111($signed(dLTe),d,e,g);
	SMUX2x1	#(.DATAWIDTH(64)) SMUX2x112($signed(dEQe),g,f,h);
	SREG	#(.DATAWIDTH(64)) SREG13(g,Clk,Rst,greg);
	SREG	#(.DATAWIDTH(64)) SREG14(h,Clk,Rst,hreg);
	SSHL	#(.DATAWIDTH(64)) SSHL15(hreg,$signed(dLTe),xrin);
	SSHR	#(.DATAWIDTH(64)) SSHR16(greg,$signed(dEQe),zrin);
	SREG	#(.DATAWIDTH(32)) SREG17(xrin[31:0],Clk,Rst,x);
	SREG	#(.DATAWIDTH(32)) SREG18(zrin[31:0],Clk,Rst,z);
endmodule