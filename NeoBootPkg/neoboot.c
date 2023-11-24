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

// 色付きの特殊文字の関数

void PrintOK(void)
{
    gST->ConOut->SetAttribute(ST->ConOut, 0x02); /* 緑で、OKを表示 */
    gST->ConOut->OutputString(ST->ConOut, L"[ OK ]");
    gST->ConOut->SetAttribute(ST->ConOut, 0x0F); /* 白に戻す */
};

void PrintWarn(void)
{
    gST->ConOut->SetAttribute(ST->ConOut, 0x0E); /* 黄色で、Warnを表示 */
    gST->ConOut->OutputString(ST->ConOut, L"[ Warn ]");
    gST->ConOut->SetAttribute(ST->ConOut, 0x0F); /* 白に戻す */
};

void PrintError(void)
{
    gST->ConOut->SetAttribute(ST->ConOut, 0x04); /* あかで、Errorを表示 */
    gST->ConOut->OutputString(ST->ConOut, L"[ Error ! ]");
    gST->ConOut->SetAttribute(ST->ConOut, 0x0F); /* 白に戻す */
};

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
    Print(L"Get Memory Map");
    return EFI_SUCCESS;
};

//メモリーマップを画面に表示
EFI_STATUS print_memmap(struct MemoryMap *map) {
    EFI_STATUS status;
    Print(L"\n [ INFO ] MemoryMap \n");
    CHAR8 *header = "Index, Buffer, Type, Type(name), PhysicalStart, VirtualStart, NumberOfPages, Size, Attribute";
    Print("%s", )
    UINT32 i;
    EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR *)map->buffer;
    for (i = 0; i < map->memmap_desc_entry; i++) {
        Print(L"%02d, %016x, %02x, %s, %016x, %016x, %016x, %d, %016x \n", i, desc, desc->Type, get_memtype_name(desc->Type), desc->PhysicalStart, desc->VirtualStart, desc->NumberOfPages, desc->NumberOfPages, desc->Attribute);
        desc = (EFI_MEMORY_DESCRIPTOR *)((UINT8 *)desc + map->descriptor_size);
    }
    Print(L"\n");
    PrintOK();
    Print(L"Print Memory Map");
    return EFI_SUCCESS;
};

//メモリーマップをファイルに保存する関数
EFI_STATUS save_memmap(struct MemoryMap *map, EFI_FILE_PROTOCOL *f) {
    EFI_STATUS status;
    CHAR8 memmap_buffer[1024];
    UINTN size;
    char *header = "Index, Buffer, Type, Type(name), PhysicalStart, VirtualStart, NumberOfPages, Size, Attribute";
    size = AsciiStrlen(header);
    //ヘッダーの書き込み
    status = f->Write(f, &size, header);
    if(EFI_ERROR(status)) {
        PrintError();
        Print(L"Open File");
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
            Print(L"Save Memory Map");
            return status;
        }
    }
}
