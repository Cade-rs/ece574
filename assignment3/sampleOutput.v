module HLSM(Clk, Rst, Start, Done, a, b, c, z, x)

input Clk, Rst, Start;
input [15:0] a, b, c;

output reg Done;
output reg [7:0] z;
output reg [15:0] x;

reg [7:0] d, e, f, g, State;

parameter [7:0]  S0=0, S1=1, S2=2, S3=3, S4=4;
parameter [7:0]  S5=5, S6=6, S7=7;

always @(posedge Clk) begin
if (Rst == 1) begin
	i<= 0;
	Done <= 0;
end
else begin
case (State)

S0: begin
	if (Start == 1) begin
		State <= S1;
	end
	else begin
		State <= S0;
	end
end

S1: begin
	//scheduled in 1
	d <= a + b;
	State <= S2;
end

S2: begin
	//scheduled in 2
	e <= a + c;
	State <= S3;
end

S3: begin
	//scheduled in 3
	g <= d > e;
	State <= S4;
end

S4: begin
	//scheduled in 4
	if (g) begin
		z <= d;
	end
	else begin
		z <= e;
	end
	State <= S5;
end

S5: begin
	//scheduled in 1
	f <= a * c;
	State <= S6;
end

S6: begin
	//scheduled in 3
	x <= f - d;
	State <= S7;
end

S7: begin
	Done <= 1;
	State <= S0;
end
endcase
end
end
endmodule
