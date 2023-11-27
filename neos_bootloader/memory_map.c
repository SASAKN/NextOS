#include "include/proto.h"
#include "include/memory_map.h"

// Allocate Pool
// Mallocの実装
void *malloc(size_t size) {
    void *src;
    EFI_STATUS status;
    src = NULL;
    status = gBS->AllocatePool(EfiLoaderData, size, &src);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Malloc\n");
    }
    return src;
}

// Free Pool
// Freeの実装
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

//メモリーマップを関数で使えるようにする準備
void init_memmap(struct MemoryMap *map, void* buffer) {
    //値を格納
    map->buffer = buffer;
    map->map_size = 0;
    map->descriptor_size = 0;
    map->descriptor_version = 0;
    map->map_key = 0;
    PrintOK();
    Print(L"Init Memory Map\n");
}

//メモリーがどうのように割り当てられているのか取得
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
EFI_STATUS get_memmap(struct MemoryMap *map) {
    EFI_STATUS status;
    // 割り当てる
    map->buffer = malloc(map->map_size);
    status = gBS->GetMemoryMap(&map->map_size, (EFI_MEMORY_DESCRIPTOR *)map->buffer, &map->map_key, &map->descriptor_size, &map->descriptor_version);
    if (status == EFI_BUFFER_TOO_SMALL) {
        //もう一度割り当てる
        free(map->buffer);
        map->buffer = malloc(map->map_size);
        status = gBS->GetMemoryMap(&map->map_size, (EFI_MEMORY_DESCRIPTOR *)map->buffer, &map->map_key, &map->descriptor_size, &map->descriptor_version);
        //エラーハンドリング
        if (EFI_ERROR(status)) {
            PrintError();
            Print(L"Get Memory Map : %r\n", status);
        }
    }
    PrintOK();
    Print(L"Get Memory Map\n");
    return EFI_SUCCESS;
}

//メモリーマップを表示
EFI_STATUS print_memmap(struct MemoryMap *map) {
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
