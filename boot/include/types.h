#ifndef _BOOT_TYPES_H
#define _BOOT_TYPES_H

/* Macros */
#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define CONST const

/* UEFIデータ修飾子 */
#define IN
#define OUT
#define EFIAPI

/* Data Types */
typedef unsigned char BOOLEAN;
typedef signed long long INTN;
typedef unsigned long long UINTN;
typedef signed char INT8;
typedef unsigned char UINT8;
typedef short INT16;
typedef unsigned short UINT16;
typedef int INT32;
typedef unsigned int UINT32;
typedef long long INT64;
typedef unsigned long long UINT64;
typedef char CHAR8;
typedef unsigned short CHAR16;
typedef void VOID;
typedef unsigned long long EFI_STATUS;
typedef VOID *EFI_HANDLE;
typedef VOID *EFI_EVENT;
typedef UINT64 EFI_LBA;
typedef UINTN EFI_TPL;

/* Stdint.hで定義されているもの */
typedef unsigned int uintptr_t;
typedef UINT64 uint64_t;
typedef UINT16 uint16_t;
typedef UINT32 uint32_t;
typedef UINT8 uint8_t;
typedef INT32 int32_t;
typedef INT64 int64_t;

/* ELF Types */
typedef uintptr_t Elf64_Addr;
typedef uint64_t Elf64_Xword;
typedef uint64_t Elf64_Off;
typedef uint32_t Elf64_Word;
typedef uint16_t Elf64_Half;
typedef int64_t Elf64_Sxword;
typedef int32_t Elf64_Sword;



#endif