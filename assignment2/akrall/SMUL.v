`timescale 1ns / 1ps

module SMUL #(parameter DATAWIDTH = 8)(a, b, prod); 
    input [DATAWIDTH-1:0] a;
    input [DATAWIDTH-1:0] b;
    output reg [DATAWIDTH-1:0] prod;
    reg mag_a, mag_b, pi;
    wire sign_a, sign_b;
    
    always @(a, b) begin
        sign_a <= a[DATAWIDTH-1];
        sign_b <= b[DATAWIDTH-1];
        mag_a <= a[DATAWIDTH-2:0];
        mag_b <= b[DATAWIDTH-2:0];

        if (sign_a == sign_b)begin
            pi[DATAWIDTH-2:0] <= mag_a * mag_b;
            prod <={0,pi};
        end 
        else begin
            pi[DATAWIDTH-2:0] <= mag_a*mag_b;
            prod <= {1,pi};
        end
    end
endmodule
