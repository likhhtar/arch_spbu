module stack_behaviour_easy(
    output wire[3:0] O_DATA, 
    input wire RESET, 
    input wire CLK, 
    input wire[1:0] COMMAND, 
    input wire[2:0] INDEX,
    input wire[3:0] I_DATA
    ); 

    bit [4:0] [3:0] stack;
    reg [2:0] head;
    reg [3:0] output_;
    assign O_DATA = output_;

    initial begin
        head = 4;
    end
    
    always @(CLK) begin
        if (CLK == 1 && RESET == 0) begin
            if (COMMAND == 2'b01) begin
                head = (head + 1) % 5;
                stack[head] = I_DATA;
            end
            else if (COMMAND == 2'b10) begin
                output_ = stack[head];
                head = (head + 4) % 5;
            end
            else if (COMMAND == 2'b11) begin
                output_ = stack[(head - (INDEX) % 5 + 5) % 5];
            end
        end
    end

    always @(RESET) begin
        if (RESET == 1) begin
            head = 4;
            
            for(integer i = 0; i < 5; i += 1) begin
                stack[i] = 0;
            end
            
            output_ = stack[head];
        end
    end
endmodule