/* Neos Boot Loader v0.01 */

#include "include/efi.h"
#include "include/proto.h"
#include "include/config.h"
#include "include/elf.h"
#include "include/graphics.h"
#include "include/mem.h"

EFI_STATUS PrintEfiFileLocation(void) {
    EFI_LOADED_IMAGE_PROTOCOL *lip;
    UINT64 status = ST->BootServices->OpenProtocol(ImageHandle, &lip_guid, (VOID**)&lip, ImageHandle, NULL, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    assert(status, L"OpenProtocol");
    custom_wprintf(L"EfiFileLocation(lip->FilePath) : %s", DPTTP->ConvertDevicePathToText(lip->FilePath, FALSE, FALSE));
    puts(L"\r\n");
};


// EFI_STATUS OpenRootDir(EFI_HANDLE image_handle, EFI_FILE_PROTOCOL** root) {
//     EFI_LOADED_IMAGE_PROTOCOL* loaded_image;
//     EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* fs;
//     /* 例外の原因は、OpenProtocol */
//     // ST->BootServices->OpenProtocol(image_handle, &lip_guid, (VOID**)&fs, image_handle, NULL, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
//     // ST->BootServices->OpenProtocol(loaded_image->DeviceHandle, &sfsp_guid, (VOID**)&fs, image_handle, NULL, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
//     fs->OpenVolume(fs, root);
//     return EFI_SUCCESS;
// };


/* Entry Point ! */
/* 起動時の最初に実行されます。 */
EFI_STATUS EfiMain(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable)
{
    efi_init(SystemTable); /* UEFIの全てを初期化する関数 */
    custom_printf("Welcome to Neos !\n");
    PrintEfiFileLocation
    // /* メモリーバッファー */
    // CHAR8 memmap_buf[MEM_DESC_SIZE];
    // UINT64 memmap_size = MEM_DESC_SIZE;
    // /* 構造体の初期化 */
    // struct MemoryMap map;
    // map.buffer = memmap_buf;
    // map.buffer_size = memmap_size;
    // /* メモリーマップの初期化と、表示 */
    // init_memmap(&map);
    // print_memmap(&map);
    // /* ファイルプロトコルを開く */
    // EFI_FILE_PROTOCOL* root_dir;
    // OpenRootDir(ImageHandle, &root_dir);
    // /* メモリーマップをファイルに保存 */
    // EFI_FILE_PROTOCOL* memmap_file;
    // root_dir->Open(root_dir, &memmap_file, L"\\memmap", EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE, 0);
    // save_memmap(&map, memmap_file);
    // memmap_file->Close(memmap_file);
    while (1);
    return EFI_SUCCESS;
};