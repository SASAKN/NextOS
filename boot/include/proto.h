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
UINT16 getc(void);
UINT32 gets(UINT16 *buf, UINT32 buf_size);
void PrintHex(UINT64 val, UINT8 num_degits); /* 16進数の出力 */
UINT8 check_warn_error (UINT64 status, UINT16 *mess);
void assert (UINT64 status, UINT16 *mess);

/* Memory */
EFI_STATUS GetMemoryMap(struct MemoryMap *map);
EFI_STATUS PrintMemoryMap(struct MemoryMap *map);
void init_memorymap(struct MemoryMap *mem_map);
void print_memmap(struct MemoryMap *mem_map)


#endif