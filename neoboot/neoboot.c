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
EFI_GUID gEfiFileInfoGuid = EFI_FILE_INFO_ID;

/* CPUを停止 */
void Halt(void) {
    custom_printf("[ INFO ] CPU HALT");
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
    if (EFI_ERROR(status))
    {
        PrintWarn(gST);
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
    if (EFI_ERROR(status))
    {
        PrintError(gST);
        custom_printf("Failed to open loaded image protocol\n");
        Halt();
    };
    status = gBS->OpenProtocol(loaded_image->DeviceHandle, &gEfiSimpleFileSystemProtocolGuid, (VOID **)&fs, ImageHandle, NULL, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
    if (EFI_ERROR(status))
    {
        PrintError(gST);
        custom_printf("Failed to open simple file system protocol\n");
        Halt();
    };
    //OpenVolumeする
    status = fs->OpenVolume(fs, root);
    if (EFI_ERROR(status)) {
        PrintError(gST);
        custom_printf("Failed to open volume.\n");
        Halt();
    }
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
    EFI_FILE_PROTOCOL *root_dir;
    OpenRootDir(ImageHandle, &root_dir);
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
    //メモリーマップの取得,表示
    GetMemoryMap(&map);
    print_memmap(&map);
    //カーネルのロード
    EFI_FILE_PROTOCOL *kernel_file;
    root_dir->Open(root_dir, &kernel_file, L"\\kernel.o", EFI_FILE_MODE_READ, 0);
    UINTN file_info_size = sizeof(EFI_FILE_INFO) + sizeof(CHAR16) * 12;
    UINT8 file_info_buf[file_info_size];
    status = kernel_file->GetInfo(kernel_file, &gEfiFileInfoGuid, &file_info_size, file_info_buf);
    assert(status, L"KernelFile->GetInfo");
    EFI_FILE_INFO* file_info = (EFI_FILE_INFO *)file_info_buf;
    UINTN kernel_file_size = file_info->FileSize;
    EFI_PHYSICAL_ADDRESS kernel_base_addr = 0x100000;
    gBS->AllocatePages(AllocateAddress, EfiLoaderData, (kernel_file_size + 0xfff) / 0x1000, &kernel_base_addr);
    assert(status, L"Allocate Pages");
    status = kernel_file->Read(kernel_file, &kernel_file_size, (VOID*)kernel_base_addr);
    assert(status, L"KernelFile->Read");
    //カーネルのファイルの情報を表示
    char buf_kern_info[200];
    text_gen(buf_kern_info, sizeof(buf_kern_info), "Kernel :0x%x (%u bytes)\n", kernel_base_addr, kernel_file_size);
    custom_printf("%s\n", buf_kern_info);
    // UEFIから離脱
    status = gBS->ExitBootServices(ImageHandle, map.map_key);
    char buf_bs_error[200];
    if (EFI_ERROR(status)) {
        status = GetMemoryMap(&map);
        if (EFI_ERROR(status)) {
            text_gen(buf_bs_error, sizeof(buf_bs_error), "%x", status);
            custom_printf("Failed to get memory map :%s\n", buf_bs_error);
        }
        // エラーメッセージをクリア
        for (int i = 0; i < sizeof(buf_bs_error); i++) {
            buf_bs_error[i] = '\0';
        }
        status = gBS->ExitBootServices(ImageHandle, map.map_key);
        if (EFI_ERROR(status)) {
            text_gen(buf_bs_error, sizeof(buf_bs_error), "%x", status);
            custom_printf("Failed to exit boot services :%s\n", buf_bs_error);  
        }
    }
    //ジャンプ
    __asm__ volatile("jmp *0x100000");
    return EFI_SUCCESS;
}