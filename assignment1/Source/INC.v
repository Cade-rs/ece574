`timescale 1ns / 1ps

module INC #(parameter DATAWIDTH = 8)(a, d); 
    input [DATAWIDTH-1:0] a;
    output reg [DATAWIDTH-1:0] d;
    
    always @(a) begin
        d <= a + 1;
    end
endmodule
