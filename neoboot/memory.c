#include "memory.h"
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/PrintLib.h>
#include "efiio.h"

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

void init_memmap(memmap *map) {
    map->buffer = NULL;
    map->buffer_size = 0;
    map->map_size = 0;
    map->map_key = 0;
    map->desc_size = 0;
    map->desc_ver = 0;
    map->desc_entry = 0;
}

EFI_STATUS get_memmap(memmap *map) {
    EFI_STATUS status = EFI_SUCCESS;
    if (map->buffer_size == 0 && map->buffer == NULL) {
        status = allocate_memmap(map, INIT_MAP_SIZE);
        if (EFI_ERROR(status)) {
            PrintError();
            Print(L"Allocate Pool\n");
            return status;
        }
        PrintOK();
        Print(L"Allocate Memory Map\n");
    }
    while(1) {
        map->map_size = map->buffer_size;
        status = gBS->GetMemoryMap(&map->map_size, (EFI_MEMORY_DESCRIPTOR *)map->buffer, &map->map_key, &map->desc_size, &map->desc_ver);
        if (status == EFI_BUFFER_TOO_SMALL) {
            PrintWarn();
            Print(L"Buffer size is too small. will try again !\n");
            const UINTN buffer_size = (map->map_size) + (map->desc_size * 4);
            Print(L"[ INFO ] Memory Map Size %lu\n", buffer_size);
            // Free Pool
            status = gBS->FreePool(map->buffer);
            if (EFI_ERROR(status)) {
                PrintError();
                Print(L"Free Pool : %r\n", status);
            }
            // Try Again !
            status = allocate_memmap(map, buffer_size);
            if (EFI_ERROR(status)) {
                PrintError();
                Print(L"Allocate Pool\n");
            }
            continue;
        }
        if (EFI_ERROR(status)) {
            PrintError();
            Print(L"Unknown Error : %r", status);
        }
        return EFI_SUCCESS;
    }
}

EFI_STATUS print_memmap(memmap *map) {
    // Print header
    Print(L"\n [ INFO ] Memory Map \n");
    UINT16 *header = L"Index, Buffer, Type, Type(name), PhysicalStart, VirtualStart, NumberOfPages, Size, Attribute";
    Print(L"%-ls\n", header);
    int i;
    EFI_PHYSICAL_ADDRESS iter;
    UINTN mem_size = 0;
    for (iter = (EFI_PHYSICAL_ADDRESS)map->buffer, i = 0;
    iter < (EFI_PHYSICAL_ADDRESS)map->buffer + map->map_size;
    iter += map->desc_size, i++) {
        EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR *)iter;
        Print(L"%02d, %016x, %02x, %-ls, %016x, %016x, %016x, %d, %016x \n", i, desc, desc->Type, get_memtype(desc->Type), desc->PhysicalStart, desc->VirtualStart, desc->NumberOfPages, desc->NumberOfPages, desc->Attribute);
        mem_size += desc->NumberOfPages;
    }
    // Entryを変更
    map->desc_entry = (UINT64)i;
    Print(L"\n");
    PrintOK();
    Print(L"Print Memory Map\n");
    Print(L"[ INFO ] Number Of Pages : %lu bytes", mem_size);
    return EFI_SUCCESS;
}

EFI_STATUS save_memmap(memmap *map, EFI_FILE_PROTOCOL *f, EFI_FILE_PROTOCOL *root_dir) {
    char buffer[512];
    EFI_STATUS status;
    UINTN size;
    // Header
    CHAR8 *header = "Index, Buffer, Type, Type(name), PhysicalStart, VirtualStart, NumberOfPages, Size, Attribute";
    size = AsciiStrLen(header);
    // Open memory map file
    status = root_dir->Open(root_dir, &f, L"\\memmap.blmm", EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE, 0);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Create a file : %r\n", status);
    }
    // Write header
    status = f->Write(f, &size, header);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Write header : %r\n", status);
    }
    // Write memory map
    EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR *)map->buffer;
    for (UINT32 i = 0; i < map->desc_entry; i++) {
        size = AsciiSPrint(buffer, sizeof(buffer), "%02u, %016x, %02x, %-ls, %016x, %016x, %016x, %d, %016x \n", i, desc, desc->Type, get_memtype(desc->Type), desc->PhysicalStart, desc->VirtualStart, desc->NumberOfPages, desc->NumberOfPages, desc->Attribute);
        status = f->Write(f, &size, header);
        if (EFI_ERROR(status)) {
            PrintError();
            Print(L"Write Memory Map : %r\n", status);
        }
        desc = (EFI_MEMORY_DESCRIPTOR *)((UINT8 *)desc + map->desc_size);
    }
    f->Close(f);
    return EFI_SUCCESS;
}