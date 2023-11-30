// For using UEFI Library
#include  <Uefi.h>
#include  <Library/UefiLib.h>
#include  <Library/UefiBootServicesTableLib.h>
#include  <Library/PrintLib.h>
#include  <Library/MemoryAllocationLib.h>
#include  <Library/BaseMemoryLib.h>
#include  <Protocol/LoadedImage.h>
#include  <Protocol/SimpleFileSystem.h>
#include  <Guid/FileInfo.h>

// Memory Map
#include "mem.h"
#include "file.h"
#include "common.h"

// Allocate Pool
void *malloc(UINTN size) {
    void *src;
    EFI_STATUS status;
    src = NULL;
    status = gBS->AllocatePool(EfiLoaderData, size, &src);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Malloc\n");
    }
    return src;
};

// Free Pool
void free(void* ptr) {
    EFI_STATUS status;
    if (ptr) {
        status = gBS->FreePool(ptr);
        if (EFI_ERROR(status)) {
            PrintError();
            Print(L"Free\n");
        }
    }
}

// Init Memory Map
void init_memmap(struct mem_map *map, void* buffer) {
    //値を格納
    map->buffer = buffer;
    map->map_size = 0;
    map->buffer_size = 0;
    map->descriptor_size = 0;
    map->descriptor_version = 0;
    map->map_key = 0;
    PrintOK();
    Print(L"Init Memory Map\n");
}

// Get Memory Buffer Type
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

// メモリーマップの取得
EFI_STATUS get_memmap(struct mem_map *map) {
    EFI_STATUS status;
    UINTN buffer_size;
    // 512 Bytes
    if (map->buffer == NULL) {
        map->buffer = malloc(512);
    }
    // Main Loop
        map->map_size = map->buffer_size;
        status = gBS->GetMemoryMap(&map->map_size, (EFI_MEMORY_DESCRIPTOR *)map->buffer, &map->map_key, &map->descriptor_size, &map->descriptor_version); 
        // reallocate
        if (status == EFI_BUFFER_TOO_SMALL) {
            // どうだろうどっちが適しているかな
            buffer_size = (map->map_size + 4095) & ~(UINTN)4095;
            // buffer_size = map->map_size + (4 * map->descriptor_size);
            free(map->buffer);
            map->buffer = malloc(buffer_size);
            status = gBS->GetMemoryMap(&buffer_size, (EFI_MEMORY_DESCRIPTOR *)map->buffer, &map->map_key, &map->descriptor_size, &map->descriptor_version); 
            return EFI_SUCCESS;
        }
    PrintOK();
    Print(L"Get Memory Map\n");
    return EFI_SUCCESS;
}

// Print Memory Map
EFI_STATUS print_memmap(struct mem_map *map) {
    Print(L"\n [ INFO ] Memory Map \n");
    UINT16 *header = L"Index, Buffer, Type, Type(name), PhysicalStart, VirtualStart, NumberOfPages, Size, Attribute";
    Print(L"%-ls\n", header);
    EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR *)map->buffer;
    for (UINT32 i = 0; i < map->memmap_desc_entry; i++) {
        Print(L"%02d, %016x, %02x, %-ls, %016x, %016x, %016x, %d, %016x \n", i, desc, desc->Type, get_memtype(desc->Type), desc->PhysicalStart, desc->VirtualStart, desc->NumberOfPages, desc->NumberOfPages, desc->Attribute);
        desc = (EFI_MEMORY_DESCRIPTOR *)((UINT8 *)desc + map->descriptor_size);
    }
    Print(L"\n");
    PrintOK();
    Print(L"Print Memory Map\n");
    return EFI_SUCCESS;
}

//メモリーマップをファイルに保存
EFI_STATUS save_memmap(struct mem_map *map, EFI_FILE_PROTOCOL *root) {
    EFI_STATUS status;
    CHAR8 buffer[512];
    UINTN size;
    EFI_FILE_PROTOCOL *memmap_file;
    // MemoryMap Header
    CHAR8 *header = "Index, Buffer, Type, Type(name), PhysicalStart, VirtualStart, NumberOfPages, Size, Attribute";
    size = AsciiStrLen(header);
    // Create Memory Map file
    memmap_file = create_file(root, L"\\EFI\\neos\\memmap.blmm");
    // Write Header
    status = memmap_file->Write(memmap_file, &size, header);
    if (EFI_ERROR (status)) {
        PrintError();
        Print(L"Write Header : %r\n", status);
    };
    // Write Memory Map
    EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR *)map->buffer;
    for (UINT32 i = 0; i < map->memmap_desc_entry; i++) {
        size = AsciiSPrint(buffer, sizeof(buffer), "%02u, %016x, %02x, %-ls, %016x, %016x, %016x, %d, %016x \n", i, desc, desc->Type, get_memtype(desc->Type), desc->PhysicalStart, desc->VirtualStart, desc->NumberOfPages, desc->NumberOfPages, desc->Attribute);
        status = memmap_file->Write(memmap_file, &size, header);
        if (EFI_ERROR(status)) {
            PrintError();
            Print(L"Write Memory Map\n : %r", status);
        }
        desc = (EFI_MEMORY_DESCRIPTOR *)((UINT8 *)desc + map->descriptor_size);
    }
    memmap_file->Close(memmap_file);
    return EFI_SUCCESS;
}


