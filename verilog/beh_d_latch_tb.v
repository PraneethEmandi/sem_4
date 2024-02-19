module beh_d_latch_tb;
reg clk,rst_n,enable;
reg [7:0]d;
wire [7:0]q;
wire zero_flag;
integer count,count2;

beh_d_latch dff(clk,rst_n,enable,d,q,zero_flag);
	initial begin
	clk=1'b0;
	repeat(4096) 
	#5
	clk=~clk;
	end
	
	initial begin
	for(count=0;count<32;count=count+1)
	begin
		for(count2=0;count2<64;count2=count2+1)
		begin
			{clk,rst_n,enable}=count;
			{d[7],d[6],d[5],d[4],d[3],d[2],d[1],d[0]}=count2;
			#10;
		end
	end
	end
	
endmodule
