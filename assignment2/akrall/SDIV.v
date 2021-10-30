`timescale 1ns / 1ps

module SDIV #(parameter DATAWIDTH = 8)(a, b, quot); 
    input [DATAWIDTH-1:0] a;
    input [DATAWIDTH-1:0] b;
    output reg [DATAWIDTH-1:0] quot;
    wire sign_a, sign_b;
    reg mag_a, mag_b, qi;
    
    always @(a, b) begin
        mag_a <= a[DATAWIDTH-2:0];
        mag_b <= b[DATAWIDTH-2:0];
        sign_a <= a[DATAWIDTH-1];
        sign_b <= b[DATAWIDTH-1];

        qi <= mag_a / mag_b;
        if (sign_a==sign_b)begin
            quot <={0,qi};
        end
        else begin
            quot <= {1,qi};
        end
    end
endmodule
