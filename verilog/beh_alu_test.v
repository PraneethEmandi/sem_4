module beh_alu_test;
reg [7:0]A,B;
reg [1:0]ALUOp;
wire [8:0]Out;
beh_alu gate(A,B,ALUOp,Out);
integer count1,count2,count3;
initial begin
	for(count1=0;count1<256;count1=count1+1) 
	begin
		for(count2=0;count2<256;count2=count2+1) 
		begin
			for(count3=0;count3<4;count3=count3+1)
			begin
				{A[0],A[1],A[2],A[3],A[4],A[5],A[6],A[7]}=count1;
				{B[0],B[1],B[2],B[3],B[4],B[5],B[6],B[7]}=count2;
				{ALUOp}=count3;
				#20;
			end
		end
	end
end
endmodule
