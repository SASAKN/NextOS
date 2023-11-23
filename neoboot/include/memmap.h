#ifndef _NEOBOOT_MEMMAP_H
#define _NEOBOOT_MEMMAP_H

#include "efilib/inc/efi.h"

#define MEMMAP_DESC_SIZE 4096

struct MemoryMap {
    UINT64 buffer_size;
    void* buffer;
    UINT64 map_size;
    UINT64 map_key;
    UINT64 descriptor_size;
    UINT32 descriptor_version;
    UINT64 memmap_desc_entry;
};

struct MemoryDescriptor {
    uint64_t Type;
    uint32_t PhysicalStart;
    uint32_t VirtualStart;
    uint32_t NumberOfPages;
    uint32_t Attribute;
};

#endif //_NEOBOOT_MEMMAP_H