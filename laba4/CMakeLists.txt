cmake_minimum_required(VERSION 3.23)
project(mkn_comp_arch_2023_riscv_likhhtar)

set(CMAKE_CXX_STANDARD 14)

add_executable(mkn_comp_arch_2023_riscv_likhhtar
        main.cpp elf_decoder_symtab.h elf_decoder_text.h elf_decoder_symtab.cpp elf_decoder_text.cpp )
