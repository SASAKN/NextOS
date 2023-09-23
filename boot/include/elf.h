#ifndef _BOOT_ELF_H
#define _BOOT_ELF_H

#include "types.h" /* Must be First. */

/* ELFの定義を書くファイル */

typedef struct {
    uint8_t e_ident[16];
    Elf64_Half e_type;
    Elf64_Half e_machine;
    Elf64_Word e_version;
    Elf64_Addr e_entry;
    Elf64_Off e_phoff;
    Elf64_Off e_shoff;
    Elf64_Word e_flags;
    Elf64_Half e_ehsize;
    Elf64_Half e_phentsize;
    Elf64_Half e_shentsize;
    Elf64_Half e_shnum;
    Elf64_Half e_shstrndx;
} Elf64_Header;

typedef struct {
    
}

typedef 

#endif