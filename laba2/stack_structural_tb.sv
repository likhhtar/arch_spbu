`include "stack_structural.sv"

module stack_structural_tb;
    wire[3:0] O_DATA;
    reg RESET, CLOCK;
    reg [1:0] COMMAND;
    reg [2:0] INDEX;
    reg [3:0] I_DATA;
    stack_structural_easy stack(
        .O_DATA(O_DATA),
        .RESET(RESET),
        .COMMAND(COMMAND),
        .INDEX(INDEX),
        .I_DATA(I_DATA), 
        .CLK(CLOCK)
    );

    initial begin
        $monitor("%t    CLK: %0d, COMMAND: %0d, INDEX: %B, I_DATA: %B, RESET: %0D, O_DATA: %B", $time, CLOCK, COMMAND, INDEX, I_DATA, RESET, O_DATA);

        $display("STACK_STRUCTURAL");
        $display("--- reset ---");
        #1 RESET = 1; CLOCK = 0; COMMAND = 2'd0; INDEX = 3'd0; I_DATA = 4'd0;
        #1 $display("");
        $display("--- push 1 2 3 ---");
        RESET = 0; I_DATA = 4'd1; COMMAND = 2'd1;
        #1 CLOCK = 1;
        #1 CLOCK = 0; I_DATA = 4'd2;
        #1 CLOCK = 1;
        #1 CLOCK = 0; I_DATA = 4'd3;
        #1 CLOCK = 1;
        #1 $display("");
        $display("--- get 0 1 2 3 4 5 6 -- answers have to be 3 2 1 0 0 3 2 ---");
        CLOCK = 0; COMMAND = 2'd3;
        #1 CLOCK = 1;
        #1 CLOCK = 0; INDEX = 3'd1;
        #1 CLOCK = 1;
        #1 CLOCK = 0; INDEX = 3'd2;
        #1 CLOCK = 1;
        #1 CLOCK = 0; INDEX = 3'd3;
        #1 CLOCK = 1;
        #1 CLOCK = 0; INDEX = 3'd4;
        #1 CLOCK = 1;
        #1 CLOCK = 0; INDEX = 3'd5;
        #1 CLOCK = 1;
        #1 CLOCK = 0; INDEX = 3'd6;
        #1 CLOCK = 1;
        #1 $display("");
        $display("--- pop * 7 -- answers have to be 3 2 1 0 0 3 2 ---");
        CLOCK = 0; COMMAND = 2'd2;
        #1 CLOCK = 1;
        #1 CLOCK = 0; 
        #1 CLOCK = 1;
        #1 CLOCK = 0; 
        #1 CLOCK = 1;
        #1 CLOCK = 0; 
        #1 CLOCK = 1;
        #1 CLOCK = 0; 
        #1 CLOCK = 1;
        #1 CLOCK = 0; 
        #1 CLOCK = 1;
        #1 CLOCK = 0; 
        #1 CLOCK = 1;
    end

endmodule;

module rs_trigger_tb;
    reg R;
    reg S;
    reg CLK = 0;
    wire Q; wire not_Q;
    rs_trigger rs( 
        .Q(Q),
        .not_Q(not_Q),
        .R(R),
        .CLK(CLK),
        .S(S)
    );

    /*initial begin
        $monitor("%t      R: %0d, S: %0d, CLK: %0d,  Q: %b, notQ: %b", $time, R, S, CLK, Q, not_Q);

        $display("rs");
        $display("");
        #1 R = 1; S = 0;
        #1 CLK = 1;
        #1 CLK = 0;
        $display("");
        #1 R = 0; S = 1;
        #1 CLK = 1;
        #1 CLK = 0;
        $display("");
        #1 R = 0; S = 0;
        #1 CLK = 1;
        #1 CLK = 0;
        $display("");
        #1 R = 1; S = 0;
        #1 CLK = 1;
        #1 CLK = 0;
        $display("");
        #1 R = 0; S = 0;
        #1 CLK = 1;
        #1 CLK = 0;
        $display("");
        #1 R = 1; S = 1;
        #1 CLK = 1;
        #1 CLK = 0;
    end*/
endmodule

module greater_tb;
    reg A;
    reg B;
    wire G;

    greater great (
        .A(A), 
        .B(B), 
        .G(G)
    );

    /*initial begin
        $monitor("%t      A: %0d, B: %0d, G: %0d", $time, A, B, G);

        $display("greater");
        #1 A = 1; B = 1;
        #1 A = 0; B = 0;
        #1 A = 0; B = 1;
        #1 A = 1; B = 0;
    end*/

endmodule

module eq_tb;
    reg A;
    reg B;
    wire Q;

    eq eq (
        .A(A), 
        .B(B), 
        .Q(Q)
    );

    /*initial begin
        $monitor("%t      A: %0d, B: %0d, Q: %0d", $time, A, B, Q);

        $display("equal");
        #1 A = 1; B = 1;
        #1 A = 0; B = 0;
        #1 A = 0; B = 1;
        #1 A = 1; B = 0;
    end*/

endmodule

module three_to_five_tb;
    reg A1, A2, A3;
    wire Q1, Q2, Q3, Q4, Q5;

    three_to_five TTF (
        .A1(A1), 
        .A2(A2), 
        .A3(A3), 
        .Q1(Q1), 
        .Q2(Q2), 
        .Q3(Q3), 
        .Q4(Q4), 
        .Q5(Q5) 
    );

    /*initial begin
        $monitor("%t      A: %0d%0d%0d, Q: %0d%0d%0d%0d%0d", $time, A3, A2, A1, Q1, Q2, Q3, Q4, Q5);

        $display("three_to_five");
        #1 A1 = 0; A2 = 0; A3 = 0; 
        #1 A1 = 0; A2 = 0; A3 = 1; 
        #1 A1 = 0; A2 = 1; A3 = 0; 
        #1 A1 = 0; A2 = 1; A3 = 1; 
        #1 A1 = 1; A2 = 0; A3 = 0; 
        #1 A1 = 1; A2 = 0; A3 = 1; 
        #1 A1 = 1; A2 = 1; A3 = 0; 
        #1 A1 = 1; A2 = 1; A3 = 1; 
    end*/

endmodule

module five_to_three_tb;
    wire[2:0] A;
    reg Q1, Q2, Q3, Q4, Q5;

    five_to_three FTT (
        .Q1(Q1), 
        .Q2(Q2), 
        .Q3(Q3), 
        .Q4(Q4), 
        .Q5(Q5),
        .A(A) 
    );
/*
    initial begin
        $monitor("%t    Q: %0d%0d%0d%0d%0d, A:%b", $time, Q1, Q2, Q3, Q4, Q5, A);

        $display("five_to_three");
        #1 Q1 = 0; Q2 = 0; Q3 = 0; Q4 = 0; Q5 = 1; 
        #1 Q1 = 0; Q2 = 0; Q3 = 0; Q4 = 1; Q5 = 0; 
        #1 Q1 = 0; Q2 = 0; Q3 = 1; Q4 = 0; Q5 = 0; 
        #1 Q1 = 0; Q2 = 1; Q3 = 0; Q4 = 0; Q5 = 0; 
        #1 Q1 = 1; Q2 = 0; Q3 = 0; Q4 = 0; Q5 = 0; 
    end
*/
endmodule

module by_module_5_tb;
    reg[2:0] A;
    reg[2:0] Q;

    by_module_5 bm5 (
        .A(A), 
        .Q(Q)
    );
/*
    initial begin
        $monitor("%t    A: %b, Q:%b", $time, A, Q);

        $display("by_module_5");
        #1 A = 3'd0;
        #1 A = 3'd1;
        #1 A = 3'd2;
        #1 A = 3'd3;
        #1 A = 3'd4;
        #1 A = 3'd5;
        #1 A = 3'd6;
        #1 A = 3'd7;
    end*/

endmodule

module sync_d_trigger_tb;
    wire Q, not_Q;
    reg CLK, D;

    sync_d_trigger d_tr (
        .CLK(CLK), 
        .D(D), 
        .Q(Q), 
        .not_Q(not_Q)
    );

    /*initial begin
        $monitor("%t    CLK: %0d, D: %0d  Q: %d  not_Q: %d", $time, CLK, D, Q, not_Q);

        $display("sync_d_trigger");
        #1 D = 1;
        #1 CLK = 1;
        #1 CLK = 0;
        #1 D = 0;
        #1 CLK = 1;
    end*/

endmodule

module d_trigger_reset_tb;
    wire Q, not_Q, C, D;
    reg CLK, DATA, RESET;

    d_trigger_reset d_tr_r (
        .CLK(CLK), 
        .DATA(DATA),
        .RESET(RESET), 
        .Q(Q), 
        .not_Q(not_Q)
    );

    /*initial begin
        $monitor("%t    CLK: %0d, DATA: %0d, RESET: %0d, Q: %d,  not_Q: %d", $time, CLK, DATA, RESET, Q, not_Q);

        $display("d_trigger_reset");
        #1 DATA = 0; RESET = 0; 
        #1 CLK = 1;
        #1 CLK = 0;
        #1 RESET = 1;
        #1 RESET = 0; DATA = 1;
        #1 CLK = 1;
        #1 RESET = 1;
    end*/

endmodule

module mem_four_bit_tb;
    wire [3:0] OUT_DATA ;
    reg [3:0] DATA;
    reg CLK, RESET;

    mem_four_bit mfb (
        .CLK(CLK), 
        .DATA(DATA),
        .RESET(RESET), 
        .OUT_DATA(OUT_DATA)
    );
/*
    initial begin
        $monitor("%t    CLK: %0d, DATA: %B, RESET: %0d, OUT_DATA: %B", $time, CLK, DATA, RESET, OUT_DATA);

        $display("mem_four_bit");
        #1 DATA = 4'd0; RESET = 0; 
        #1 CLK = 1;
        #1 CLK = 0;
        #1 DATA = 4'd2;
        #1 CLK = 1;
        #1 CLK = 0;
        #1 DATA = 4'd3;
        #1 CLK = 1;
        #1 CLK = 0;
        #1 RESET = 1;
    end*/

endmodule

module demux_tb;
    reg D;
    reg [2:0] ADDR;
    wire Q1, Q2, Q3, Q4, Q5;

    demux dem (
        .D(D), 
        .ADDR(ADDR), 
        .Q1(Q1), 
        .Q2(Q2), 
        .Q3(Q3), 
        .Q4(Q4), 
        .Q5(Q5) 
    );
/*
    initial begin
        $monitor("%t      ADDR: %b, D: %0d, Q: %0d%0d%0d%0d%0d", $time, ADDR, D, Q1, Q2, Q3, Q4, Q5);

        $display("demux");
        #1 ADDR = 3'd0; D = 0;
        #1 ADDR = 3'd4; D = 0;
        #1 D = 1;
        #1 D = 0; ADDR = 3'd0;
        #1 D = 1;
        #1 D = 0; ADDR = 3'd2;
        #1 D = 1;
        #1 D = 0; ADDR = 3'd7;
        #1 D = 1;
    end*/

endmodule

module mux_tb;
    reg [3:0] Q1, Q2, Q3, Q4, Q5;
    reg [2:0] ADDR;
    wire [3:0] Q;

    mux mu (
        .Q(Q), 
        .ADDR(ADDR), 
        .Q1(Q1), 
        .Q2(Q2), 
        .Q3(Q3), 
        .Q4(Q4), 
        .Q5(Q5) 
    );
/*
    initial begin
        $monitor("%t      ADDR: %b, Q1 = %B, Q2 = %B, Q3 = %B, Q4 = %B, Q5 = %B, Q: %B", $time, ADDR, Q1, Q2, Q3, Q4, Q5, Q);

        $display("mux");

        #1  Q1 = 4'd1; Q2 = 4'd2; Q3 = 4'd3; Q4 = 4'd4; Q5 = 4'd5; ADDR = 3'd0;
        #1 ADDR = 3'd1;
        #1 ADDR = 3'd2;
        #1 ADDR = 3'd3;
        #1 ADDR = 3'd4;
        #1 ADDR = 3'd5;
        #1 ADDR = 3'd6;
        #1 ADDR = 3'd7;
    end*/

endmodule

module four_and_one_tb;
    reg Q2;
    reg [3:0] Q1;
    wire [3:0] Q;

    four_and_one fao (
        .Q(Q), 
        .Q2(Q2),
        .Q1(Q1)
    );
/*
    initial begin
        $monitor("%t      A: %b, B: %0d, Q: %B", $time, Q1, Q2, Q);

        $display("four_and_one");
        #1 Q1 = 3'd4; Q2 = 0;
        #1 Q2 = 1;
    end*/

endmodule

module four_or_four_tb;
    reg [3:0] Q2;
    reg [3:0] Q1;
    wire [3:0] Q;

    four_or_four fof (
        .Q(Q), 
        .Q2(Q2),
        .Q1(Q1)
    );

    /*initial begin
        $monitor("%t      A: %b, B: %b, Q: %B", $time, Q1, Q2, Q);

        $display("four_or_four");
        #1 Q1 = 3'd4; Q2 = 3'd0;
        #1 Q2 = 3'd1;
        #1 Q2 = 3'd6;
    end*/

endmodule

module commands_tb;
    reg [1:0] COMMAND;
    wire PUSH, POP, GET;

    commands commands_ (
        .COMMAND(COMMAND),
        .POP(POP),
        .PUSH(PUSH),
        .GET(GET)
    );
/*
    initial begin
        $monitor("%t      COMMAND: %b, PUSH: %0D, POP: %0D, GET: %0D", $time, COMMAND, PUSH, POP, GET);

        $display("commands");
        #1 COMMAND = 2'd0;
        #1 COMMAND = 2'd1;
        #1 COMMAND = 2'd2;
        #1 COMMAND = 2'd3;
    end*/

endmodule

module summator_tb;
    reg A, B, OST;
    wire SUM, OST_AFTER;

    summator summ (
        .A(A),
        .B(B),
        .OST(OST),
        .SUM(SUM), 
        .OST_AFTER(OST_AFTER)
    );

    /*initial begin
        $monitor("%t      A: %0D, B: %0D, OST: %0D, SUM: %0D, OST_AFTER: %0D", $time, A, B, OST, SUM, OST_AFTER);

        $display("summator");
        #1 A = 1'd0; B = 1'd0; OST = 1'd0;  
        #1 A = 1'd0; B = 1'd0; OST = 1'd1;
        #1 A = 1'd0; B = 1'd1; OST = 1'd0;   
        #1 A = 1'd1; B = 1'd0; OST = 1'd0;   
        #1 A = 1'd1; B = 1'd1; OST = 1'd0;
        #1 A = 1'd0; B = 1'd0; OST = 1'd1;
        #1 A = 1'd0; B = 1'd1; OST = 1'd1;
        #1 A = 1'd1; B = 1'd0; OST = 1'd1;
        #1 A = 1'd1; B = 1'd1; OST = 1'd1;          
    end*/

endmodule

module addition_tb;
    reg [2:0] A, B;
    wire [2:0] RESULT;

    addition add (
        .A(A),
        .B(B),
        .RESULT(RESULT)
    );
/*
    initial begin
        $monitor("%t      A: %B, B: %B, RESULT: %B", $time, A, B, RESULT);

        $display("summator");
        #1 A = 3'd1; B = 3'd1; 
        #1 A = 3'd5; B = 3'd1;  
        #1 A = 3'd0; B = 3'd4; 
        #1 A = 3'd1; B = 3'd3; 
        #1 A = 3'd7; B = 3'd1; 
    end*/

endmodule

module substraction_tb;
    reg [2:0] A, B;
    wire [2:0] RESULT;

    substraction sub (
        .A(A),
        .B(B),
        .RESULT(RESULT)
    );
/*
    initial begin
        $monitor("%t      A: %B, B: %B, RESULT: %B", $time, A, B, RESULT);

        $display("summator");
        #1 A = 3'd1; B = 3'd1; 
        #1 A = 3'd5; B = 3'd1;  
        #1 A = 3'd0; B = 3'd3; 
        #1 A = 3'd1; B = 3'd3; 
        #1 A = 3'd7; B = 3'd1; 
    end
*/
endmodule

module comp_tb;
    reg [2:0] A, B;
    wire A_is_greater, B_is_greater;

    comp comparator (
        .A(A),
        .B(B),
        .A_is_greater(A_is_greater), 
        .B_is_greater(B_is_greater)
    );
/*
    initial begin
        $monitor("%t      A: %B, B: %B, A is Greater: %0d, B is Greater: %0d", $time, A, B, A_is_greater, B_is_greater);

        $display("comparator");
        #1 A = 3'd1; B = 3'd4; 
        #1 A = 3'd5; B = 3'd1;  
        #1 A = 3'd0; B = 3'd3; 
        #1 A = 3'd1; B = 3'd3; 
        #1 A = 3'd7; B = 3'd1; 
    end*/

endmodule

module get_pos_for_get_tb;
    reg [2:0] HEAD, INDEX;
    wire [2:0] RESULT;

    get_pos_for_get gpfg (
        .HEAD(HEAD),
        .INDEX(INDEX),
        .RESULT(RESULT)
    );

  /*  initial begin
        $monitor("%t      HEAD: %B, INDEX: %B, RESULT: %B", $time, HEAD, INDEX, RESULT);

        $display("get_pos_for_get");
        
        #1 HEAD = 3'd1; INDEX = 3'd4; 
        #1 HEAD = 3'd5; INDEX = 3'd1; 
        #1 HEAD = 3'd7; INDEX = 3'd0; 
        #1 HEAD = 3'd5; INDEX = 3'd2; 
        #1 HEAD = 3'd4; INDEX = 3'd6; 
    end
*/
endmodule

module change_number_tb;
    reg [2:0] A;
    wire [2:0] RESULT1, RESULT2;

    change_number cn (
        .A(A), 
        .RESULT1(RESULT1),
        .RESULT2(RESULT2)
    );
/*
    initial begin
        $monitor("%t      A: %B, RESULT1: %B, RESULT2: %B", $time, A, RESULT1, RESULT2);

        $display("change_number_tb");
        
        #1 A = 3'd1;
        #1 A = 3'd2;
        #1 A = 3'd5;
        #1 A = 3'd7;
    end
*/
endmodule

module d_trigger_tb;
    wire Q, not_Q;
    reg CLK, DATA, RESET;

    d_trigger d_tr (
        .CLK(CLK), 
        .DATA(DATA), 
        .RESET(RESET),
        .Q(Q), 
        .not_Q(not_Q)
    );
/*
    initial begin
        $monitor("%t    CLK: %0d, RESET: %0D, DATA: %0d,  Q: %d , not_Q: %d", $time, CLK, RESET, DATA, Q, not_Q);

        $display("d_trigger");
        #1 RESET = 1; CLK = 0; DATA = 0;
        #1 RESET = 0; DATA = 1;
        #1 CLK = 1;
        #1 CLK = 0;
        #1 DATA = 0;
        #1 CLK = 1;
        #1 CLK = 0;
        #1 CLK = 1;
        #1 DATA = 1; RESET = 1;
        #1 CLK = 1;
    end
*/
endmodule

module mem_3_bit_tb;
    wire [2:0] RESULT;
    reg [2:0] DATA;
    reg PUSH, POP, CLOCK, RESET;

    mem_3_bit M3B (
        .CLOCK(CLOCK), 
        .DATA(DATA), 
        .RESET(RESET),
        .PUSH(PUSH), 
        .POP(POP),
        .RESULT(RESULT)
    );

 /*   initial begin
        $monitor("%t    CLK: %0d, PUSH: %0d, POP: %0d, RESET: %0D, DATA: %B,  RESULT: %B", $time, CLOCK, PUSH, POP, RESET, DATA, RESULT);

        $display("mem_3_bit");
        #1 RESET = 1; CLOCK = 0; DATA = 3'd0; PUSH = 0; POP = 0;
        #1 RESET = 0; DATA = 3'd5; PUSH = 1;
        #1 CLOCK = 1;
        #1 CLOCK = 0;
        #1 POP = 1; PUSH = 0;
        #1 CLOCK = 1;
        #1 CLOCK = 0;
        #1 DATA = 3'd0;
        #1 CLOCK = 1;
        #1 CLOCK = 0;
    end*/

endmodule

module totalizer_tb;
    wire [2:0] POINTER;
    reg PUSH, POP, CLOCK, RESET;

    totalizer total (
        .CLOCK(CLOCK), 
        .RESET(RESET),
        .PUSH(PUSH), 
        .POP(POP),
        .POINTER(POINTER)
    );
/*
    initial begin
        $monitor("%t    CLK: %0d, PUSH: %0d, POP: %0d, RESET: %0D, POINTER: %B", $time, CLOCK, PUSH, POP, RESET, POINTER);

        $display("totalizer");
        #1 RESET = 1; CLOCK = 0; PUSH = 0; POP = 0;
        #1 RESET = 0; PUSH = 1;
        #1 CLOCK = 1;
        #1 CLOCK = 0;
        #1 CLOCK = 1;
        #1 CLOCK = 0;
        #1 CLOCK = 0;
        #1 POP = 1; PUSH = 0;
        #1 CLOCK = 1;
        #1 CLOCK = 0;
    end
*/
endmodule

module number_tb;
    wire [2:0] ADDR;
    reg [2:0] INDEX;
    reg PUSH, POP, CLOCK, RESET, GET;

    number num (
        .CLOCK(CLOCK), 
        .RESET(RESET),
        .PUSH(PUSH), 
        .POP(POP),
        .GET(GET),
        .INDEX(INDEX),
        .ADDR(ADDR)
    );
/*
    initial begin
        $monitor("%t    CLK: %0d, INDEX: %B, PUSH: %0d, POP: %0d, GET: %0d,  RESET: %0D, ADDR: %B", $time, CLOCK, INDEX, PUSH, POP, GET, RESET, ADDR);

        $display("number");
        #1 RESET = 1; CLOCK = 0; PUSH = 0; POP = 0; GET = 0; INDEX = 3'd0;
        #1 RESET = 0; PUSH = 1;
        #1 CLOCK = 1;
        #1 CLOCK = 0;
        #1 CLOCK = 1;
        #1 CLOCK = 0;
        #1 POP = 1; PUSH = 0;
        #1 CLOCK = 1;
        #1 CLOCK = 0;
        #1 POP = 0; GET = 1;
        #1 CLOCK = 1;
        #1 CLOCK = 0;
        #1 INDEX = 3'd1;
        #1 CLOCK = 1;
        #1 CLOCK = 0;
        #1 INDEX = 3'd2;
        #1 CLOCK = 1;
        #1 CLOCK = 0;
        #1 INDEX = 3'd3;
        #1 CLOCK = 1;
        #1 CLOCK = 0;
        #1 INDEX = 3'd4;
        #1 CLOCK = 1;
        #1 CLOCK = 0;
        #1 INDEX = 3'd5;
        #1 CLOCK = 1;
        #1 CLOCK = 0;
    end
*/
endmodule