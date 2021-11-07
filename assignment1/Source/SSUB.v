`timescale 1ns / 1ps

module SSUB #(parameter DATAWIDTH = 8)(a, b, diff);
    input [DATAWIDTH-1:0] a;
    input [DATAWIDTH-1:0] b;
    output reg [DATAWIDTH-1:0] diff;

    always @(a, b) begin
        diff <= a-b;
    end
endmodule
