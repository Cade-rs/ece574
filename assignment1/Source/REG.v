`timescale 1ns / 1ps

module REG #(parameter DATAWIDTH = 8)(d, Clk, Rst, q); 
    input [DATAWIDTH-1:0] d;
    input Clk, Rst;
    output reg [DATAWIDTH-1:0] q;
    
    always @(posedge Clk) begin
        if (Rst == 1) begin
            q <= 0;
        end
        else begin
            q <= d;
        end 
    end
endmodule
<<<<<<< HEAD




=======
>>>>>>> 9acd9388ba5cf9f6d17c0da52034f561d3c0d724
