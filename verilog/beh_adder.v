module beh_adder (
  input wire [7:0] A,
  input wire [7:0] B,
  output [7:0] Sum,
  output Carry
);
  reg [8:0] sum_temp;

  always @(A or B) begin
    sum_temp = A + B;
  end
  assign Sum = sum_temp[7:0];
  assign Carry = sum_temp[8];

endmodule
