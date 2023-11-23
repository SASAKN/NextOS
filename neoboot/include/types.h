#ifndef _NEOBOOT_TYPES_H
#define _NEOBOOT_TYPES_H

// General Types

//unsgined
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

//signed
typedef int int32_t;
typedef short int16_t;

//other
typedef uint16_t wchar_t;

// ELF Types
typedef unsigned long long Elf64_Addr;
typedef unsigned long long Elf64_Xword;
typedef unsigned long long Elf64_Off;
typedef unsigned int Elf64_Word;
typedef unsigned short Elf64_Half;
typedef long long Elf64_Sxword;
typedef int Elf64_Sword;

#endif