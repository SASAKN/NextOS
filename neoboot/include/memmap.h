#ifndef _NEOBOOT_MEMMAP_H
#define _NEOBOOT_MEMMAP_H

#include "types.h"

#define MEMMAP_DESC_SIZE 4096

struct MemoryMap {
    uint64_t buffer_size;
    void* buffer;
    uint64_t map_size;
    uint64_t map_key;
    uint64_t descriptor_size;
    uint32_t descriptor_version;
    uint64_t memmap_desc_entry;
};

struct MemoryDescriptor {
    uint64_t Type;
    uint32_t PhysicalStart;
    uint32_t VirtualStart;
    uint32_t NumberOfPages;
    uint32_t Attribute;
};

#endif //_NEOBOOT_MEMMAP_H