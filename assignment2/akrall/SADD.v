`timescale 1ns / 1ps

module SADD #(parameter DATAWIDTH = 8)(a, b, sum);
    input [DATAWIDTH-1:0] a, b;
    output reg [DATAWIDTH-1:0] sum;
    
    //Implementing the Sign and Magnitude Intermediates
    reg sign_a, sign_b, sign_sum;
    reg [DATAWIDTH-2:0] mag_a, mag_b, mag_sum, max, min;
    
    always @(a, b) begin
        mag_a <= a[DATAWIDTH-2:0];
        mag_b <= b[DATAWIDTH-2:0];
        sign_a <= a[DATAWIDTH-1];
        sign_b <= b[DATAWIDTH-1];
        
        if (mag_a>mag_b) begin
            max <= mag_a;
            min <= mag_b;
            sign <= sign_a;
        end
        else begin
            max <= mag_b;
            min <= mag_a;
            sign <=sign_b;
        end
        if (sign_a==sign_b)begin
            sum[DATAWIDTH-2:0] <=  max + min;
        end
        else begin
            sum[DATAWIDTH-2:0] <=  max - min;
        end
        sum[DATAWIDTH-1:0]<={sign,sum[DATAWIDTH-2:0]};
    end
endmodule
