// For using UEFI Library
#include  <Uefi.h>
#include  <Library/UefiLib.h>
#include  <Library/UefiBootServicesTableLib.h>
#include  <Library/PrintLib.h>
#include  <Library/MemoryAllocationLib.h>
#include  <Library/BaseMemoryLib.h>
#include  <Protocol/LoadedImage.h>
#include  <Protocol/SimpleFileSystem.h>
#include  <Guid/FileInfo.h>

// Base Include Files
#include "mem.h"
#include "file.h"
#include "elf.h"
#include "common.h"

// Print
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

// Init UEFI
void init_uefi(void) {
    gBS->SetWatchdogTimer(0, 0 ,0, NULL);
    PrintOK();
    Print(L"Welcome to NextOS \n");
}

EFI_STATUS EFIAPI uefi_main(EFI_HANDLE IM, EFI_SYSTEM_TABLE *sys_table) {
    // Welcome
    init_uefi();
    // Init MemoryMap
    struct MemoryMap map;
    char *buffer = NULL;
    init_memmap(&map, buffer);
    // Open Root Directory
    EFI_FILE_PROTOCOL *root;
    open_root_dir(IM, &root);
    // Get it, Print it and Save it
    get_memmap(&map);
    print_memmap(&map);
    save_memmap(&map, root);
    return EFI_SUCCESS;
} 


