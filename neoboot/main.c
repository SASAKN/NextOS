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

    // Open Root Directory
    EFI_FILE_PROTOCOL *root;
    open_root_dir(IM, &root);

    // Init memory map
    memmap map;
    init_memmap(&map);
    // Get memory map
    get_memmap(&map);
    // Print memory map
    print_memmap(&map);
    // Print memory map info
    Print(L"\n[ INFO ] Memory Map Info \n");
    Print(L" map : %08x\n map_size : %lu\n desc_size : %lu\n desc_ver : %lu\n key : %lu\n entry : %lu  \n\n", map.buffer, map.map_size, map.desc_size, map.desc_ver, map.map_key, map.desc_entry);
    // Save memory map
    EFI_FILE_PROTOCOL *memmap_f;
    memmap_f = NULL;
    save_memmap(&map, memmap_f, root);
    // End Memory Map
    FreePool(map.buffer);

    // Open the kernel file
    EFI_FILE_PROTOCOL *kernel_f = NULL;
    UINTN kernel_f_size = 0;
    open_file_read(root, L"\\kernel.elf", kernel_f, kernel_f_size);
    // Allocate the kernel file
    EFI_PHYSICAL_ADDRESS kernel_base_addr = 0x100000;
    allocate_kernel(kernel_f_size, &kernel_base_addr);
    PrintOK();
    Print(L"Allocate kernel \n");
    // Read Kernel
    read_kernel(kernel_f, &kernel_f_size, &kernel_base_addr);
    PrintOK();
    Print(L"Read kernel \n");
    Print(L"[ INFO ] Kernel File Info \n Size: %lu \n Address: %lx", kernel_f_size, kernel_base_addr);
    // Halt
    while (1) __asm__ ("hlt");
    return EFI_SUCCESS;
} 