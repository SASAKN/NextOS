/* Neos Boot Loader v0.01 */

#include "include/efi.h"
#include "include/proto.h"
#include "include/config.h"
#include "include/elf.h"
#include "include/graphics.h"
#include "include/mem.h"

/* 実行中のファイルの場所を表示 */
EFI_STATUS PrintEfiFileLocation(IN EFI_HANDLE ImageHandle) {
    EFI_LOADED_IMAGE_PROTOCOL *lip;
    UINT64 status = ST->BootServices->OpenProtocol(ImageHandle, &lip_guid, (VOID**)&lip, ImageHandle, NULL, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    assert(status, L"OpenProtocol");
    custom_wprintf(L"EfiFileLocation(lip->FilePath) : %s", DPTTP->ConvertDevicePathToText(lip->FilePath, FALSE, FALSE));
    puts(L"\r\n");
    return status;
};

EFI_STATUS OpenRootDir(EFI_HANDLE image_handle, EFI_FILE_PROTOCOL** root, EFI_SYSTEM_TABLE* system_table) {
  EFI_LOADED_IMAGE_PROTOCOL* loaded_image;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* fs;
  EFI_STATUS status;

  status = system_table->BootServices->OpenProtocol(
      image_handle,
      &lip_guid,
      (VOID**)&loaded_image,
      image_handle,
      NULL,
      EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
    assert(status, L"OpenProtocol");
  status = system_table->BootServices->OpenProtocol(
      loaded_image->DeviceHandle,
      &sfsp_guid,
      (VOID**)&fs,
      image_handle,
      NULL,
      EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
    assert(status, L"OpenProtocol");

  fs->OpenVolume(fs, root);

  return EFI_SUCCESS;
}


/* Entry Point ! */
/* 起動時の最初に実行されます。 */
EFI_STATUS EfiMain(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable)
{
    efi_init(SystemTable); /* UEFIの全てを初期化する関数 */
    custom_printf("Welcome to Neos !\n"); /* ようこそメッセージ */
    PrintEfiFileLocation(ImageHandle); /* 実行しているEFIファイルの場所を表示 */
    /* メモリーバッファー */
    CHAR8 memmap_buf[MEM_DESC_SIZE];
    UINT64 memmap_size = MEM_DESC_SIZE;
    /* 構造体の初期化 */
    struct MemoryMap map;
    map.buffer = memmap_buf;
    map.buffer_size = memmap_size;
    /* メモリーマップの初期化,表示 */
    init_memmap(&map);
    print_memmap(&map);
    custom_printf("All Done !\n");
    while (TRUE);
    return EFI_SUCCESS;
};