#include "memory.h"

#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/PrintLib.h>

const CHAR16 *get_memtype(EFI_MEMORY_TYPE type) {
    switch (type) {
        case EfiReservedMemoryType: return L"EfiReservedMemoryType";
        case EfiLoaderCode: return L"EfiLoaderCode";
        case EfiLoaderData: return L"EfiLoaderData";
        case EfiBootServicesCode: return L"EfiBootServicesCode";
        case EfiBootServicesData: return L"EfiBootServicesData";
        case EfiRuntimeServicesCode: return L"EfiRuntimeServicesCode";
        case EfiRuntimeServicesData: return L"EfiRuntimeServicesData";
        case EfiConventionalMemory: return L"EfiConventionalMemory";
        case EfiUnusableMemory: return L"EfiUnusableMemory";
        case EfiACPIReclaimMemory: return L"EfiACPIReclaimMemory";
        case EfiACPIMemoryNVS: return L"EfiACPIMemoryNVS";
        case EfiMemoryMappedIO: return L"EfiMemoryMappedIO";
        case EfiMemoryMappedIOPortSpace: return L"EfiMemoryMappedIOPortSpace";
        case EfiPalCode: return L"EfiPalCode";
        case EfiPersistentMemory: return L"EfiPersistentMemory";
        case EfiMaxMemoryType: return L"EfiMaxMemoryType";
        default: return L"InvalidMemoryType";
    }
}

EFI_STATUS allocate_memmap(memmap *map, UINTN buffer_size) {
    map->buffer_size = buffer_size;
    return gBS->AllocatePool(EfiLoaderData, buffer_size, &map->buffer);
}

EFI_STATUS get_memmap(memmap *map) {
    EFI_STATUS status;
    if (map->buffer_size == 0 && map->buffer == NULL) {
        status = allocate_memmap(map, INIT_MAP_SIZE);
        if (EFI_ERROR(status)) {
            return status;
        }
    }
    while(true) {
        map->map_size = map->buffer_size;
        status = gBS->GetMemoryMap(&map->map_size, (EFI_MEMORY_DESCRIPTOR *)map->buffer, &map->map_key, &map->desc_size, &map->desc_ver);
        if (status == EFI_BUFFER_TOO_SMALL) {
            const UINTN buffer_size = (map->map_size) + (map->desc_size * 4);
            Print(L"Memory Map Size %lu", buffer_size);
            status = gBS->FreePool(map->buffer);
        }
    }
}