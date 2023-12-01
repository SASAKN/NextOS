#ifndef _MEM_H
#define _MEM_H

#include <Uefi/UefiBaseType.h>
#include <Protocol/SimpleFileSystem.h>

#define INIT_MAP_SIZE 128

// Memory Mapのデータ型
typedef struct memory_map {
    void *buffer;
    UINTN buffer_size;
    UINTN map_size;
    UINTN map_key;
    UINTN desc_size;
    UINTN desc_ver;
} memmap;

// Prototype
const CHAR16 *get_memtype(EFI_MEMORY_TYPE type);
EFI_STATUS allocate_memmap(memmap *map, UINTN buffer_size);
EFI_STATUS get_memmap(memmap *map);
EFI_STATUS print_memmap(memmap *map);
EFI_STATUS save_memmap(memmap *map, EFI_FILE_PROTOCOL *f, EFI_FILE_PROTOCOL *root_dir);


#endif // _MEM_H