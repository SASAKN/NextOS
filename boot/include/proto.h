/* Prototype Functions */
#ifndef _BOOT_PROTO_H
#define _BOOT_PROTO_H

#include "efi.h"
#include "graphics.h"
#include "mem.h"
#include "elf.h"

void efi_init(EFI_SYSTEM_TABLE *SystemTable);
void dump_eficonftable(void);
void *find_efi_acpi_table(void);
void puts(unsigned short *s);
void graphics_init(struct frame_buffer);

#endif