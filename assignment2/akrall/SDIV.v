`timescale 1ns / 1ps

module SDIV #(parameter DATAWIDTH = 8)(a, b, quot); 
    input [DATAWIDTH-1:0] a;
    input [DATAWIDTH-1:0] b;
    output reg [DATAWIDTH-1:0] quot;
    
    always @(a, b) begin
        quot <= a / b;
    end
endmodule
