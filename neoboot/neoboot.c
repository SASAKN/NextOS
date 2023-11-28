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
#include  <Guid/FileInfo.h>

#include "include/memory_map.h"
#include "include/file.h"
#include "include/proto.h"
#include "include/elf.h"

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
    DIR *root;
    open_root_dir(IM, &root);
    // Get it, Print it and Save it
    get_memmap(&map);
    print_memmap(&map);
    save_memmap(&map, root);
    return EFI_SUCCESS;
} 


