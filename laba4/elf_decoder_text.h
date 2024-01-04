#ifndef ELF_DECODER_TEXT_H
#define ELF_DECODER_TEXT_H

#include "elf_decoder_symtab.h"

typedef struct {
    unsigned char func7;
    unsigned char rs2;
    unsigned char rs1;
    unsigned char func3;
    unsigned char rd;
    unsigned char opcode;
    std::string name;
    std::string type;


    unsigned char succ;
    unsigned char pred;
    unsigned char mid;

    unsigned int data;

} program;

std::string get_register(unsigned char reg);

program program_create(unsigned short text1, unsigned short text2);
program get_prog(program &pr);
void print_prog(FILE *f, unsigned int addr, program &pr, std::map<unsigned int, std::string> &symbol_addr_names);

std::string parse_fenct(unsigned char comb);
int expen(unsigned int n, bool tw);

#endif //ELF_DECODER_TEXT_H
