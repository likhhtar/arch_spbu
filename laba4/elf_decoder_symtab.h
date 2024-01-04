#ifndef ELF_DECODER_H
#define ELF_DECODER_H

#include <vector>
#include <cstring>
#include <map>
#include <string>
#include <iostream>
#include <fstream>

typedef struct {
    unsigned char      e_mag[4];
    unsigned char      e_class;
    unsigned char      e_data;
    unsigned char      e_version1;
    unsigned char      e_osabi;
    unsigned char      e_abiversion;
    unsigned char      e_pad[7];
    unsigned short     e_type;
    unsigned short     e_machine;
    unsigned int       e_version2;
    unsigned int       e_entry;
    unsigned int       e_phoff;
    unsigned int       e_shoff;
    unsigned int       e_flags;
    unsigned short     e_ehsize;
    unsigned short     e_phentsize;
    unsigned short     e_phnum;
    unsigned short     e_shentsize;
    unsigned short     e_shnum;
    unsigned short     e_shstrndx;
} Elf32_Ehdr;


typedef struct {
    unsigned int	sh_name;
    unsigned int	sh_type;
    unsigned int	sh_flags;
    unsigned int	sh_addr;
    unsigned int	sh_offset;
    unsigned int	sh_size;
    unsigned int	sh_link;
    unsigned int	sh_info;
    unsigned int	sh_addralign;
    unsigned int	sh_entsize;
} Elf32_Shdr;

typedef struct {
    unsigned int	st_name;
    unsigned int	st_value;
    unsigned int	st_size;
    unsigned char	st_info;
    unsigned char	st_other;
    unsigned short 	st_shndx;
} Elf32_Sym;



bool check_header(Elf32_Ehdr* header);

int ELF32_ST_BIND(int i);
int ELF32_ST_TYPE(int i);
int ELF32_ST_VISIBILITY(int o);

std::string get_index(unsigned short st_shndx);

void print_symbol(FILE * f, Elf32_Sym *symbol, int i, char *symbols_names);
void print_symtab(FILE * f, Elf32_Sym* symbols, Elf32_Shdr *symtab_section, char *symbols_names);

std::map<unsigned int, std::string> make_names(Elf32_Sym * symbols, char* symbols_names,  Elf32_Shdr *symtab_section);



#endif //ELF_DECODER_H