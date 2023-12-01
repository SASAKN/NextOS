#ifndef _MEM_H
#define _MEM_H

#include <Uefi/UefiBaseType.h>

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


#endif // _MEM_H