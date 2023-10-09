#ifndef _BOOT_MEM_H
#define _BOOT_MEM_H

#include "types.h" /* Must be First. */

#define MEM_BUFFER_SIZE 4800

/* A memory map for booting */
struct MemoryMap {
    uint64_t buffer_size;
    void* buffer;
    uint64_t map_size;
    uint64_t map_key;
    uint64_t descriptor_size;
    uint32_t descriptor_version;
};

/* EFI_MEMORY_DESCRIPTOR */
struct MemoryDescriptor {
    UINTN Type;
    UINT32 PhysicalStart;
    UINT32 VirtualStart;
    UINT32 NumberOfPages;
    UINT32 Attribute;
};


#endif