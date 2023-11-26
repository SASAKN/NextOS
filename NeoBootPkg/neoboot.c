// For using UEFI Library
#include  <Uefi.h>
#include  <Library/UefiLib.h>
#include  <Library/UefiBootServicesTableLib.h>
#include  <Library/UefiRuntimeServicesTableLib.h>
#include  <Library/PrintLib.h>
#include  <Library/MemoryAllocationLib.h>
#include  <Library/BaseMemoryLib.h>
#include  <Protocol/LoadedImage.h>
#include  <Protocol/SimpleFileSystem.h>
#include  <Protocol/DiskIo2.h>
#include  <Protocol/BlockIo.h>
#include  <Guid/FileInfo.h>

// For using kernel
#include "include/mem.h"
#include "include/elf.h"

// // For Debug
// #include "uefilib/inc/efi.h"
// #include "uefilib/inc/efilib.h"

//EDK2から正しく読み込まれなかったら
#ifndef MAX_UINT64
#define MAX_UINT64 18446744073709551615
#endif

#ifndef MIN
#define MAX(a, b) (a < b ? b : a)
#define MIN(a, b) (a < b ? a : b)
#endif

// 文字を表示する関係

void PrintOK(void)
{
    gST->ConOut->SetAttribute(gST->ConOut, 0x02); /* 緑で、OKを表示 */
    gST->ConOut->OutputString(gST->ConOut, L"[ OK ]");
    gST->ConOut->SetAttribute(gST->ConOut, 0x0F); /* 白に戻す */
};

void PrintWarn(void)
{
    gST->ConOut->SetAttribute(gST->ConOut, 0x0E); /* 黄色で、Warnを表示 */
    gST->ConOut->OutputString(gST->ConOut, L"[ Warn ]");
    gST->ConOut->SetAttribute(gST->ConOut, 0x0F); /* 白に戻す */
};

void PrintError(void)
{
    gST->ConOut->SetAttribute(gST->ConOut, 0x04); /* あかで、Errorを表示 */
    gST->ConOut->OutputString(gST->ConOut, L"[ Error ! ]");
    gST->ConOut->SetAttribute(gST->ConOut, 0x0F); /* 白に戻す */
};

void PrintGoodBye(void)
{
    gST->ConOut->SetAttribute(gST->ConOut, EFI_BLUE); /* あかで、Errorを表示 */
    gST->ConOut->OutputString(gST->ConOut, L"[ GoodBye ]");
    gST->ConOut->SetAttribute(gST->ConOut, 0x0F); /* 白に戻す */
};

//ファイル関係

//ルートディレクトリーを開くための関数
EFI_STATUS open_root_dir(EFI_HANDLE IM, EFI_FILE_PROTOCOL** root) {
    EFI_STATUS status;
    EFI_LOADED_IMAGE_PROTOCOL *lip;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *sfsp;
    // Loaded Image Protocol
    status = gBS->OpenProtocol(IM, &gEfiLoadedImageProtocolGuid, (VOID **)&lip, IM, NULL, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Open LIP Protocol\n");
        return status;
    };
    // Simple File System Protocol
    status = gBS->OpenProtocol(lip->DeviceHandle, &gEfiSimpleFileSystemProtocolGuid, (VOID **)&sfsp, IM, NULL, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Open SFSP Protocol\n");
        return status;
    };
    //記憶装置について取得
    status = sfsp->OpenVolume(sfsp, root);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Open Volume\n");
        return status;
    };
    return EFI_SUCCESS;
}

//ブロックデバイス関係

//ブロックデバイスについての情報を表示
EFI_STATUS open_block_io_protocol(EFI_HANDLE IM, EFI_BLOCK_IO_PROTOCOL **block_io) {
    EFI_STATUS status;
    EFI_LOADED_IMAGE_PROTOCOL *lip;
    // Loaded Image Protocol
    status = gBS->OpenProtocol(IM, &gEfiLoadedImageProtocolGuid, (VOID **)&lip, IM, NULL, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Open LIP Protocol");
        return status;
    };
    // Block IO Protocol
    status = gBS->OpenProtocol(lip->DeviceHandle, &gEfiBlockIoProtocolGuid, (VOID **)block_io, IM, NULL, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
        if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Open Block IO Protocol");
        return status;
    };
    return EFI_SUCCESS;
}

//ディスク情報を表示
EFI_STATUS open_disk(EFI_BLOCK_IO_PROTOCOL *block_io, UINT32 media_id, UINTN read_bytes, VOID** buffer) {
    EFI_STATUS status;
    //一時的なメモリーを確保
    status = gBS->AllocatePool(EfiLoaderData, read_bytes, buffer);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Allocate Pool\n");
        return status;
    }
    //ブロックデバイスを読む
    status = block_io->ReadBlocks(block_io, media_id, 0, read_bytes, *buffer);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Read Blocks\n");
        return status;
    }
    //デバッグ情報を表示
    Print(L"[ DEBUG ] LBA 0 Media ID %x, Read_Bytes %x, Buffer %x\n",media_id, read_bytes, buffer);
    //実は、OSには、ドライバーがしっかりあるためこれ以降は、BLOCK_IOを使わない
    return EFI_SUCCESS;
}


//メモリーマップ関係

//メモリーマップを取得
EFI_STATUS get_memmap(struct MemoryMap *map) {
    EFI_STATUS status;
    status = gBS->GetMemoryMap(&map->map_size, NULL, &map->map_key, &map->descriptor_size, NULL);
    if (status != EFI_BUFFER_TOO_SMALL || !map->map_size) {
        PrintError();
        Print(L"Get Memory Map\n");
    }
    map->map_size += 4 * map->descriptor_size;
    char memmap_buf[map->map_size];
    map->buffer = memmap_buf;
    if (!map->map_size) {
        PrintError();
        Print(L"Allocate Memory\n");
        return 1;
    }
    //2回目の実行で確実に取得できる
    status = gBS->GetMemoryMap(&map->map_size, (EFI_MEMORY_DESCRIPTOR *)map->buffer, &map->map_key, &map->descriptor_size, NULL);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Get Memory Map\n");
    }
    //これを計算することによって、Printなどで呼び出すときに呼び出しやすくなる
    map->memmap_desc_entry = map->map_size / map->descriptor_size;
    PrintOK();
    Print(L"Get Memory Map\n");
    return EFI_SUCCESS;
};

//種類を特定
char *get_memtype_name(EFI_MEMORY_TYPE type)
{
    switch (type)
    {
    case EfiReservedMemoryType:
        return "EfiReservedMemoryType";
    case EfiLoaderCode:
        return "EfiLoaderCode";
    case EfiLoaderData:
        return "EfiLoaderData";
    case EfiBootServicesCode:
        return "EfiBootServicesCode";
    case EfiBootServicesData:
        return "EfiBootServicesData";
    case EfiRuntimeServicesCode:
        return "EfiRuntimeServicesCode";
    case EfiRuntimeServicesData:
        return "EfiRuntimeServicesData";
    case EfiConventionalMemory:
        return "EfiConventionalMemory";
    case EfiUnusableMemory:
        return "EfiUnusableMemory";
    case EfiACPIReclaimMemory:
        return "EfiACPIReclaimMemory";
    case EfiACPIMemoryNVS:
        return "EfiACPIMemoryNVS";
    case EfiMemoryMappedIO:
        return "EfiMemoryMappedIO";
    case EfiMemoryMappedIOPortSpace:
        return "EfiMemoryMappedIOPortSpace";
    case EfiPalCode:
        return "EfiPalCode";
    case EfiPersistentMemory:
        return "EfiPersistentMemory";
    case EfiMaxMemoryType:
        return "EfiMaxMemoryType";
    default:
        return "InvalidMemoryType";
    }
};

//メモリーマップを画面に表示
EFI_STATUS print_memmap(struct MemoryMap *map) {
    Print(L"\n [ INFO ] MemoryMap \n");
    char *header = "Index, Buffer, Type, Type(name), PhysicalStart, VirtualStart, NumberOfPages, Size, Attribute";
    Print(L"%s", header);
    EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR *)map->buffer;
    for (UINT32 i = 0; i < map->memmap_desc_entry; i++) {
        Print(L"%02d, %016x, %02x, %s, %016x, %016x, %016x, %d, %016x \n", i, desc, desc->Type, get_memtype_name(desc->Type), desc->PhysicalStart, desc->VirtualStart, desc->NumberOfPages, desc->NumberOfPages, desc->Attribute);
        desc = (EFI_MEMORY_DESCRIPTOR *)((UINT8 *)desc + map->descriptor_size);
    }
    Print(L"\n");
    PrintOK();
    Print(L"Print Memory Map\n");
    return EFI_SUCCESS;
};

//メモリーマップをファイルに保存する関数
EFI_STATUS save_memmap(struct MemoryMap *map, EFI_FILE_PROTOCOL *f) {
    EFI_STATUS status;
    CHAR8 memmap_buffer[1024];
    UINTN size;
    char *header = "Index, Buffer, Type, Type(name), PhysicalStart, VirtualStart, NumberOfPages, Size, Attribute";
    size = AsciiStrLen(header);
    //ヘッダーの書き込み
    status = f->Write(f, &size, header);
    if(EFI_ERROR(status)) {
        PrintError();
        Print(L"Open File\n");
        return status;
    }
    Print(L"[ DEBUG ] map->buffer = %08lx, map->map_size = %08lx\n", map->buffer, map->map_size);
    EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR *)map->buffer;
    //メモリーマップの書き込み
    for (UINT32 i = 0; i < map->memmap_desc_entry; i++) {
        size = AsciiSPrint(memmap_buffer, sizeof(memmap_buffer), "%02d, %016x, %02x, %s, %016x, %016x, %016x, %d, %016x \n", i, desc, desc->Type, get_memtype_name(desc->Type), desc->PhysicalStart, desc->VirtualStart, desc->NumberOfPages, desc->NumberOfPages, desc->Attribute);
        status = f->Write(f, &size, memmap_buffer);
        if(EFI_ERROR(status)) {
            PrintError();
            Print(L"Save Memory Map\n");
            return status;
        }
    }
    // Close File Handle
    f->Close(f);
    return EFI_SUCCESS;
}

//ELF解析系

//メモリアドレスの計算
void calc_address_range(elf64_ehdr *ehdr, UINT64 start, UINT64 end) {
    //初期値の設定
    start = 0;
    end = 0;
    //ループでアドレスの計算
    for ( Elf64_Half i = 0; i < ehdr->e_phnum; i++) {
        elf64_phdr* phdr = (elf64_phdr *)((UINT64)ehdr + ehdr->e_phoff + ehdr->e_phentsize * i);
        if (phdr[i].p_type != PT_LOAD) continue;
        if (!start) {
            start = phdr->p_paddr;
            end = phdr->p_paddr + phdr->p_memsz;
        }
        start = MIN(start, phdr->p_paddr);
        end = MAX(end, phdr->p_paddr + phdr->p_memsz);
    };
};

//セグメントのコピーとロード
void copy_load_segments(elf64_ehdr *ehdr) {
    for (Elf64_Half i = 0; i < ehdr->e_phnum; i++) {
        elf64_phdr* phdr = (elf64_phdr *)((UINT64)ehdr + ehdr->e_phoff + ehdr->e_phentsize * i);
        if (phdr->p_type != PT_LOAD) continue;
        CopyMem((VOID *)phdr->p_paddr, (char *)ehdr + phdr->p_offset, phdr->p_filesz);
    }
}

//カーネルの読み込み
// Defines Of Entry Point
typedef void entry_t(void);

EFI_STATUS load_kernel(EFI_FILE_PROTOCOL *kernel_f, EFI_FILE_PROTOCOL *root_dir, UINT64 entry_addr, entry_t e_entry) {
    EFI_STATUS status;
    // Create Kernel File Handle
    status = root_dir->Open(root_dir, &kernel_f, L"\\kernel.elf", EFI_FILE_MODE_READ, 0);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Open 'kernel.elf'\n ");
        return status;
    }
    // Get Info Kernel File
    UINTN kernel_f_info_size = sizeof(EFI_FILE_INFO) + sizeof(CHAR16) *12;
    UINT8 kernel_f_info_buffer[kernel_f_info_size];
    status = kernel_f->GetInfo(kernel_f, &gEfiFileInfoGuid, &kernel_f_info_size, kernel_f_info_buffer);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Get Info Kernel File 'kernel.elf'\n ");
    }
    // Read Kernel File Info
    EFI_FILE_INFO *kernel_f_info = (EFI_FILE_INFO *)kernel_f_info_buffer;
    UINTN kernel_f_size = kernel_f_info->FileSize;
    VOID *kernel_buffer;
    // Allocate Pool
    status = gBS->AllocatePool(EfiLoaderData, kernel_f_size, &kernel_buffer);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Allocate Pool\n");
    }
    // Read Kernel
    status = kernel_f->Read(kernel_f, &kernel_f_size, kernel_buffer);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Read Kernel File\n");
    }
    // Allocate Pages
    elf64_ehdr *kernel_ehdr = (elf64_ehdr *)kernel_buffer;
    UINT64 kernel_start_addr = 0, kernel_end_addr = 0;
    calc_address_range(kernel_ehdr, kernel_start_addr, kernel_end_addr);
    UINTN num_pages = (kernel_end_addr - kernel_start_addr + 0xfff) / 0x1000;
    status = gBS->AllocatePages(AllocateAddress, EfiLoaderData, num_pages, &kernel_start_addr);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Allocate Pool\n");
    }
    // Copy Segments
    copy_load_segments(kernel_ehdr);
    status = gBS->FreePool(kernel_buffer);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Free Pool\n");
    }
    // Get Entry Address
    entry_addr = *(UINT64 *)(kernel_start_addr + 24);
    e_entry = (entry_t *)kernel_ehdr->e_entry;
    return EFI_SUCCESS;
}


//カーネルパラメーター用意系

//ラッパー関数系

//ExitBootServices
EFI_STATUS exit_bs(EFI_HANDLE IM, struct MemoryMap *map) {
    EFI_STATUS status;
    PrintGoodBye();
    status = gBS->ExitBootServices(IM, map->map_key);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Exit Boot Services\n");
        //メモリーマップを取得して再度試す
        Print(L"trying again ...\n");
        get_memmap(map);
        status = gBS->ExitBootServices(IM, map->map_key);
        if (EFI_ERROR(status)) {
            //どうしても無理なら終了
            PrintError();
            Print(L"Fatal Error :Exit Boot Services\n");
            gBS->Exit(IM, EFI_SUCCESS, 0, NULL);
        }
    }
    return EFI_SUCCESS;
}

EFI_STATUS EFIAPI uefi_main(EFI_HANDLE IM, EFI_SYSTEM_TABLE *sys_table) {
    EFI_STATUS status;
    //Welcome
    gBS->SetWatchdogTimer(0, 0 ,0, NULL);
    PrintOK();
    Print(L"Welcome to NeoBoot !");
    // MemoryMap
    struct MemoryMap map;
    map.map_size = 0;
    map.map_key = 0;
    map.descriptor_size = 0;
    // Get Memory Map
    get_memmap(&map);
    // Open Volume
    EFI_FILE_PROTOCOL *root_dir;
    open_root_dir(IM, &root_dir);
    // Create "memmap.blmm" BLMM = Boot Loader Memory Map
    EFI_FILE_PROTOCOL *memmap_f;
    status = root_dir->Open(root_dir, &memmap_f, L"\\memmap.blmm", EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE, 0);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Create a memory map file 'memmap.blmm'");
    }
    // Print Memory Map
    print_memmap(&map);
    // Save Memory Map
    save_memmap(&map, memmap_f);
    // Get Info Kernel
    EFI_FILE_PROTOCOL *kernel_f = NULL;
    UINT64 entry_addr = 0;
    entry_t *e_entry = NULL;
    load_kernel(kernel_f, root_dir, entry_addr, e_entry);
    // Print Entry Point Address
    Print(L"entry = %x\n", e_entry);
    // Exit Boot Services
    exit_bs(IM, &map);
    //これ以降にprintを呼び出しては、いけない
    //カーネルにジャンプ
    __asm__ volatile("jmp *%0" :: "r"(e_entry));
    //無限ループしないとログとか見れない
    while(1) __asm__ ("hlt");
}
