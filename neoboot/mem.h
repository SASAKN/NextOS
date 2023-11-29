#ifndef _NEOBOOT_MEM_H
#define _NEOBOOT_MEM_H

// UEFI Base Type
#include <Uefi/UefiBaseType.h>

// Memory Map
struct mem_map {
    UINT64 buffer_size;
    void* buffer;
    UINT64 map_size;
    UINT64 map_key;
    UINT64 descriptor_size;
    UINT32 descriptor_version;
    UINT64 memmap_desc_entry;
};

// ProtoType


#endif //_NEOBOOT_MEM_H