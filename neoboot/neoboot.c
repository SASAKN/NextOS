// neoboot v.0.01
#include "include/efi.h"
#include "include/proto.h"
#include "include/config.h"
#include "include/elf.h"
#include "include/graphics.h"
#include "include/mem.h"
#include "include/macros.h"
#include "include/status.h"

/* GUIDの定義 */
EFI_GUID gEfiLoadedProtocolGuid = EFI_LOADED_IMAGE_PROTOCOL_GUID;
EFI_GUID gEfiSimpleFileSystemProtocolGuid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;

/* CPUを停止 */
void Halt(void) {
    while(1) __asm__("hlt");
}

/* メモリーマップの取得 */
EFI_STATUS GetMemoryMap(struct MemoryMap *map) {
    EFI_STATUS status;
    if (map->buffer == NULL) {
        return EFI_BUFFER_TOO_SMALL;
    }

    map->map_size = map->buffer_size;
    status = gBS->GetMemoryMap(&map->map_size, (EFI_MEMORY_DESCRIPTOR*)map->buffer, &map->map_key, &map->descriptor_size, &map->descriptor_version);
    return status;
}

/* EFIファイルの場所を示す */
EFI_STATUS PrintEfiFileLocation(IN EFI_HANDLE ImageHandle)
{
    EFI_LOADED_IMAGE_PROTOCOL *lip;
    EFI_STATUS status;
    status = gBS->OpenProtocol(ImageHandle, &gEfiLoadedProtocolGuid, (VOID **)&lip, ImageHandle, NULL, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (EFI_EROOR(status))
    {
        custom_printf("EfiFileLocation(lip->FilePath) : Unknown\n");
        custom_printf("This is not a fatal error, so proceed with the process.\n");
    };
    custom_printf("[ INFO ]EfiFileLocation\n");
    custom_wprintf(L"EfiFileLocation(lip->FilePath) : %s", DPTTP->ConvertDevicePathToText(lip->FilePath, FALSE, FALSE));
    return status;
}

/* ルートディレクトリーが開かれる */
EFI_STATUS OpenRootDir(EFI_HANDLE ImageHandle, EFI_FILE_PROTOCOL **root) {
    EFI_STATUS status;
    EFI_LOADED_IMAGE_PROTOCOL *loaded_image;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *fs;
    status = gBS->OpenProtocol(ImageHandle, &gEfiLoadedProtocolGuid, (VOID**)&fs, ImageHandle, NULL, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
    if (EFI_EROOR(status))
    {
        custom_printf("Failed to open loaded image protocol\n");
        Halt();
    };
    status = gBS->OpenProtocol(loaded_image->DeviceHandle, &gEfiSimpleFileSystemProtocolGuid, (VOID **)&fs, ImageHandle, NULL, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
    if (EFI_EROOR(status))
    {
        custom_printf("Failed to open simple file system protocol\n");
        Halt();
    };
    //OpenVolumeする
    fs->OpenVolume(fs, root);
}

/* ベンダーなどの情報を表示 */
void PrintEfiConfigurationTable(void)
{
  UINT64 i;
  custom_printf("[ INFO ] EfiConfigurationTable\n");
  for (i = 0; i < gST->NumberOfTableEntries; i++)
  {
    PrintHex(i, 1);
    putc(L':');
    PrintHex((unsigned long long)&gST->ConfigurationTable[i], 16);
    putc(L':');
    PrintHex(gST->ConfigurationTable[i].VendorGuid.Data1, 8);
    putc(L' ');
    PrintHex(gST->ConfigurationTable[i].VendorGuid.Data2, 4);
    putc(L' ');
    PrintHex(gST->ConfigurationTable[i].VendorGuid.Data3, 4);
    putc(L' ');
    unsigned char j;
    for (j = 0; j < 8; j++)
      PrintHex(gST->ConfigurationTable[i].VendorGuid.Data4[j], 2);
    putc(L':');
    PrintHex((unsigned long long)gST->ConfigurationTable[i].VendorTable,
             16);
    puts(L"\r\n");
  }
};

EFI_STATUS EfiMain(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS status;
    // UEFIの初期化
    gST = SystemTable;
    gBS = gST->BootServices;
    gRT = gST->RuntimeServices;
    PrintOK(SystemTable);
    custom_printf("Init UEFI\n");
    //  UEFIファイルの場所を表示
    PrintEfiFileLocation(ImageHandle);
    // ベンダーの情報などを表示
    PrintEfiConfigurationTable();
    // 作者などの表示
    custom_printf("Copyright: SASAKEN NeoBoot");
    // NeoBootが起動
    custom_printf("Starting NeoBoot....");
    // ボリュームを開く
    EFI_FILE_PROTOCOOL *root_dir;
    OpenRootDir(ImageHandle, &root_dir);
    SFSP->O
    // メモリーマップ構造体の初期化
    CHAR8 memmap_buffer[MEM_DESC_SIZE];
    UINT64 memmap_size = MEM_DESC_SIZE;
    struct MemoryMap map;
    map.buffer = memmap_buffer;
    map.buffer_size = memmap_size;
    map.descriptor_size = 0;
    map.descriptor_version = 0;
    map.map_key = 0;
    map.map_size = memmap_size;
    //メモリーマップの取得
    GetMemoryMap(&map);

    return EFI_SUCCESS;
}