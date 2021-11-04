`timescale 1ns / 1ps

module SCOMP #(parameter DATAWIDTH = 8)(a, b, gt, lt, eq);
    input [DATAWIDTH-1:0] a, b;
    output reg gt, lt, eq;
    wire sign_a, sign_b;
    
    always @(a, b) begin
        sign_a <= a[DATAWIDTH-1];
        sign_b <= b[DATAWIDTH-1];
        if (sign_a>sign_b])begin
            gt <= 0;
            lt <= 1;
            eq <= 0;
        end
        else if (sign_a<sign_b)begin
            gt <= 1;
            lt <= 0;
            eq <= 0;
        end
        else if (a[DATAWIDTH-2:0] > b[DATAWIDTH-2:0] || sign_a==0) begin
            gt <= 1;
            lt <= 0;
            eq <= 0;
        end        
        else if (a[DATAWIDTH-2:0] < b[DATAWIDTH-2:0] || sign_a==1) begin
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
