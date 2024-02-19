module beh_d_latch (
  input wire clk,
  input wire rst_n,
  input wire enable,
  input wire [7:0] d,
  output reg [7:0] q,
  output reg zero_flag
);

  always @(posedge clk or negedge rst_n) begin
    if (~rst_n) begin
      q <= 8'b0;
      zero_flag <= 1'b1; 
    end else if (enable) begin
      q <= d;
      zero_flag <= (q == 8'b0) ? 1'b1 : 1'b0; 
    end
  end

endmodule
