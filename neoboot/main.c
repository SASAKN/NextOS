#include  <Uefi.h>
#include  <Library/UefiLib.h>
#include  <Library/UefiBootServicesTableLib.h>
#include  <Library/UefiRuntimeServicesTableLib.h>
#include  <Library/PrintLib.h>
#include  <Library/MemoryAllocationLib.h>
#include  <Library/BaseMemoryLib.h>
#include  <Protocol/LoadedImage.h>
#include  <Protocol/SimpleFileSystem.h>
#include  <Guid/FileInfo.h>

#include "memory.h"

// Print(Special Ver.)

void PrintOK(void)
{
    gST->ConOut->SetAttribute(gST->ConOut, EFI_GREEN); /* 緑で、OKを表示 */
    gST->ConOut->OutputString(gST->ConOut, L"[ OK ]");
    gST->ConOut->SetAttribute(gST->ConOut, EFI_WHITE); /* 白に戻す */
};

void PrintWarn(void)
{
    gST->ConOut->SetAttribute(gST->ConOut, EFI_YELLOW); /* 黄色で、Warnを表示 */
    gST->ConOut->OutputString(gST->ConOut, L"[ Warn ]");
    gST->ConOut->SetAttribute(gST->ConOut, EFI_WHITE); /* 白に戻す */
};

void PrintError(void)
{
    gST->ConOut->SetAttribute(gST->ConOut, EFI_RED); /* あかで、Errorを表示 */
    gST->ConOut->OutputString(gST->ConOut, L"[ Error ! ]");
    gST->ConOut->SetAttribute(gST->ConOut, EFI_WHITE); /* 白に戻す */
};

// Open root directory
EFI_STATUS open_root_dir(EFI_HANDLE IM, EFI_FILE_PROTOCOL **root) {
    EFI_STATUS status;
    EFI_LOADED_IMAGE_PROTOCOL *lip;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *fs;
    // Loaded Image Protocol
    status = gBS->OpenProtocol(IM, &gEfiLoadedImageProtocolGuid, (VOID**)&lip, IM, NULL, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Open Protocol : %r\n", status);
    }
    // Simple File System Protocol
    status = gBS->OpenProtocol(lip->DeviceHandle, &gEfiSimpleFileSystemProtocolGuid, (VOID**)&fs, IM, NULL, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Open Protocol : %r\n", status);
    }
    // Open Volume
    status = fs->OpenVolume(fs, root);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Open Volume : %r\n", status);
    }
    PrintOK();
    Print(L"Open Volume\n");
    return EFI_SUCCESS;
}

UINT64 open_file_read(EFI_FILE_PROTOCOL *root, CHAR16 *file_path, EFI_FILE_PROTOCOL *file) {
    EFI_STATUS status;
    // open the file
    status = root->Open(root, &file, file_path, EFI_FILE_MODE_READ, 0);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Open '%-ls' : %r\n", file_path, status);
        return status;
    }

    // calculate file info buffer size
    UINTN file_info_buffer_size = sizeof(EFI_FILE_INFO) + sizeof(CHAR16) * StrLen(file_path) + 2;
    UINT8 file_info_buffer[file_info_buffer_size];
    status = file->GetInfo(file, &gEfiFileInfoGuid, &file_info_buffer_size, file_info_buffer);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Get Info : %r \n", status);
        return status;
    }

    PrintOK();
    Print(L"Get Info\n");

    // result
    EFI_FILE_INFO *file_info = (EFI_FILE_INFO *)file_info_buffer;
    return file_info->FileSize;
}

void Halt(void) {
    while(1) __asm__ ("hlt");
}

// Memory Map 
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
    Print(L"[ INFO ] Number Of Pages : %lu\n", (mem_size + 0xfff) / 0x1000);
    return EFI_SUCCESS;
}

EFI_STATUS save_memmap(memmap *map, EFI_FILE_PROTOCOL *f, EFI_FILE_PROTOCOL *root_dir) {
    char buffer[256];
    EFI_STATUS status;
    UINTN size;
    // Header
    CHAR8 *header = "Index, Buffer, Type, Type(name), PhysicalStart, VirtualStart, NumberOfPages, Size, Attribute\n"
                    "-----|------------------|----|----------------------|------------------|------------------|------------------|-----|----------------|\n";
    size = AsciiStrLen(header); // 211
    // Open memory map file
    status = root_dir->Open(root_dir, &f, L"\\memmap.blmm", EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE, 0);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Create a file : %r\n", status);
    }
    PrintOK();
    Print(L"Create a file 'memmap.blmm' \n");
    // Write header
    status = f->Write(f, &size, header);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Write header : %r\n", status);
    }
    PrintOK();
    Print(L"Write header\n");
    // Write memory map
    EFI_PHYSICAL_ADDRESS iter;
    int i;
    for (iter = (EFI_PHYSICAL_ADDRESS)map->buffer, i = 0;
    iter < (EFI_PHYSICAL_ADDRESS)map->buffer + map->map_size;
    iter += map->desc_size, i++)  {
        EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR *)iter;
        size = AsciiSPrint(buffer, sizeof(buffer), "| %02u | %016x | %02x | %20ls | %016x | %016x | %016x | %3d | %2ls %5lx | \n", i, desc, desc->Type, get_memtype(desc->Type), desc->PhysicalStart, desc->VirtualStart, desc->NumberOfPages, desc->NumberOfPages, (desc->Attribute & EFI_MEMORY_RUNTIME) ? L"RT" : L"", desc->Attribute & 0xffffflu);
        status = f->Write(f, &size, buffer);
        if (EFI_ERROR(status)) {
            PrintError();
            Print(L"Write Memory Map : %r\n", status);
        }
    }
    PrintOK();
    Print(L"Save Memory Map\n");
    f->Close(f);
    return EFI_SUCCESS;
}


void init_uefi(void) {
    // Do not reboot
    gBS->SetWatchdogTimer(0, 0 ,0, NULL);
    // Interval of priting text
    gBS->Stall(50000);
    // Ascii art
    Print(L" __    __                        __       ______    ______  \n");
    Print(L"/  \\  /  |                      /  |     /      \\  /      \\  \n");
    Print(L"$$  \\ $$ |  ______   __    __  _$$ |_   /$$$$$$  |/$$$$$$  | \n");
    Print(L"$$$  \\$$ | /      \\ /  \\  /  |/ $$   |  $$ |  $$ |$$ \\__$$/ \n");
    Print(L"$$$$  $$ |/$$$$$$  |$$  \\/$$/ $$$$$$/   $$ |  $$ |$$      \\ \n");
    Print(L"$$ $$ $$ |$$    $$ | $$  $$<    $$ | __ $$ |  $$ | $$$$$$  |\n");
    Print(L"$$ |$$$$ |$$$$$$$$/  /$$$$  \\   $$ |/  |$$ \\__$$ |/  \\__$$ |\n");
    Print(L"$$ | $$$ |$$       |/$$/ $$  |  $$  $$/ $$    $$/ $$    $$/ \n ");
    Print(L"$$/   $$/  $$$$$$$/ $$/   $$/    $$$$/   $$$$$$/   $$$$$$/  \n\n");
    // Welcome
    PrintOK();
    Print(L"Welcome to NextOS \n");
}


EFI_STATUS EFIAPI efi_main(EFI_HANDLE IM, EFI_SYSTEM_TABLE *sys_table) {
    // Welcome
    EFI_STATUS status;
    init_uefi();

    // Open Root Directory
    EFI_FILE_PROTOCOL *root;
    open_root_dir(IM, &root);

    // Init memory map
    memmap map;
    init_memmap(&map);
    // Get memory map
    get_memmap(&map);
    // Print memory map
    print_memmap(&map);
    // Print memory map info
    Print(L"\n[ INFO ] Memory Map Info \n");
    Print(L" map : %08x\n map_size : %lu\n desc_size : %lu\n desc_ver : %lu\n key : %lu\n entry : %lu  \n\n", map.buffer, map.map_size, map.desc_size, map.desc_ver, map.map_key, map.desc_entry);
    // Save memory map
    EFI_FILE_PROTOCOL *memmap_f;
    memmap_f = NULL;
    save_memmap(&map, memmap_f, root);
    // End Memory Map
    FreePool(map.buffer);

    // Exit boot services  
    status = gBS->ExitBootServices(IM, map.map_key);
    if (EFI_ERROR(status)) {
        status = get_memmap(&map);
        if (EFI_ERROR(status)) {
            PrintError();
            Print(L"Get Memory Map - Exit BS : %r \n", status);
            while(1);
        }
        status = gBS->ExitBootServices(IM, map.map_key);
        if (EFI_ERROR(status)) {
            PrintError();
            Print(L"Exit BS : %r\n", status);
            while(1);
        }
    }

    // // Call kernel
    // // entry_addr -= 0x1000UL;
    // typedef void entry_point_t(void);
    // entry_point_t *entry_point = (entry_point_t *)entry_addr;
    // entry_point();

    // Halt
    while (1) __asm__ ("hlt");
    return EFI_SUCCESS;
} 


