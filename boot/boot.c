/* Neos Boot Loader v0.01 */

#include "include/efi.h"
#include "include/proto.h"
#include "include/config.h"
#include "include/elf.h"
#include "include/graphics.h"
#include "include/mem.h"

/* UEFIから離脱 */
void ExitBootLoader(EFI_HANDLE *ImageHandle, struct MemoryMap map) {
  EFI_STATUS status;
  status = BS->ExitBootServices(ImageHandle, map.map_key);
  assert(status, L"ExitBootServices");
} 

/* カーネルの読み込み関数 */
void LoadKernel(EFI_FILE_PROTOCOL* root_dir) {
  EFI_FILE_PROTOCOL* kernel_file;
  EFI_STATUS status;
  status = root_dir->Open(root_dir, &kernel_file, KERNEL_FILE, EFI_FILE_MODE_READ, 0);
  assert(status, L"KernelLoadError !(root->Open)");
  UINTN file_info_size = sizeof(EFI_FILE_INFO) + sizeof(CHAR16) * 12;
  UINT8 file_info_buffer[file_info_size];
  kernel_file->GetInfo(kernel_file, &fi_guid, &file_info_size, file_info_buffer);
  EFI_FILE_INFO* file_info = (EFI_FILE_INFO*)file_info_buffer;
  UINTN kernel_file_size = file_info->FileSize;
  EFI_PHYSICAL_ADDRESS kernel_base_addr = 0x100000;
  /* メモリーにファイルを置く */
  BS->AllocatePages(AllocateAddress, EfiLoaderData, (kernel_file_size + 0xfff) / 0x1000, &kernel_base_addr);
  kernel_file->Read(kernel_file, &kernel_file_size, (VOID*)kernel_base_addr);
  char buffer[100];
  text_gen(buffer, sizeof(buffer), "Kernel : 0x%x (%u bytes)\n", kernel_base_addr, kernel_file_size);
  custom_printf("%s\n", buffer);
};

void call_kernel(EFI_PHYSICAL_ADDRESS kernel_base_addr) {
  UINT64 entry_addr = *(UINT64*)(kernel_base_addr + 24);
  typedef void EntryPointType(void);
  EntryPointType* entry_point = (EntryPointType*)entry_addr;
  entry_point();
}

/* 実行中のファイルの場所を表示 */
EFI_STATUS PrintEfiFileLocation(IN EFI_HANDLE ImageHandle) {
    EFI_LOADED_IMAGE_PROTOCOL *lip;
    UINT64 status = ST->BootServices->OpenProtocol(ImageHandle, &lip_guid, (VOID**)&lip, ImageHandle, NULL, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    assert(status, L"OpenProtocol");
    custom_printf("[ INFO ]EfiFileLocation\n");
    custom_wprintf(L"EfiFileLocation(lip->FilePath) : %s", DPTTP->ConvertDevicePathToText(lip->FilePath, FALSE, FALSE));
    puts(L"\r\n");
    return status;
};

/* ベンダーなどの情報を表示 */
void PrintEfiConfigurationTable(void) {
  UINT64 i;
  custom_printf("[ INFO ] EfiConfigurationTable\n");
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
};


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
    /* ファイル用の定義 */
    EFI_FILE_PROTOCOL *root_dir;
    EFI_FILE_PROTOCOL *memmap_file;
    /* ボリュームを開く */
    status = SFSP->OpenVolume(SFSP, &root_dir); /* Root_Dirに読み込んでる */
    assert(status, L"[ Error! ] SFSP->OpenVolume\n");
    PrintOK(SystemTable);
    custom_printf("OpenVolume\n");
    /* メモリーバッファー */
    CHAR8 memmap_buf[MEM_DESC_SIZE];
    UINT64 memmap_size = MEM_DESC_SIZE;
    /* 構造体の初期化 */
    struct MemoryMap map;
    map.buffer = memmap_buf;
    map.buffer_size = memmap_size;
    /* メモリーマップの初期化,表示,保存 */
    init_memmap(&map);
    print_memmap(&map);
    /* カーネルの読み込み */
    custom_printf("Loading Kernel....");
    /* カーネルの読み込み処理 */
    LoadKernel(root_dir);
    /* ブートローダーから離脱 */
    ExitBootLoader(ImageHandle, map);
    /* All Done ! */
    custom_printf("All Done !\n");
    while (TRUE);
    return EFI_SUCCESS;
};