#include  <Uefi.h>
#include  <Library/UefiLib.h>
#include  <Library/UefiBootServicesTableLib.h>
#include  <Library/UefiRuntimeServicesTableLib.h>
#include  <Library/PrintLib.h>
#include  <Library/MemoryAllocationLib.h>
#include  <Library/BaseMemoryLib.h>
#include  <Protocol/LoadedImage.h>
#include  <Protocol/SimpleFileSystem.h>
#include  <Guid/FileInfo.h>

#include "efiio.h"
#include "memory.h"
#include "elf.h"

void init_uefi(void) {
    // Do not reboot
    gBS->SetWatchdogTimer(0, 0 ,0, NULL);
    // Interval of priting text
    gBS->
    // Welcome
    Print(L" __    __                        __       ______    ______  \n")
    Print(L"/  \\  /  |                      /  |     /      \\  /      \\  \n")
    Print(L"$$  \\ $$ |  ______   __    __  _$$ |_   /$$$$$$  |/$$$$$$  | \n")
    Print(L"$$$  \\$$ | /      \\ /  \\  /  |/ $$   |  $$ |  $$ |$$ \\__$$/ \n")
    Print(L"$$$$  $$ |/$$$$$$  |$$  \\/$$/ $$$$$$/   $$ |  $$ |$$      \\ \n")
    Print(L"$$ $$ $$ |$$    $$ | $$  $$<    $$ | __ $$ |  $$ | $$$$$$  |\n")
    Print(L"$$ |$$$$ |$$$$$$$$/  /$$$$  \\   $$ |/  |$$ \\__$$ |/  \\__$$ |\n")
    Print(L"$$ | $$$ |$$       |/$$/ $$  |  $$  $$/ $$    $$/ $$    $$/ \n ")
    Print(L"$$/   $$/  $$$$$$$/ $$/   $$/    $$$$/   $$$$$$/   $$$$$$/  \n")
    PrintOK();
    Print(L"Welcome to NextOS \n");
}

EFI_STATUS EFIAPI main(EFI_HANDLE IM, EFI_SYSTEM_TABLE *sys_table) {
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



