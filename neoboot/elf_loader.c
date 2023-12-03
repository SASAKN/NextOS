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
#include "elf.h"
#include "elf_loader.h"

void calc_address_range(elf64_ehdr* ehdr, UINT64* first, UINT64* last) {
  elf64_phdr* phdr = (Elf64_Phdr*)((UINT64)ehdr + ehdr->e_phoff);
  *first = MAX_UINT64;
  *last = 0;
  for (Elf64_Half i = 0; i < ehdr->e_phnum; ++i) {
    if (phdr[i].p_type != PT_LOAD) continue;
    *first = MIN(*first, phdr[i].p_vaddr);
    *last = MAX(*last, phdr[i].p_vaddr + phdr[i].p_memsz);
  }
}

void copy_load_segments(elf64_ehdr* ehdr) {
  elf64_phdr* phdr = (Elf64_Phdr*)((UINT64)ehdr + ehdr->e_phoff);
  for (Elf64_Half i = 0; i < ehdr->e_phnum; ++i) {
    if (phdr[i].p_type != PT_LOAD) continue;

    UINT64 segm_in_file = (UINT64)ehdr + phdr[i].p_offset;
    CopyMem((VOID*)phdr[i].p_vaddr, (VOID*)segm_in_file, phdr[i].p_filesz);

    UINTN remain_bytes = phdr[i].p_memsz - phdr[i].p_filesz;
    SetMem((VOID*)(phdr[i].p_vaddr + phdr[i].p_filesz), remain_bytes, 0);
  }
}



// ELFローダーあり
EFI_STATUS load_kernel(EFI_FILE_PROTOCOL *root, EFI_FILE_PROTOCOL *kernel_file, UINTN kernel_file_size, EFI_PHYSICAL_ADDRESS kernel_base_addr, Elf64_Addr *entry_addr) {
  EFI_STATUS status;
  // Open file
  status = root->Open(root, &kernel_file, L"\\kernel.elf", EFI_FILE_MODE_READ, 0);
  if(EFI_ERROR(status)) {
    PrintError();
    Print(L"Open the kernel file 'kernel.elf'\n");
  }

  // Get info
  UINTN file_info_size = sizeof(EFI_FILE_INFO) + sizeof(CHAR16) * 12;
  UINT8 file_info_buffer[file_info_size];
  status =  kernel_file->GetInfo(kernel_file, &gEfiFileInfoGuid, &file_info_size, file_info_buffer);
  if(EFI_ERROR(status)) {
    PrintError();
    Print(L"Get info the kernel file 'kernel.elf'\n");
  }

  // Get file size
  EFI_FILE_INFO* file_info = (EFI_FILE_INFO*)file_info_buffer;
  kernel_file_size = file_info->FileSize;
  
  // Allocate pool
  VOID *kernel_buffer;
  status = gBS->AllocatePool(EfiLoaderData, kernel_file_size, &kernel_buffer);
  if (EFI_ERROR(status)) {
    PrintError();
    Print(L"Allocate Pool \n");
  }
  // Read the kernel file
  status = kernel_file->Read(kernel_file, &kernel_file_size, kernel_buffer);
  if (EFI_ERROR(status)) {
    PrintError();
    Print(L"Read the kernel file \n");
  } 

  // Read program headers
  elf64_ehdr *kernel_ehdr = (elf64_ehdr *)kernel_buffer;
  UINT64 kernel_start_addr;
  UINT64 kernel_end_addr;

  // Is the kernel file is executable ?
  if (kernel_ehdr->e_ident[0] == 0x7f && kernel_ehdr->e_ident[1] == 'E' && kernel_ehdr->e_ident[2] == 'L' && kernel_ehdr->e_ident[3] == 'F' && kernel_ehdr->e_ident[4] == 2 && kernel_ehdr->e_ident[5] == 1 && kernel_ehdr->e_type == ET_EXEC) {
    PrintOK();
    Print(L"The kernel file is executable file \n");
  } else {
    PrintError();
    Print(L"The kernel file is not executable file\n");
  }

  // Calculate address range
  calc_address_range(kernel_ehdr, &kernel_start_addr, &kernel_end_addr);

  // Allocate pages
  UINTN num_pages = (kernel_end_addr - kernel_start_addr + 4095) / 4096;
  Print(L"[ INFO ] NUM_PAGES %lu, KERNEL_START_ADDR %lx\n", num_pages, kernel_start_addr);
  status = gBS->AllocatePages(AllocateAddress, EfiLoaderData, num_pages, &kernel_start_addr);
  if (EFI_ERROR(status)) {
    PrintError();
    Print(L"Allocate pages : %r \n", status);
  }

  // Copy LOAD segments
  copy_load_segments(kernel_ehdr);

  // Locate entry point
  *entry_addr = kernel_ehdr->e_entry;
  return EFI_SUCCESS;
}
