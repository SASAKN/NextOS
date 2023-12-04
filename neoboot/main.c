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

void calc_load_addr_range(elf64_ehdr *ehdr, EFI_PHYSICAL_ADDRESS *first, EFI_PHYSICAL_ADDRESS *last) {
    elf64_phdr *phdr = ELF64_GET_PHDR(ehdr);
    *first = MAX_UINT64;
    *last = 0;
    for (Elf64_Half i = 0; i < ehdr->e_phnum; i++) {
        if (phdr[i].p_type != PT_LOAD) continue;
        Print(L"[ DEBUG ] PT_LOAD Segment\n");
        *first = MIN(*first, phdr[i].p_vaddr);
        *last = MAX(*last, phdr[i].p_vaddr + phdr[i].p_memsz);
    }
}

void copy_load_segments(elf64_ehdr* ehdr) {
  elf64_phdr* phdr = ELF64_GET_PHDR(ehdr);
  for (Elf64_Half i = 0; i < ehdr->e_phnum; ++i) {
    if (phdr[i].p_type != PT_LOAD) continue;

    UINT64 segm_in_file = (UINT64)ehdr + phdr[i].p_offset;
    CopyMem((VOID*)phdr[i].p_vaddr, (VOID*)segm_in_file, phdr[i].p_filesz);

    UINTN remain_bytes = phdr[i].p_memsz - phdr[i].p_filesz;
    SetMem((VOID*)(phdr[i].p_vaddr + phdr[i].p_filesz), remain_bytes, 0);
  }
}


EFI_STATUS EFIAPI efi_main(EFI_HANDLE IM, EFI_SYSTEM_TABLE *sys_table) {
    // Welcome
    EFI_STATUS status;
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
    EFI_FILE_PROTOCOL *kernel_file;
    status = root->Open(root, &kernel_file, L"\\kernel.elf", EFI_FILE_MODE_READ, 0);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Open the kernel file \n");
    }

    // Get info about the kernel file
    void *kernel_buffer;
    UINTN file_info_size = sizeof(EFI_FILE_INFO) + sizeof(CHAR16) * 12;
    UINT8 file_info_buffer[file_info_size];
    status = kernel_file->GetInfo(kernel_file, &gEfiFileInfoGuid, &file_info_size, file_info_buffer);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Get info the kernel file \n");
    }
    EFI_FILE_INFO *file_info = (EFI_FILE_INFO *)file_info_buffer;
    UINTN file_size = file_info->FileSize;

    // Allocate pool for the kernel file
    status = gBS->AllocatePool(EfiLoaderData, file_size, &kernel_buffer);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Allocate pool\n");
    }

    // Read the kernel file
    status = kernel_file->Read(kernel_file, &file_size, kernel_buffer);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Read the kernel file \n");
    }

    // Load the ELF header
    elf64_ehdr *kernel_ehdr = (elf64_ehdr *)kernel_buffer;
    EFI_PHYSICAL_ADDRESS kernel_start_addr;
    EFI_PHYSICAL_ADDRESS kernel_end_addr;

    // calculate LOAD address range
    calc_load_addr_range(kernel_ehdr, &kernel_start_addr, &kernel_end_addr);
    UINTN num_pages = (kernel_end_addr - kernel_start_addr + 0xfff) / 0x1000;

    kernel_start_addr = 0x101120;
    // Allocate pages
    status = gBS->AllocatePages(AllocateAddress, EfiLoaderData, num_pages, &kernel_start_addr);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Allocate pages\n");
    }

    // copy LOAD segments
    copy_load_segments(kernel_ehdr);

    // Print Kernel Address Range
    Print(L"Kernel : 0x%0lx - 0x%0lx & entry = 0x%0lx\n", kernel_start_addr, kernel_end_addr, kernel_ehdr->e_entry);

    // Free pool
    status = gBS->FreePool(kernel_buffer);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Free pool\n");
    }

    // Locate entry point
    Elf64_Addr entry_addr;
    entry_addr = kernel_ehdr->e_entry;


    // Exit boot services  
    status = gBS->ExitBootServices(IM, map.map_key);
    if (EFI_ERROR(status)) {
        status = get_memmap(&map);
        if (EFI_ERROR(status)) {
            PrintError();
            Print(L"Get Memory Map - Exit BS : %r \n", status);
            while(1);
        }
        status = gBS->ExitBootServices(IM, map.map_key);
        if (EFI_ERROR(status)) {
            PrintError();
            Print(L"Exit BS : %r\n", status);
            while(1);
        }
    }

    // Call kernel
    // entry_addr -= 0x1000UL; //LLD10以降では、これがないと、カーネルが起動しない
    typedef void entry_point_t(void);
    entry_point_t *entry_point = (entry_point_t *)entry_addr;
    entry_point();

    // Halt
    while (1) __asm__ ("hlt");
    return EFI_SUCCESS;
} 