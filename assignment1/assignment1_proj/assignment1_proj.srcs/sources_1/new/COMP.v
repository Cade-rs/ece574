`timescale 1ns / 1ps

module COMP #(parameter DATAWIDTH = 8)(a, b, gt, lt, eq);
    input [DATAWIDTH-1:0] a, b;
    output wire gt;
    
    always @(a, b) begin
        if (a > b) begin
            gt <= 1;
            lt <= 0;
            eq <= 0;
        end        
        else if (a < b) begin
            gt <= 0;
            lt <= 1;
            eq <= 0;
        end
        else begin
            gt <= 0;
            lt <= 0;
            eq <= 1;
        end 
    end
endmodule