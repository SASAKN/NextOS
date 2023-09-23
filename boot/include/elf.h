#ifndef _BOOT_ELF_H
#define _BOOT_ELF_H

#include "types.h" /* Must be First. */

/* ELFの定義を書くファイル */

/* Dynamic Header */
typedef struct {
    Elf64_Sxword d_tag;
    union {
        Elf64_Xword d_val;
        Elf64_Addr d_ptr;
    } d_un;
} elf_dynamic;

/* ELF Header */
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
} elf_hdr;

/* ELF Section Header */
typedef struct {
    Elf64_Word sh_name;
    Elf64_Word sh_type;
    Elf64_Word sh_flags;
    Elf64_Addr sh_addr;
    Elf64_Off sh_offset;
    Elf64_Word sh_size;
    Elf64_Word sh_link;
    Elf64_Word sh_info;
    Elf64_Word sh_addralign;
    Elf64_Word sh_entsize; 
} elf_shdr;

/* ELF Program Header */
typedef struct {
    Elf64_Word p_type;
    Elf64_Word p_flags;
    Elf64_Off  p_offset;
    Elf64_Addr p_vaddr;
    Elf64_Addr p_paddr;
    Elf64_Xword p_filesz;
    Elf64_Xword p_memsz;
    Elf64_Xword p_align;
} elf_phdr;

/* ELF Relocation Entries */
typedef struct {
    Elf64_Addr r_offset;
    Elf64_Word r_info;
} elf_rel;

typedef struct {
    Elf64_Addr r_offset;
    Elf64_Word r_info;
    Elf64_Sxword r_append;
} elf_rela;

#endif