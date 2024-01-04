#include "elf_decoder_symtab.h"

using namespace std;

std::string get_type(int x){
    switch (x) {
        case 0:
            return "NOTYPE";
        case 1:
            return "OBJECT";
        case 2:
            return "FUNC";
        case 3:
            return "SECTION";
        case 4:
            return "FILE";
        case 5:
            return "COMMON";
        case 6:
            return "TLS";
        case 10:
            return "LOOS";
        case 12:
            return "HIOS";
        case 13:
            return "LOPROC";
        case 15:
            return "HIPROC";
        default:
            return "";
    }
}

std::string get_binds(int x){
    switch (x) {
        case 0:
            return "LOCAL";
        case 1:
            return "GLOBAL";
        case 2:
            return "WEAK";
        case 10:
            return "LOOS";
        case 12:
            return "HIOS";
        case 13:
            return "LOPROC";
        case 15:
            return "HIPROC";
        default:
            return "";
    }
}

std::string get_visibility(int x){
    switch (x) {
        case 0:
            return "DEFAULT";
        case 1:
            return "INTERNAL";
        case 2:
            return "HIDDEN";
        case 3:
            return "PROTECTED";
        default:
            return "";
    }
}

bool check_header(Elf32_Ehdr* header) {
    if (header->e_mag[0] == 0x7f && header->e_mag[1] == 0x45 && header->e_mag[2] == 0x4c
        && header->e_mag[3] == 0x46 && header->e_class == 0x01 && header->e_data == 0x01
        && header->e_machine == 0xf3 && header->e_version1 == 0x01 && header->e_version2 == 0x01)
        return true;
    return false;
}


int ELF32_ST_BIND(int i) {
    return i >> 4;
}

int ELF32_ST_TYPE(int i) {
    return ((i)&0xf);
}

int ELF32_ST_VISIBILITY(int o) {
    return  ((o)&0x3);
}

string get_index(unsigned short st_shndx) {
    switch (st_shndx) {
        case 0:
            return "UNDEF";
        case 0xfff1:
            return "ABS";
        case 0xfff2:
            return "COMMON";
        case 0xffff:
            return "XINDEX";
        default:
            return std::to_string(st_shndx);
    }
}

void print_symbol(FILE * f, Elf32_Sym *symbol, const int i, char *symbols_names) {
    fprintf(f, "[%4i] 0x%-15X %5i %-8s %-8s %-8s %6s %s\n", i,
           symbol->st_value,
           symbol->st_size,
           get_type(ELF32_ST_TYPE(symbol->st_info)).c_str(),
           get_binds(ELF32_ST_BIND(symbol->st_info)).c_str(),
           get_visibility(ELF32_ST_VISIBILITY(symbol->st_other)).c_str(),
           get_index(symbol->st_shndx).c_str(),
           &symbols_names[symbol->st_name]);
}

void print_symtab(FILE * f, Elf32_Sym* symbols, Elf32_Shdr *symtab_section, char *symbols_names) {
    fprintf(f, "\n.symtab\n");
    fprintf(f, "\nSymbol Value              Size Type     Bind     Vis       Index Name\n");
    for (int i = 0; i * symtab_section->sh_entsize < symtab_section->sh_size; i++) {
        print_symbol(f, &symbols[i], i, symbols_names);
    }
}

std::map<unsigned int, std::string> make_names(Elf32_Sym * symbols, char* symbols_names,  Elf32_Shdr *symtab_section) {
    std::map<unsigned int, std::string> names;
    for (int i = 0; i * symtab_section->sh_entsize < symtab_section->sh_size; i++) {
        if(symbols[i].st_name != 0) names[symbols[i].st_value] = &symbols_names[symbols[i].st_name];
    }
    return names;
}
