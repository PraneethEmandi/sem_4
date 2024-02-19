module beh_alu (
  input [7:0] A,      
  input [7:0] B,      
  input [1:0] ALUOp,  
  output reg [8:0] Out 
);

  always @* begin
    case (ALUOp)
      2'b00:
        Out = A + B;
      2'b01:
        Out = A - B;
      2'b10: begin
        Out = A ^ B;
        Out[8] = 1'b0;
      end
      2'b11: begin
        Out = A << 1;
        Out[8] = 1'b0;
      end
      default:
        Out = 9'b0;
    endcase
  end

endmodule

