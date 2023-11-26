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

// For Debug
#include "uefilib/inc/efi.h"
#include "uefilib/inc/efilib.h"

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
        Print(L"Open LIP Protocol : %r\n", status);
        return status;
    };
    // Simple File System Protocol
    status = gBS->OpenProtocol(lip->DeviceHandle, &gEfiSimpleFileSystemProtocolGuid, (VOID **)&sfsp, IM, NULL, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Open SFSP Protocol : %r\n", status);
        return status;
    };
    //記憶装置について取得
    status = sfsp->OpenVolume(sfsp, root);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Open Volume : %r\n", status);
        return status;
    };
    return EFI_SUCCESS;
}

//メモリーマップ関係

//メモリーマップを取得
EFI_MEMORY_DESCRIPTOR *get_memmap (UINTN *NoEntries, UINTN *MapKey, UINTN *DescriptorSize,UINT32 *DescriptorVersion) {
    EFI_STATUS              Status;
    EFI_MEMORY_DESCRIPTOR   *Buffer;
    UINTN                   BufferSize;

    BOOLEAN TryAgain;

    // GrowBuffer ループの初期化
    Status = EFI_SUCCESS;
    Buffer = NULL;
    BufferSize = sizeof(EFI_MEMORY_DESCRIPTOR);

    // GrowBuffer のロジックを使用して実際の関数を呼び出す
    do {
        TryAgain = GrowBuffer(&Status, (VOID **)&Buffer, BufferSize);

        if (TryAgain) {
            Status = uefi_call_wrapper(BS->GetMemoryMap, 5, &BufferSize, Buffer, MapKey, DescriptorSize, DescriptorVersion);
            Status = gBS->GetMemoryMap(&BufferSize, Buffer, MapKey, DescriptorSize, DescriptorVersion);
        }

    } while (TryAgain);

    // バッファーサイズを NoEntries に変換
    if (!EFI_ERROR(Status)) {
        *NoEntries = BufferSize / *DescriptorSize;
    }

    return Buffer;
}


//種類を特定
UINT16 *get_memtype_name(EFI_MEMORY_TYPE type)
{
    switch (type)
    {
    case EfiReservedMemoryType:
        return L"EfiReservedMemoryType";
    case EfiLoaderCode:
        return L"EfiLoaderCode";
    case EfiLoaderData:
        return L"EfiLoaderData";
    case EfiBootServicesCode:
        return L"EfiBootServicesCode";
    case EfiBootServicesData:
        return L"EfiBootServicesData";
    case EfiRuntimeServicesCode:
        return L"EfiRuntimeServicesCode";
    case EfiRuntimeServicesData:
        return L"EfiRuntimeServicesData";
    case EfiConventionalMemory:
        return L"EfiConventionalMemory";
    case EfiUnusableMemory:
        return L"EfiUnusableMemory";
    case EfiACPIReclaimMemory:
        return L"EfiACPIReclaimMemory";
    case EfiACPIMemoryNVS:
        return L"EfiACPIMemoryNVS";
    case EfiMemoryMappedIO:
        return L"EfiMemoryMappedIO";
    case EfiMemoryMappedIOPortSpace:
        return L"EfiMemoryMappedIOPortSpace";
    case EfiPalCode:
        return L"EfiPalCode";
    case EfiPersistentMemory:
        return L"EfiPersistentMemory";
    case EfiMaxMemoryType:
        return L"EfiMaxMemoryType";
    default:
        return L"InvalidMemoryType";
    }
};

//メモリーマップを画面に表示
EFI_STATUS print_memmap(struct MemoryMap *map) {
    Print(L"\n [ INFO ] MemoryMap \n");
    UINT16 *header = L"Index, Buffer, Type, Type(name), PhysicalStart, VirtualStart, NumberOfPages, Size, Attribute";
    Print(L"%-ls\n", header);
    EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR *)map->buffer;
    for (UINT32 i = 0; i < map->memmap_desc_entry; i++) {
        Print(L"%02d, %016x, %02x, %-ls, %016x, %016x, %016x, %d, %016x \n", i, desc, desc->Type, get_memtype_name(desc->Type), desc->PhysicalStart, desc->VirtualStart, desc->NumberOfPages, desc->NumberOfPages, desc->Attribute);
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
        Print(L"Open 'kernel.elf' : %r\n ", status);
        return status;
    }
    // Get Info Kernel File
    UINTN kernel_f_info_size = sizeof(EFI_FILE_INFO) + sizeof(CHAR16) *12;
    UINT8 kernel_f_info_buffer[kernel_f_info_size];
    status = kernel_f->GetInfo(kernel_f, &gEfiFileInfoGuid, &kernel_f_info_size, kernel_f_info_buffer);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Get Info Kernel File 'kernel.elf' %r\n ", status);
    }
    // Read Kernel File Info
    EFI_FILE_INFO *kernel_f_info = (EFI_FILE_INFO *)kernel_f_info_buffer;
    UINTN kernel_f_size = kernel_f_info->FileSize;
    VOID *kernel_buffer;
    // Allocate Pool
    status = gBS->AllocatePool(EfiLoaderData, kernel_f_size, &kernel_buffer);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Allocate Pool : %r\n", status);
    }
    // Read Kernel
    status = kernel_f->Read(kernel_f, &kernel_f_size, kernel_buffer);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Read Kernel File : %r\n", status);
    }
    // Allocate Pages
    elf64_ehdr *kernel_ehdr = (elf64_ehdr *)kernel_buffer;
    UINT64 kernel_start_addr = 0, kernel_end_addr = 0;
    calc_address_range(kernel_ehdr, kernel_start_addr, kernel_end_addr);
    UINTN num_pages = (kernel_end_addr - kernel_start_addr + 0xfff) / 0x1000;
    status = gBS->AllocatePages(AllocateAddress, EfiLoaderData, num_pages, &kernel_start_addr);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Allocate Pool : %r\n", status);
    }
    // Copy Segments
    copy_load_segments(kernel_ehdr);
    status = gBS->FreePool(kernel_buffer);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Free Pool : %r\n", status);
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
            //どうしても無理なら止まってPCの起動を阻止する
            PrintError();
            Print(L"Fatal Error :Exit Boot Services, %r\n", status);
            while(1);
        }
    }
    return EFI_SUCCESS;
}

EFI_STATUS EFIAPI uefi_main(EFI_HANDLE IM, EFI_SYSTEM_TABLE *sys_table) {
    EFI_STATUS status;
    //Welcome
    gBS->SetWatchdogTimer(0, 0 ,0, NULL);
    PrintOK();
    Print(L"Welcome to NeoBoot !\n");
    // MemoryMap
    struct MemoryMap map;
    map.map_size = 0;
    map.map_key = 0;
    map.descriptor_size = 0;
    // Get Memory Map
    get_memmap(&map);
    //Print
    Print(L"%x, %d", map.map_key, map.map_key);
    // Open Volume
    EFI_FILE_PROTOCOL *root_dir;
    open_root_dir(IM, &root_dir);
    // Create "memmap.blmm" BLMM = Boot Loader Memory Map
    EFI_FILE_PROTOCOL *memmap_f;
    status = root_dir->Open(root_dir, &memmap_f, L"\\memmap.blmm", EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE, 0);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Create a memory map file 'memmap.blmm'\n");
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
