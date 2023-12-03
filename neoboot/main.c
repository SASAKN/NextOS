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

    // Get info about the kernel file
    EFI_FILE_PROTOCOL* kernel_file;
    root_dir->Open(
      root_dir, &kernel_file, L"\\kernel.elf",
      EFI_FILE_MODE_READ, 0);

    UINTN file_info_size = sizeof(EFI_FILE_INFO) + sizeof(CHAR16) * 12;
    UINT8 file_info_buffer[file_info_size];
    kernel_file->GetInfo(
        kernel_file, &gEfiFileInfoGuid,
        &file_info_size, file_info_buffer);

    EFI_FILE_INFO* file_info = (EFI_FILE_INFO*)file_info_buffer;
    UINTN kernel_file_size = file_info->FileSize;

    // Allocate kernel
    EFI_PHYSICAL_ADDRESS kernel_base_addr = 0x100000;
    gBS->AllocatePages(
      AllocateAddress, EfiLoaderData,
      (kernel_file_size + 4095) / 4096, &kernel_base_addr);
    kernel_file->Read(kernel_file, &kernel_file_size, (VOID*)kernel_base_addr);
    Print(L"Kernel: 0x%0lx (%lu bytes)\n", kernel_base_addr, kernel_file_size);

    
    // Halt
    while (1) __asm__ ("hlt");
    return EFI_SUCCESS;
} 