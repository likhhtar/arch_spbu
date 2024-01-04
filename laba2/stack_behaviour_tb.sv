`include "stack_behaviour.sv"

module stack_behaviour_tb;
    wire[3:0] output_data;
    reg reset_ = 0;
    reg clock = 0; 
    reg[1:0] cmd;
    reg[2:0] ind;
    reg[3:0] input_data;
    stack_behaviour_easy stck(
        .O_DATA(output_data),
        .RESET(reset_),
        .CLK(clock),
        .COMMAND(cmd),
        .INDEX(ind),
        .I_DATA(input_data)
    );
    initial begin
        $monitor("%t      cmd: %b, clock: %0d, index: %b reset: %b, in: %b, out: %b", $time, cmd, clock, ind, reset_, input_data, output_data);
        $display("push while reset is on");

        
        #1 cmd = 1; input_data = 7; reset_ = 1;
        #1 clock = 1;
        #1 clock = 0; input_data = 10; reset_ = 0;
        #1 clock = 1;
        #1 clock = 0; cmd = 3; reset_ = 0;


        for (integer i = 0; i < 5; i++) begin
             #1 ind = i;
             #1 clock = 1;
             #1 clock = 0;
        end


        #1; $display("push once and pop");


        #1 cmd = 1; input_data = 7; 
        #1 clock = 1;
        #1 clock = 0;

        #1 cmd = 2; 
        #1 clock = 1;
        #1 clock = 0;

        for (integer i = 0; i < 6; i++) begin
             #1 clock = 1;
             #1 clock = 0;
        end

        #1; $display("push and get this and previous elements");

        for (integer i = 1; i <= 6; i++) begin
             #1 cmd = 1; input_data = i;
             #1 clock = 1;
             #1 clock = 0;

             #1 cmd = 3; ind = 1; 
             #1 clock = 1;
             #1 clock = 0;

             #1 cmd = 3; ind = 0; 
             #1 clock = 1;
             #1 clock = 0;
        end

        

        #1 $display("reset and get every element"); reset_ = 1;
        #1 reset_ = 0;
        for (integer i = 0; i < 5; i++) begin
            ind = i; 
            #1 clock = 1;
            #1 clock = 0;
        end
    end
    
endmodule
