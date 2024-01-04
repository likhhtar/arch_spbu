module stack_structural_easy(
    output wire[3:0] O_DATA,
    input wire RESET, 
    input wire CLK, 
    input wire[1:0] COMMAND, 
    input wire[2:0] INDEX,
    input wire[3:0] I_DATA
    ); 

    wire push, pop, get;
    commands f1(push, pop, get, COMMAND);

    wire [2:0] addr;
    number f2(addr, push, pop, get, CLK, RESET, INDEX);

    wire C;
    and (C, push, CLK);

    wire Q1, Q2, Q3, Q4, Q5;
    demux f3(Q1, Q2, Q3, Q4, Q5, addr, C);

    wire [3:0] D1, D2, D3, D4, D5;
    mem_four_bit f4(D1, Q1, I_DATA, RESET);
    mem_four_bit f5(D2, Q2, I_DATA, RESET);
    mem_four_bit f6(D3, Q3, I_DATA, RESET);
    mem_four_bit f7(D4, Q4, I_DATA, RESET);
    mem_four_bit f8(D5, Q5, I_DATA, RESET);

    mux f9(O_DATA, D1, D2, D3, D4, D5, addr);
endmodule

module rs_trigger ( 
    output wire Q,
    output wire not_Q,
    input wire R,
    input wire CLK,
    input wire S
    );

    wire R_CLK, S_CLK;
    and (R_CLK, R, CLK);
    and (S_CLK, S, CLK);

    nor (not_Q, S_CLK, Q);
    nor (Q, R_CLK, not_Q);
endmodule

module greater ( 
    output wire G,
    input wire A,
    input wire B
    );

    wire not_B;
    not (not_B, B);
    and (G, A, not_B);
endmodule

module eq ( 
    output wire Q,
    input wire A,
    input wire B
    );

    xnor (Q, A, B);
endmodule

module three_to_five (
    output wire Q1,
    output wire Q2,
    output wire Q3,
    output wire Q4,
    output wire Q5,
    input wire A1,
    input wire A2, 
    input wire A3
    );

    wire not_A1, not_A2, not_A3;
    not (not_A1, A1);
    not (not_A2, A2);
    not (not_A3, A3);

    wire A1_A2, A1_not_A2, not_A1_A2, not_A1_not_A2;
    wire A1_A2_A3, A1_not_A2_A3, not_A1_A2_A3, not_A1_not_A2_A3;
    wire A1_A2_not_A3, A1_not_A2_not_A3, not_A1_A2_not_A3, not_A1_not_A2_not_A3;

    and (A1_A2, A1, A2);
    and (A1_not_A2, A1, not_A2);
    and (not_A1_A2, not_A1, A2);
    and (not_A1_not_A2, not_A1, not_A2);

    and (A1_A2_A3, A1_A2, A3);
    and (A1_not_A2_A3, A1_not_A2, A3);
    and (not_A1_A2_A3, not_A1_A2, A3);
    and (not_A1_not_A2_A3, not_A1_not_A2, A3);

    and (A1_A2_not_A3, A1_A2, not_A3);
    and (A1_not_A2_not_A3, A1_not_A2, not_A3);
    and (not_A1_A2_not_A3, not_A1_A2, not_A3);
    and (not_A1_not_A2_not_A3, not_A1_not_A2, not_A3);

    or(Q1, not_A1_not_A2_not_A3, A1_not_A2_A3);
    or(Q2, not_A1_not_A2_A3, A1_A2_not_A3);
    or(Q3, not_A1_A2_not_A3, A1_A2_A3);
    assign Q4 = not_A1_A2_A3;
    assign Q5 = A1_not_A2_not_A3;

endmodule

module five_to_three (
    output wire[2:0] A,
    input wire Q1,
    input wire Q2,
    input wire Q3,
    input wire Q4,
    input wire Q5
    );  

    wire Q24, Q34;
    or (Q24, Q2, Q4);
    or (Q34, Q4, Q3);

    assign A[0] = Q24;
    assign A[1] = Q34;
    assign A[2] = Q5;


endmodule

module by_module_5 (
    output wire[2:0] Q,
    input wire[2:0] A
    );  

    reg Q1, Q2, Q3, Q4, Q5;
    three_to_five ttf( Q1, Q2, Q3, Q4, Q5,  A[2], A[1], A[0]);
    five_to_three ftt(Q, Q1, Q2, Q3, Q4, Q5);
endmodule

module sync_d_trigger (
    output wire Q,
    output wire not_Q,
    input wire CLK, 
    input wire D
    );  

    wire R;
    not (R, D);
    rs_trigger rs(Q, not_Q, R, CLK, D);
endmodule

module d_trigger_reset (
    output wire Q,
    output wire not_Q,
    input wire CLK, 
    input wire DATA, 
    input wire RESET
    );  

    wire C, D;
    wire not_R;
    or (C, CLK, RESET);
    not (not_R, RESET);
    and (D, DATA, not_R);
    sync_d_trigger d_tr(Q, not_Q, C, D);
endmodule


module mem_four_bit (
    output wire[3:0] OUT_DATA,
    input wire CLK,
    input wire[3:0] DATA,
    input wire RESET
    );  

    d_trigger_reset d1(OUT_DATA[0],,CLK, DATA[0], RESET);
    d_trigger_reset d2(OUT_DATA[1],,CLK, DATA[1], RESET);
    d_trigger_reset d3(OUT_DATA[2],,CLK, DATA[2], RESET);
    d_trigger_reset d4(OUT_DATA[3],,CLK, DATA[3], RESET);
endmodule

module demux(
    output wire Q1,
    output wire Q2,
    output wire Q3,
    output wire Q4,
    output wire Q5,
    input wire [2:0] ADDR,
    input wire D
    );

    wire Q_1, Q_2, Q_3, Q_4, Q_5;
    three_to_five ttf( Q_1, Q_2, Q_3, Q_4, Q_5,  ADDR[2], ADDR[1], ADDR[0]);
    and (Q1, Q_1, D);
    and (Q2, Q_2, D);
    and (Q3, Q_3, D);
    and (Q4, Q_4, D);
    and (Q5, Q_5, D);
endmodule

module four_and_one(
    output wire [3:0] Q,
    input wire [3:0] Q1,
    input wire Q2
    );

    and (Q[0], Q1[0], Q2);
    and (Q[1], Q1[1], Q2);
    and (Q[2], Q1[2], Q2);
    and (Q[3], Q1[3], Q2);
endmodule

module four_or_four(
    output wire [3:0] Q,
    input wire [3:0] Q1,
    input wire [3:0] Q2
    );

    or (Q[0], Q1[0], Q2[0]);
    or (Q[1], Q1[1], Q2[1]);
    or (Q[2], Q1[2], Q2[2]);
    or (Q[3], Q1[3], Q2[3]);
endmodule

module mux(
    output wire [3:0] Q,
    input wire [3:0] Q1,
    input wire [3:0] Q2,
    input wire [3:0] Q3,
    input wire [3:0] Q4,
    input wire [3:0] Q5,
    input wire [2:0] ADDR
    );

    wire Q_1, Q_2, Q_3, Q_4, Q_5;
    three_to_five ttf( Q_1, Q_2, Q_3, Q_4, Q_5,  ADDR[2], ADDR[1], ADDR[0]);

    wire [3:0] Q12, Q34, Q345;
    wire [3:0] A1, A2, A3, A4, A5;

    four_and_one f1(A1, Q1, Q_1);
    four_and_one f2(A2, Q2, Q_2);
    four_and_one f3(A3, Q3, Q_3);
    four_and_one f4(A4, Q4, Q_4);
    four_and_one f5(A5, Q5, Q_5);

    four_or_four f6(Q12, A1, A2);
    four_or_four f7(Q34, A3, A4);
    four_or_four f8(Q345, Q34, A5);
    four_or_four f9(Q, Q345, Q12);

endmodule

module commands(
    output wire PUSH,
    output wire POP,
    output wire GET,
    input wire [1:0] COMMAND
    );

    wire not_one, not_zero;
    not (not_zero, COMMAND[0]);
    not (not_one, COMMAND[1]);
    and (PUSH, COMMAND[0], not_one);
    and (POP, COMMAND[1], not_zero);
    and (GET, COMMAND[0], COMMAND[1]);

endmodule

module summator (
    output wire SUM, 
    output wire OST_AFTER,
    input wire A,
    input wire B, 
    input wire OST
    );

    wire fir_sum, fir_ost, sec_ost, sec_sum;
    xor (fir_sum, A, B);
    xor (SUM, fir_sum, OST);

    and (fir_ost, A, B);
    and (sec_ost, fir_sum, OST);

    xor (OST_AFTER, sec_ost, fir_ost);
endmodule

module addition (
    output wire [2:0] RESULT,
    input wire [2:0] A, 
    input wire [2:0] B
    );

    wire fir_ost, sec_ost;

    summator f1(RESULT[0], fir_ost, A[0], B[0], 1'd0);
    summator f2(RESULT[1], sec_ost, A[1], B[1], fir_ost);
    summator f3(RESULT[2], , A[2], B[2], sec_ost);
endmodule

module substraction (
    output wire [2:0] RESULT,
    input wire [2:0] A, 
    input wire [2:0] B
    );

    wire fir_ost, sec_ost;
    wire not_B1, not_B2, not_B3;

    not (not_B1, B[0]);
    not (not_B2, B[1]);
    not (not_B3, B[2]);

    summator f1(RESULT[0], fir_ost, A[0], not_B1, 1'd1);
    summator f2(RESULT[1], sec_ost, A[1], not_B2, fir_ost);
    summator f3(RESULT[2], , A[2], not_B3, sec_ost);
endmodule

module comp(
    output wire A_is_greater,
    output wire B_is_greater,
    input wire [2:0] A, 
    input wire [2:0] B
    );

    wire eq1, eq2, eq3, gr1, gr2, gr3;
    eq f1(eq1, A[0], B[0]);
    eq f2(eq2, A[1], B[1]);
    eq f3(eq3, A[2], B[2]);

    greater f4(gr1, A[0], B[0]);
    greater f5(gr2, A[1], B[1]);
    greater f6(gr3, A[2], B[2]);

    wire g1, g2, g3, g4, g5;
    or (g1, eq1, gr1);
    and (g2, g1, eq2);
    or (g3, g2, gr2);
    and (g4, g3, eq3);
    or (g5, g4, gr3);

    assign A_is_greater = g5;
    not (B_is_greater, g5);
endmodule

module get_pos_for_get (
    output wire [2:0] RESULT,
    input wire [2:0] HEAD, 
    input wire [2:0] INDEX
    );

    wire [2:0] head_by_module, index_by_module;
    by_module_5 f1(head_by_module, HEAD);
    by_module_5 f2(index_by_module, INDEX);

    wire  A_is_greater,  B_is_greater;
    comp f3(A_is_greater, B_is_greater, head_by_module, index_by_module);

    wire [2:0] sub1, sub2, add;
    substraction f4(sub1, head_by_module, index_by_module);
    substraction f5(sub2, 3'd5, index_by_module);
    addition f6(add, head_by_module, sub2);

    wire n1, n2, n3, n4, n5, n6;
    and (n1, A_is_greater, sub1[0]);
    and (n2, A_is_greater, sub1[1]);
    and (n3, A_is_greater, sub1[2]);
    and (n4, B_is_greater, add[0]);
    and (n5, B_is_greater, add[1]);
    and (n6, B_is_greater, add[2]);

    wire[2:0] RES;
    or (RES[0], n1, n4);
    or (RES[1], n2, n5);
    or (RES[2], n3, n6);
    by_module_5 f7(RESULT, RES);
endmodule

module plus_one (
    output wire [2:0] RESULT,
    input wire [2:0] A
    );

    wire [2:0] add, mod;
    by_module_5 f0(mod, A);
    addition f1(add, mod, 3'd1);
    by_module_5 f2(RESULT, add);
endmodule

module change_number (
    output wire [2:0] RESULT1,
    output wire [2:0] RESULT2,
    input wire [2:0] A
    );

    plus_one f0(RESULT1, A);

    get_pos_for_get f1(RESULT2, A, 3'd1);
endmodule

module d_trigger (
    output wire Q,
    output wire not_Q,
    input wire CLK,
    input wire DATA, 
    input wire RESET 
    );

    wire not_R, D, C;
    not (not_R, RESET);
    and (D, DATA, not_R);
    or (C, CLK, RESET);

    wire Q1, not_C, C2;
    sync_d_trigger f1(Q1,, C, D);
    not (not_C, C);
    or (C2, not_C, RESET);
    sync_d_trigger f2(Q, not_Q, C2, Q1);
endmodule

module mem_3_bit (
    output wire [2:0] RESULT,
    input wire [2:0] DATA,
    input wire PUSH, 
    input wire POP, 
    input wire CLOCK,
    input wire RESET 
    );

   wire C1, C2, C3;
   and (C1, CLOCK, POP);
   and (C2, CLOCK, PUSH);
   xor (C3, C1, C2);

   d_trigger f1(RESULT[0], , C3, DATA[0], RESET);
   d_trigger f2(RESULT[1], , C3, DATA[1], RESET);
   d_trigger f3(RESULT[2], , C3, DATA[2], RESET);
endmodule

module totalizer (
    output wire [2:0] POINTER,
    input wire PUSH, 
    input wire POP, 
    input wire CLOCK,
    input wire RESET 
    );

   reg [2:0] data, mem, plus, minus, pop_num, push_num;

   change_number f1(plus, minus, mem);

   and (push_num[0], plus[0], PUSH);
   and (push_num[1], plus[1], PUSH);
   and (push_num[2], plus[2], PUSH);

   and (pop_num[0], minus[0], POP);
   and (pop_num[1], minus[1], POP);
   and (pop_num[2], minus[2], POP);

   or (data[0], push_num[0], pop_num[0]);
   or (data[1], push_num[1], pop_num[1]);
   or (data[2], push_num[2], pop_num[2]);

   mem_3_bit f2(mem, data, PUSH, POP, CLOCK, RESET);

   assign POINTER = mem;

endmodule

module number (
    output wire [2:0] ADDR,
    input wire PUSH, 
    input wire POP, 
    input wire GET, 
    input wire CLOCK,
    input wire RESET,
    input wire [2:0] INDEX
    );

    wire [2:0] total, push_num, get_num;
    totalizer f1(total, PUSH, POP, CLOCK, RESET);
    plus_one f2(push_num, total);
    get_pos_for_get f3(get_num, total, INDEX);

    wire [2:0] pop_, push_, get_;
    and (pop_[0], POP, total[0]);
    and (pop_[1], POP, total[1]);
    and (pop_[2], POP, total[2]);

    and (push_[0], PUSH, push_num[0]);
    and (push_[1], PUSH, push_num[1]);
    and (push_[2], PUSH, push_num[2]);

    and (get_[0], GET, get_num[0]);
    and (get_[1], GET, get_num[1]);
    and (get_[2], GET, get_num[2]);

    or (ADDR[0], get_[0], push_[0], pop_[0]);
    or (ADDR[1], get_[1], push_[1], pop_[1]);
    or (ADDR[2], get_[2], push_[2], pop_[2]);
endmodule