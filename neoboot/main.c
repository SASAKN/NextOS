// EDK2 Include
#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/PrintLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Protocol/LoadedImage.h>
#include <Protocol/SimpleFileSystem.h>
#include <Guid/FileInfo.h>

// NeoBoot Include
#include "common.h"
#include "memory.h"
#include "elf.h"
#include "graphics.h"

// Operating System that boot after processing boot process of files

// Copyright NeoBoot 2024

// Initallize
void init_uefi(void) {
  // Do not reboot
  gBS->SetWatchdogTimer(0, 0, 0, NULL);
  // Interval of priting text
  gBS->Stall(50000);
  // Ascii art - OS Logo
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

// Boot Process
EFI_STATUS EFIAPI efi_main(EFI_HANDLE IM, EFI_SYSTEM_TABLE *sys_table) {
  // Welcome
  EFI_STATUS status;
  init_uefi();

  // Open Root Directory
  EFI_FILE_PROTOCOL *root_dir;
  open_root_dir(IM, &root_dir);

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
  save_memmap(&map, memmap_f, root_dir);

  // Freeing up of memory
  FreePool(map.buffer);

  // Open uefi graphics output protocol
  EFI_GRAPHICS_OUTPUT_PROTOCOL *gop;
  open_gop(IM, &gop);

  // Print the screen info
  PrintOK();
  Print(L"Open the graphics protocol\n");
  Print(L"\n[ INFO ] Graphics Info\n Horizontal Resolution : %u\n Vertical Resolution : %u\n Resolution : %ux%u\n Pixel Format Type : %x\n PixelsPerLine : %u\n\n",
        gop->Mode->Info->HorizontalResolution,
        gop->Mode->Info->VerticalResolution,
        gop->Mode->Info->HorizontalResolution,
        gop->Mode->Info->VerticalResolution,
        gop->Mode->Info->PixelFormat,
        gop->Mode->Info->PixelsPerScanLine);
  
  // Make a structure for a frame buffer of the kernel
  fb_config fb_con;
  fb_con.hr = gop->Mode->Info->HorizontalResolution;
  fb_con.vr = gop->Mode->Info->VerticalResolution;
  fb_con.fb_size = gop->Mode->FrameBufferSize;
  fb_con.base_addr = gop->Mode->FrameBufferBase;
  fb_con.pixels_per_scan_line = gop->Mode->Info->PixelsPerScanLine;
  // Pixel Formatの処理は、また後で

  //Note - [ Important ! ]
  //BootParamの変更がこれに以降にあると、いけない
  //BootParamの内容のみがこの前に編集し切るべしである

  // Allocate a temporary structure
  void *bp = NULL;
  EFI_PHYSICAL_ADDRESS bp_addr;
  bp_addr = 0x200000; // Boot paramater address
  gBS->AllocatePages(AllocateAddress, EfiLoaderData, (sizeof(struct _boot_param) + 4095) / 4096, &bp_addr); //Alignmentしないとエラー。

  // Make a structure for the kernel
  struct _boot_param *boot_param = (struct _boot_param *)bp;
  boot_param->fb_setting = fb_con;

  // Know where the structure
  Print(L"[ BOOT CONFIG ADDRESS ] 0x0%p\n", fb_con);

  
  // Load the kernel file into structure
  EFI_FILE_PROTOCOL *kernel_file;
  status = root_dir->Open(root_dir, &kernel_file, L"\\kernel.elf", EFI_FILE_MODE_READ, 0);
  if (EFI_ERROR(status)) {
    Print(L"failed to open file '\\kernel.elf': %r\n", status);
    Halt();
  }

  // Get size of the kernel file
  UINTN file_info_size = sizeof(EFI_FILE_INFO) + sizeof(CHAR16) * 12;
  UINT8 file_info_buffer[file_info_size];
  status = kernel_file->GetInfo(
      kernel_file, &gEfiFileInfoGuid,
      &file_info_size, file_info_buffer);
  if (EFI_ERROR(status)) {
    Print(L"failed to get file information: %r\n", status);
    Halt();
  }

  // Read the kernel file
  EFI_FILE_INFO *file_info = (EFI_FILE_INFO *)file_info_buffer;
  UINTN kernel_file_size = file_info->FileSize;

  // Allocate memory for the kernel
  VOID *kernel_buffer;
  status = gBS->AllocatePool(EfiLoaderData, kernel_file_size, &kernel_buffer);
  if (EFI_ERROR(status)) {
    Print(L"failed to allocate pool: %r\n", status);
    Halt();
  }

  // Read the kernel file into the structure
  status = kernel_file->Read(kernel_file, &kernel_file_size, kernel_buffer);
  if (EFI_ERROR(status))
  {
    Print(L"error: %r", status);
    Halt();
  }

  // Parse the kernel file
  Elf64_Ehdr *kernel_ehdr = (Elf64_Ehdr *)kernel_buffer;
  UINT64 kernel_first_addr, kernel_last_addr;
  calc_load_addr_range(kernel_ehdr, &kernel_first_addr, &kernel_last_addr);

  UINTN num_pages = (kernel_last_addr - kernel_first_addr + 0xfff) / 0x1000;
  status = gBS->AllocatePages(AllocateAddress, EfiLoaderData,
                              num_pages, &kernel_first_addr);
  if (EFI_ERROR(status)) {
    Print(L"failed to allocate pages: %r\n", status);
    Halt();
  }

  // Copy and load all the segments of the kernel file
  copy_load_segments(kernel_ehdr);
  Print(L"[ INFO ] Kernel: 0x%0lx - 0x%0lx, e_entry :0x0%lx \n", kernel_first_addr, kernel_last_addr, kernel_ehdr->e_entry);

  // Locate entry point for boot the kernel file
  EFI_PHYSICAL_ADDRESS entry_addr = *(EFI_PHYSICAL_ADDRESS *)(kernel_first_addr + 24);

  // Free up memory for the kernel file
  status = gBS->FreePool(kernel_buffer);
  if (EFI_ERROR(status)) {
    PrintError();
    Print(L"Free Pool: %r\n", status);
    Halt();
  }

  // Exit boot services
  status = gBS->ExitBootServices(IM, map.map_key);
  if (EFI_ERROR(status)) {
    status = get_memmap(&map);
    if (EFI_ERROR(status)) {
      PrintError();
      Print(L"Get Memory Map - Exit BS : %r \n", status);
      while (1)
        ;
    }
    status = gBS->ExitBootServices(IM, map.map_key);
    if (EFI_ERROR(status)) {
      PrintError();
      Print(L"Exit BS : %r\n", status);
      while (1)
        ;
    }
  }

  // Boot the kernel!!
  typedef void entry_point_t(void);
  entry_point_t *entry_point = (entry_point_t *)entry_addr;
  entry_point();

  // stop cpu
  while (1)
    __asm__("hlt");
  return EFI_SUCCESS;
}
