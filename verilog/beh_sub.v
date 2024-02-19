module beh_sub (
  input [7:0] A, 
  input [7:0] B, 
  output [7:0] Diff,
  output Borrow 
);
  reg [8:0] diff_temp;

  always @(A or B) begin
    diff_temp = A - B;
  end
  assign Diff = diff_temp[7:0];
  assign Borrow = diff_temp[8];

endmodule
