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
#include "elf_loader.h"

void init_uefi(void) {
    // Do not reboot
    gBS->SetWatchdogTimer(0, 0 ,0, NULL);
    // Interval of priting text
    gBS->Stall(50000);
    // Ascii art
    Print(L" __    __                        __       ______    ______  \n");
    Print(L"/  \\  /  |                      /  |     /      \\  /      \\  \n");
    Print(L"$$  \\ $$ |  ______   __    __  _$$ |_   /$$$$$$  |/$$$$$$  | \n");
    Print(L"$$$  \\$$ | /      \\ /  \\  /  |/ $$   |  $$ |  $$ |$$ \\__$$/ \n");
    Print(L"$$$$  $$ |/$$$$$$  |$$  \\/$$/ $$$$$$/   $$ |  $$ |$$      \\ \n");
    Print(L"$$ $$ $$ |$$    $$ | $$  $$<    $$ | __ $$ |  $$ | $$$$$$  |\n");
    Print(L"$$ |$$$$ |$$$$$$$$/  /$$$$  \\   $$ |/  |$$ \\__$$ |/  \\__$$ |\n");
    Print(L"$$ | $$$ |$$       |/$$/ $$  |  $$  $$/ $$    $$/ $$    $$/ \n ");
    Print(L"$$/   $$/  $$$$$$$/ $$/   $$/    $$$$/   $$$$$$/   $$$$$$/  \n\n");
    // Welcome
    PrintOK();
    Print(L"Welcome to NextOS \n");
}

EFI_STATUS EFIAPI efi_main(EFI_HANDLE IM, EFI_SYSTEM_TABLE *sys_table) {
    // Welcome
    init_uefi();
    // Init MemoryMap
    memmap map;
    init_memmap(&map);
    // Open Root Directory
    EFI_FILE_PROTOCOL *root;
    open_root_dir(IM, &root);
    // Get it, Print it and Save it
    get_memmap(&map);
    print_memmap(&map);
    // Print memory map info
    Print(L"\n[ INFO ] Memory Map Info \n");
    Print(L" map : %08x\n map_size : %lu\n desc_size : %lu\n desc_ver : %lu\n key : %lu\n entry : %lu  \n\n", map.buffer, map.map_size, map.desc_size, map.desc_ver, map.map_key, map.desc_entry);
    EFI_FILE_PROTOCOL *memmap_f;
    memmap_f = NULL;
    save_memmap(&map, memmap_f, root);
    // Load kernel
    UINTN kernel_size = 0;
    EFI_FILE_PROTOCOL *kernel_file = NULL;
    open_file_read(root, L"\\kernel.elf", kernel_file, &kernel_size);
    // Print kernel file size
    Print(L"[ INFO ] Kernel File Size : %lu bytes. \n", kernel_size);
    // Read kernel
    VOID *kernel_buffer = NULL;
    read_kernel(kernel_file, kernel_size, kernel_buffer);
    // Halt
    while (1) __asm__ ("hlt");
    return EFI_SUCCESS;
} 