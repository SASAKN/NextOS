/* Prototype Functions */
#ifndef _BOOT_PROTO_H
#define _BOOT_PROTO_H

#include "efi.h"
#include "graphics.h"
#include "mem.h"
#include "elf.h"


/* EFI */
void efi_init(EFI_SYSTEM_TABLE *SystemTable);
void dump_eficonftable(void);
void *find_efi_acpi_table(void);

/* Graphics */
void graphics_init(struct frame_buffer);

/* Common */
void putc (UINT16 c);
void puts(UINT16 *s);
void Print(UINT16 *s); /* EDK2などに合わせるためにある関数 */
UINTN EFIAPI strlen(const CHAR8 *String); /* 文字数を数える */
UINT16 getc(void);
UINT32 gets(UINT16 *buf, UINT32 buf_size);
void PrintHex(UINT64 val, UINT8 num_degits); /* 16進数の出力 */
UINT8 check_warn_error (UINT64 status, UINT16 *mess);
void assert (UINT64 status, UINT16 *mess);

/* Memory */
// void print_memmap(struct MemoryMap* map);
void print_memmap(struct MemoryMap* map);
EFI_STATUS init_memmap(struct MemoryMap *map);
UINT16 *get_memtype_name(EFI_MEMORY_TYPE type);

#endif