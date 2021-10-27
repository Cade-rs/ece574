`timescale 1ns / 1ps

module MOD #(parameter DATAWIDTH = 8)(a, b, rem); 
    input [DATAWIDTH-1:0] a;
    input [DATAWIDTH-1:0] b;
    output reg [DATAWIDTH-1:0] rem;
    
    always @(a, b) begin
        rem <= a % b;
    end
endmodule

