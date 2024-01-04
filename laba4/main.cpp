#include "elf_decoder_text.h"

using namespace std;

int main(int argc, char * argv[]) {
    if (argc < 3) {
        std::cerr << "Incorrect argument count";
        return 1;
    }

    std::ifstream fin(argv[1], std::ios::binary);

    if (!fin.is_open()) {
        cerr << "Can't open file";
        return 1;
    }

    Elf32_Ehdr elf_header;
    if(fin.read(reinterpret_cast<char *>(&elf_header), sizeof(Elf32_Ehdr)).gcount() < sizeof (Elf32_Ehdr)) {
        cerr << "Wrong header size";
        return 1;
    }
    if(!check_header(&elf_header)) {
        cerr << "Wrong header";
        return 1;
    }

    fin.seekg(elf_header.e_shoff, std::ios::beg);
    std::vector<Elf32_Shdr> section_headers(elf_header.e_shnum);
    fin.read(reinterpret_cast<char*>(section_headers.data()), elf_header.e_shnum * elf_header.e_shentsize);


    fin.seekg(section_headers[elf_header.e_shstrndx].sh_offset, std::ios::beg);
    std::vector<char> section_names(section_headers[elf_header.e_shstrndx].sh_size);
    fin.read(section_names.data(), section_headers[elf_header.e_shstrndx].sh_size);

    Elf32_Shdr *symtab_section;
    Elf32_Shdr *text_section;

    for (int i = 1; i < elf_header.e_shnum; i++) {
        if(strcmp(&section_names[section_headers[i].sh_name], ".text") == 0) text_section = &section_headers[i];
        if(strcmp(&section_names[section_headers[i].sh_name], ".symtab") == 0) symtab_section = &section_headers[i];
    }


    unsigned int symbols_size = symtab_section->sh_size / symtab_section->sh_entsize;
    auto* symbols = new Elf32_Sym[symbols_size];
    fin.seekg(symtab_section->sh_offset, std::ios::beg);
    fin.read(reinterpret_cast<char *>(symbols), symtab_section->sh_size);

    char* symbols_names = new char[section_headers[symtab_section->sh_link].sh_size];
    fin.seekg(section_headers[symtab_section->sh_link].sh_offset, std::ios::beg);
    fin.read(symbols_names, section_headers[symtab_section->sh_link].sh_size);

    auto *texts = new short[text_section->sh_size << 1];
    fin.seekg(text_section->sh_offset, std::ios::beg);
    fin.read((char *)texts, text_section->sh_size);

    auto symbol_addr_names = make_names(symbols, symbols_names, symtab_section);

    int l_num = 0;
    std::vector<program> programs;
    for(unsigned int i = 0, j = text_section->sh_addr; i * 4 < text_section->sh_size; i++, j += 4) {
        auto text1 = texts[i * 2];
        auto text2 = texts[i * 2 + 1];
        program pr = program_create(text1, text2);
        auto prog = get_prog(pr);
        programs.push_back(prog);
        int off = 0;
        if (prog.type == "J") {
            unsigned int offset = (((pr.data >> 21) & 0b1111111111) | (((pr.data >> 20) & 0b1)  << 10)  |
                                   (((pr.data >> 12) & 0b11111111) << 11) | (((pr.data >> 31) & 0b1) << 19)) << 1;
            off = expen(j + offset, 0);
            if (symbol_addr_names.count(off) == 0) {
                symbol_addr_names[off] = "L" + std::to_string(l_num++);
            }
        }
        else if (pr.type == "B") {
            unsigned int offset = (((pr.data >> 8) & 0b1111) | (((pr.data >> 25) & 0b111111) << 4)  |
                                   (((pr.data >> 7) & 0b1) << 10) | (((pr.data >> 31) & 0b1) << 11)) << 1;
            off = j + expen(offset, 1);
            if (symbol_addr_names.count(off) == 0) {
                symbol_addr_names[off] = "L" + std::to_string(l_num++);
            }
        }
    }

    FILE *fout = std::fopen(argv[2], "wb");
    fprintf(fout, ".text\n");

    for(unsigned int i = 0, j = text_section->sh_addr; i * 4 < text_section->sh_size; i++, j += 4) {
        auto pr = programs[i];
        print_prog(fout, j, programs[i], symbol_addr_names);
    }

    fprintf(fout, "\n");
    print_symtab(fout, symbols, symtab_section, symbols_names);
    fin.close();
    fclose(fout);
    return 0;
}
