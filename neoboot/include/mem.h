#ifndef _BOOT_MEM_H
#define _BOOT_MEM_H

#include "../uefi/uefi.h"

/* A memory map for booting */
struct MemoryMap {
    uint64_t buffer_size;
    void* buffer;
    uint64_t map_size;
    uint64_t map_key;
    uint64_t descriptor_size;
    uint32_t descriptor_version;
    uint64_t memmap_desc_entry;
};

/* EFI_MEMORY_DESCRIPTOR */
struct MemoryDescriptor {
    uintn_t Type;
    uint32_t PhysicalStart;
    uint32_t VirtualStart;
    uint32_t NumberOfPages;
    uint32_t Attribute;
};

#endif