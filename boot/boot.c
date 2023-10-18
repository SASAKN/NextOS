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

/* ベンダーなどの情報を表示 */
void PrintEfiConfigurationTable(void) {
  UINT64 i;
  for (i = 0; i < ST->NumberOfTableEntries; i++) {
    PrintHex(i, 1);
		putc(L':');
    PrintHex((unsigned long long)&ST->ConfigurationTable[i], 16);
		putc(L':');
		PrintHex(ST->ConfigurationTable[i].VendorGuid.Data1, 8);
		putc(L' ');
		PrintHex(ST->ConfigurationTable[i].VendorGuid.Data2, 4);
		putc(L' ');
		PrintHex(ST->ConfigurationTable[i].VendorGuid.Data3, 4);
		putc(L' ');
		unsigned char j;
		for (j = 0; j < 8; j++)
			PrintHex(ST->ConfigurationTable[i].VendorGuid.Data4[j], 2);
		putc(L':');
		PrintHex((unsigned long long)ST->ConfigurationTable[i].VendorTable,
		     16);
		puts(L"\r\n");
  }
}


/* Entry Point ! */
/* 起動時の最初に実行されます。 */
EFI_STATUS EfiMain(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable)
{
    efi_init(SystemTable); /* UEFIの全てを初期化する関数 */
    UINT64 status;
    custom_printf("Starting NEOS BootLoader ...\n"); /* ようこそメッセージ */
    PrintEfiFileLocation(ImageHandle); /* 実行しているEFIファイルの場所を表示 */
    PrintEfiConfigurationTable(); /* ConfiguratonTableの表示 */
    /* ファイルを開く操作 */
    EFI_FILE_PROTOCOL *root;
    status = SFSP->OpenVolume(SFSP, &root);
    assert(status, L"[ Error! ] SFSP->OpenVolume\n");
    PrintOK(SystemTable);
    custom_printf("OpenVolume\n");
    // /* メモリーバッファー */
    // CHAR8 memmap_buf[MEM_DESC_SIZE];
    // UINT64 memmap_size = MEM_DESC_SIZE;
    // /* 構造体の初期化 */
    // struct MemoryMap map;
    // map.buffer = memmap_buf;
    // map.buffer_size = memmap_size;
    // /* ファイルの保存場所などの指定 */
    // /* メモリーマップの初期化,表示 */
    // init_memmap(&map);
    // print_memmap(&map);
    /* All Done ! */
    custom_printf("All Done !\n");
    while (TRUE);
    return EFI_SUCCESS;
};