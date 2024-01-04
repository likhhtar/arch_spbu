#include "elf_decoder_text.h"


std::string get_register(unsigned char reg) {
    switch (reg) {
        case 0: return "zero";
        case 1: return "ra";
        case 2: return "sp";
        case 3: return "gp";
        case 4: return "tp";
        case 5: return "t0";
        case 6: return "t1";
        case 7: return "t2";
        case 8: return "s0";
        case 9: return "s1";
        case 10: return "a0";
        case 11: return "a1";
        case 12: return "a2";
        case 13: return "a3";
        case 14: return "a4";
        case 15: return "a5";
        case 16: return "a6";
        case 17: return "a7";
        case 18: return "s2";
        case 19: return "s3";
        case 20: return "s4";
        case 21: return "s5";
        case 22: return "s6";
        case 23: return "s7";
        case 24: return "s8";
        case 25: return "s9";
        case 26: return "s10";
        case 27: return "s11";
        case 28: return "t3";
        case 29: return "t4";
        case 30: return "t5";
        case 31: return "t6";
        default: return "undefined";
    }
}


int expen_pr(program &pr) {
    unsigned short num;
    if (pr.name == "srli" || pr.name == "srai") {
        num = pr.rs2;
    }
    else num = (pr.func7 << 5) | (pr.rs2);

    // Выполняем знаковое расширение
    auto res = static_cast<unsigned int>(num);

    // Если самый старший бит установлен, выполняем расширение
    if (num & (1 << 11)) {
        res |= 0xFFFFF000;  // Знаковое расширение
    }
    return res;
}

int expen(unsigned int n, bool tw) {
    int res;
    if (tw) {
        // Получаем значение, игнорируя старшие 20 бит
        res = n & 0xFFF;
        // Если самый старший бит установлен, выполняем знаковое расширение
        if (n & (1 << 11)) {
            res |= 0xFFFFF000;  // Знаковое расширение
        }
    }
    else{
        // Получаем значение, игнорируя старшие 12 бит
        res = n & 0xFFFFF;

        // Если самый старший бит установлен, выполняем знаковое расширение
        if (n & (1 << 19)) {
            res |= 0xFFF00000;  // Знаковое расширение
        }
    }
    return res;
}


void b_print(FILE *f, unsigned int addr, program &pr, std::map<unsigned int, std::string> &symbol_addr_names) {
    unsigned int x = (((pr.data >> 8) & 0b1111) | (((pr.data >> 25) & 0b111111) << 4)  |
                       (((pr.data >> 7) & 0b1) << 10) | (((pr.data >> 31) & 0b1) << 11)) << 1;

    fprintf(f, "   %05x:\t%08x\t%7s\t%s, %s, 0x%x, <%s>\n", addr, pr.data, pr.name.c_str(),
            get_register(pr.rs1).c_str(), get_register(pr.rs2).c_str(),
            addr + expen(x, 1), symbol_addr_names[addr + expen(x, 1)].c_str());
}

void j_print(FILE *f, unsigned int addr, program &pr, std::map<unsigned int, std::string> &symbol_addr_names) {
    unsigned int x = (((pr.data >> 21) & 0b1111111111) | (((pr.data >> 20) & 0b1)  << 10)  |
                       (((pr.data >> 12) & 0b11111111) << 11) | (((pr.data >> 31) & 0b1) << 19)) << 1;


    fprintf(f, "   %05x:\t%08x\t%7s\t%s, 0x%x <%s>\n", addr, pr.data, pr.name.c_str(),
            get_register(pr.rd).c_str(), expen(addr + x, 0), symbol_addr_names[expen(addr + x, 0)].c_str());
}

std::string fence(unsigned char x) {
    std::string f;
    if (x & 8) f += "i";
    if (x & 4) f += "o";
    if (x & 2) f += "r";
    if (x & 1) f += "w";
    return f;
}

void i_print(FILE *f, unsigned int addr, program &pr) {
    if (pr.name == "jalr" || pr.name[0] == 'l') {
        fprintf(f, "   %05x:\t%08x\t%7s\t%s, %d(%s)\n", addr, pr.data, pr.name.c_str(),
                get_register(pr.rd).c_str(), expen((pr.func7 << 5) | (pr.rs2), 1), get_register(pr.rs1).c_str());
    }
    else if (pr.name == "fence") {
        fprintf(f, "   %05x:\t%08x\t%7s\t%s, %s\n", addr, pr.data, pr.name.c_str(),
                fence(pr.pred).c_str(), fence(pr.succ).c_str());
    }
    else if (pr.opcode == 0b1110011) {
        if (pr.func3 != 0)
            fprintf(f, "   %05x:\t%08x\t%7s\t%s, %d, %s\n", addr, pr.data, pr.name.c_str(),
                    get_register(pr.rd).c_str(), (pr.func7 << 5) | (pr.rs2), get_register(pr.rs1).c_str());
        else
            fprintf(f, "   %05x:\t%08x\t%7s\n", addr, pr.data, pr.name.c_str());

    }
    else {
        fprintf(f, "   %05x:\t%08x\t%7s\t%s, %s, %s\n", addr, pr.data, pr.name.c_str(),
                get_register(pr.rd).c_str(), get_register(pr.rs1).c_str(), std::to_string(expen_pr(pr)).c_str());
    }
}


void print_prog(FILE *f, unsigned int addr, program &pr, std::map<unsigned int, std::string> &symbol_addr_names) {
    if (pr.name == "invalid_operation") {
        fprintf(f, "   %05x:\t%08x\t%-7s\n", addr, pr.data, pr.name.c_str());
        return;
    }
    if (symbol_addr_names.count(addr) > 0) {
        fprintf(f, "\n%08x \t<%s>:\n", addr, symbol_addr_names[addr].c_str());
    }
    if (pr.type == "I") {
        i_print(f, addr, pr);
    }
    else if (pr.type == "R")  {
        fprintf(f, "   %05x:\t%08x\t%7s\t%s, %s, %s\n", addr, pr.data, pr.name.c_str(),
                get_register(pr.rd).c_str(), get_register(pr.rs1).c_str(), get_register(pr.rs2).c_str());
    }
    else if (pr.type == "S")  {
        fprintf(f, "   %05x:\t%08x\t%7s\t%s, %d(%s)\n", addr, pr.data, pr.name.c_str(),
                get_register(pr.rs2).c_str(), expen(pr.rd + (pr.func7 << 5), 1), get_register(pr.rs1).c_str());
    }
    else if (pr.type == "J")  {
        j_print(f, addr, pr, symbol_addr_names);
    }
    else if (pr.type == "B")    {
        b_print(f, addr, pr, symbol_addr_names);
    }
    else if (pr.type == "U") {
        fprintf(f, "   %05x:\t%08x\t%7s\t%s, 0x%x\n", addr, pr.data, pr.name.c_str(),
                get_register(pr.rd).c_str(), expen(pr.data >> 12, 0));
    }
}

program program_create(unsigned short text1, unsigned short text2) {
    program pr;
    pr.data = text1 | (text2 << 16);
    pr.opcode = (text1 & 0b1111111);
    pr.rd = (text1 >> 7) & 0b11111;
    pr.func3 = (text1 >> 12) & 0b111;
    pr.rs1 = ((text1 >> 15) & 0x1) | ((text2 & 0xf) << 1);
    pr.rs2 = (text2 >> 4) & 0b11111;
    pr.func7 = (text2 >> 9);
    pr.succ = (text2 >> 4) & 0b1111;
    pr.pred = (text2 >> 8) & 0b1111;
    pr.mid = text2 >> 12;
    pr.name = "invalid_operation";
    pr.type = "no_type";
    return pr;
}


program get_prog(program &pr) {
    switch (pr.opcode) {
        case 0b0110111:
            pr.type = "U";
            pr.name = "lui";
            break;
        case 0b0010111:
            pr.type = "U";
            pr.name = "auipc";
            break;
        case 0b0010011:
            pr.type = "I";
            switch (pr.func3) {
                case 0:
                    pr.name = "addi";
                    break;
                case 1:
                    if ((pr.func7 >> 1) == 0) pr.name = "slli";
                    break;
                case 2:
                    pr.name = "slti";
                    break;
                case 3:
                    pr.name = "sltiu";
                    break;
                case 4:
                    pr.name = "xori";
                    break;
                case 5:
                    if ((pr.func7 & 3) > 1) break;
                    if ((pr.func7 >> 2) == 0)           pr.name = "srli";
                    else if ((pr.func7 >> 2) == 0b1000) pr.name = "srai";
                    break;
                case 6:
                    pr.name = "ori";
                    break;
                case 7:
                    pr.name = "andi";
                    break;
            }
            break;
        case 0b0110011:
            pr.type = "R";
            if (pr.func7 == 1) {
                switch (pr.func3) {
                    case 0:
                        pr.name = "mul";
                        break;
                    case 1:
                        pr.name = "mulh";
                        break;
                    case 2:
                        pr.name = "mulhsu";
                        break;
                    case 3:
                        pr.name = "mulhu";
                        break;
                    case 4:
                        pr.name = "div";
                        break;
                    case 5:
                        pr.name = "divu";
                        break;
                    case 6:
                        pr.name = "rem";
                        break;
                    case 7:
                        pr.name = "remu";
                        break;
                }
            }
            else if ((pr.func7 & 0b11) == 0) {
                switch (pr.func3) {
                    case 0:
                        if ((pr.func7 & 0b11) != 0) break;
                        if ((pr.func7 >> 2) == 0)           pr.name = "add";
                        else if ((pr.func7 >> 2) == 0b1000) pr.name = "sub";
                        break;
                    case 1:
                        if (pr.func7 != 0) break;
                        pr.name = "sll";
                        break;
                    case 2:
                        if (pr.func7 != 0) break;
                        pr.name = "slt";
                        break;
                    case 3:
                        if (pr.func7 != 0) break;
                        pr.name = "sltu";
                        break;
                    case 4:
                        if (pr.func7 != 0) break;
                        pr.name = "xor";
                        break;
                    case 5:
                        if ((pr.func7 & 3) != 0) break;
                        if ((pr.func7 >> 2) == 0)           pr.name = "srl";
                        else if ((pr.func7 >> 2) == 0b1000) pr.name = "sra";
                        break;
                    case 6:
                        if (pr.func7 != 0) break;
                        pr.name = "or";
                        break;
                    case 7:
                        if (pr.func7 != 0) break;
                        pr.name = "and";
                        break;
                }
            }
            break;
        case 0b1110011:
            pr.type = "I";
            switch (pr.func3) {
                case 0:
                    if (pr.func7 == 0 && pr.func3 == 0 && pr.rs1 == 0) {
                        if (pr.rs2 == 0)        pr.name = "ecall";
                        else if (pr.rs2 == 1)   pr.name = "ebreak";
                        else if (pr.rs2 == 2)   pr.name = "uret";
                    }

                    if ((pr.func7 & 0b11) == 0 && pr.rs2 == 2 && pr.rs1 == 0 && pr.func3 == 0 && pr.rd == 0) {
                        if ((pr.func7 >> 2) == 2)       pr.name = "sret";
                        else if ((pr.func7 >> 2) == 6)  pr.name = "mret";
                    }

                    if ((pr.func7 >> 2) == 2 && (pr.func7 & 3) == 0 && pr.rs2 == 5 && pr.rs1 == 0 && pr.func3 == 0 && pr.rd == 0)
                        pr.name = "wfi";
            }
            break;
        case 0b0000011:
            pr.type = "I";
            switch (pr.func3) {
                case 0:
                    pr.name = "lb";
                    break;
                case 1:
                    pr.name = "lh";
                    break;
                case 2:
                    pr.name = "lw";
                    break;
                case 4:
                    pr.name = "lbu";
                    break;
                case 5:
                    pr.name = "lhu";
                    break;
            }
            break;
        case 0b0100011:
            pr.type = "S";
            switch (pr.func3) {
                case 0:
                    pr.name = "sb";
                    break;
                case 1:
                    pr.name = "sh";
                    break;
                case 2:
                    pr.name = "sw";
                    break;
            }
            break;
        case 0b0001111:
            pr.type = "I";
            if (pr.rd == 0 && pr.rs1 == 0) {
                if (pr.func3 == 0 && pr.mid == 0) pr.name = "fence";
            }
            break;
        case 0b1100111:
            pr.type = "I";
            pr.name = "jalr";
            break;
        case 0b1101111:
            pr.type = "J";
            pr.name = "jal";
            break;
        case 0b1100011:
            pr.type = "B";
            switch (pr.func3) {
                case 0:
                    pr.name = "beq";
                    break;
                case 1:
                    pr.name = "bne";
                    break;
                case 4:
                    pr.name = "blt";
                    break;
                case 5:
                    pr.name = "bge";
                    break;
                case 6:
                    pr.name = "bltu";
                    break;
                case 7:
                    pr.name = "bgeu";
                    break;
            }
            break;
    }

    return pr;
}