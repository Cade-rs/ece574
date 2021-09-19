`timescale 1ns / 1ps

module MUX2x1 #(parameter DATAWIDTH = 8)(a, b, sel, d);
    input [DATAWIDTH-1:0] a, b;
    output reg [DATAWIDTH-1:0] d;

    always @(a, b, sel)
        if (sel == 0) begin
            d <= a;
        end
        else begin
            d<= b;
        end
endmodule