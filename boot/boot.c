/* Neos Boot Loader v0.01 */

#include "include/efi.h"
#include "include/guid.h"
#include "include/proto.h"
#include "include/config.h"
#include "include/elf.h"
#include "include/graphics.h"
#include "include/mem.h"

EFI_STATUS OpenRootDir(EFI_HANDLE image_handle, EFI_FILE_PROTOCOL** root) {
    EFI_LOADED_IMAGE_PROTOCOL* loaded_image;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* fs;

    BS->OpenProtocol(image_handle, &EfiLoadedImageProtocolGuid, (VOID**)&fs, image_handle, NULL, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
    fs->OpenVolume(fs, root);
    return EFI_SUCCESS;
}


/* Entry Point ! */
/* 起動時の最初に実行されます。 */
EFI_STATUS EfiMain(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable)
{
    custom_printf("Welcome to Neos !\n");
    efi_init(SystemTable); /* UEFIの全てを初期化する関数 */
    /* メモリーバッファー */
    CHAR8 memmap_buf[MEM_DESC_SIZE];
    UINT64 memmap_size = MEM_DESC_SIZE;
    /* 構造体の初期化 */
    struct MemoryMap map;
    map.buffer = memmap_buf;
    map.buffer_size = memmap_size;
    /* メモリーマップの初期化と、表示 */
    init_memmap(&map);
    print_memmap(&map);
    /* ファイルプロトコルを開く */
    EFI_FILE_PROTOCOL* root_dir;
    OpenRootDir(image_handle, &root_dir);
    EFI_FILE_PROTOCOL* memmap_file;
    root_dir->Open(root_dir, &memmap_file, L"\\memmap", )
    while (1);
    return EFI_SUCCESS;
};