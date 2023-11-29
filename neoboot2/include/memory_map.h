#ifndef _BOOT_MEM_H
#define _BOOT_MEM_H

// For using UEFI Library
#include <Uefi/UefiBaseType.h>

#include "file.h"
#include "proto.h"
#include "elf.h"

/* A memory map for booting */
struct MemoryMap {
    UINT64 buffer_size;
    void* buffer;
    UINT64 map_size;
    UINT64 map_key;
    UINT64 descriptor_size;
    UINT32 descriptor_version;
    UINT64 memmap_desc_entry;
};

/* EFI_MEMORY_DESCRIPTOR */
struct MemoryDescriptor {
    UINT64 Type;
    UINT32 PhysicalStart;
    UINT32 VirtualStart;
    UINT32 NumberOfPages;
    UINT32 Attribute;
};

#endif // _BOOT_MEM_H
