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
void *malloc(UINTN size);
void free(void *ptr);
void init_memmap(struct mem_map *map, void *buffer);
const CHAR16 *get_memtype(EFI_MEMORY_TYPE type);
EFI_STATUS get_memmap(struct mem_map *map);
EFI_STATUS print_memmap(struct mem_map *map);
EFI_STATUS save_memmap(struct mem_map *map, EFI_FILE_PROTOCOL *root);


#endif //_NEOBOOT_MEM_H