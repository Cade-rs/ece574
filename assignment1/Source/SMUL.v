`timescale 1ns / 1ps

module SMUL #(parameter DATAWIDTH = 8)(a, b, prod); 
    input [DATAWIDTH-1:0] a;
    input [DATAWIDTH-1:0] b;
    output reg [DATAWIDTH-1:0] prod;
    
    always @(a, b) begin
        prod <= a * b;
    end
endmodule
