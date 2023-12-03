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

// Alignment
EFI_PHYSICAL_ADDRESS align_addr(EFI_PHYSICAL_ADDRESS addr, UINTN align) {
  const EFI_PHYSICAL_ADDRESS mask = align  - 1;
  return (addr + mask) & ~mask;
}

// Segment end addr
EFI_PHYSICAL_ADDRESS get_segment_end_addr(elf64_phdr *phdr) {
  return align_addr(phdr->p_vaddr + phdr->p_memsz, phdr->p_align);
}

// Get segment size
void calc_segment_start_size(elf64_ehdr *ehdr, EFI_PHYSICAL_ADDRESS *segment_start_addr, UINTTN *segment_size) {
  UINTN i = 0;
  elf64_phdr *phdr = ELF64_GET_PHDR(ehdr);

  for (; i < ehdr->e_phnum && phdr[i].p_type != PT_LOAD; ++i);
  EFI_PHYSICAL_ADDRESS start = phdr[i].p_vaddr;
  EFI_PHYSICAL_ADDRESS end = get_segment_end_addr(&phdr[i]);
  ++i;

  for (; i < edhr->e_phnum; ++i) {
    if (phdr[i].p_type != PT_LOAD) continue;

    if (start > phdr[i].p_vaddr) {
      start = phdr[i].p_vaddr;
    }

    const EFI_PHYSICAL_ADDRESS seg_end = get_segment_end_addr(&phdr[i]);
    if (end < seg_end) {
      end = seg_end;
    }

    *segment_start_addr = start;
    *segment_size = end - start;
  }
}

// copy a segment
void copy_a_segment(elf64_phdr *phdr, EFI_PHYSICAL_ADDRESS image_base_addr, EFI_PHYSICAL_ADDRESS load_addr) {
  if (phdr->p_filesz > 0) {
    CopyMem((VOID *)(phdr->p_vaddr + load_addr), (VOID *)(image_base_addr + phdr->p_offset), phdr->p_filesz);
    PrintOK();
    Print(L"Copied Image Block %08x -> %08x (%08x bytes)\n", image_base_addr + phdr->p_offset, phdr->p_vaddr + load_addr, phdr->p_filesz);
  }
  if (phdr->p_memsz > phdr->p_filesz) {
    ZeroMem((VOID *)(phdr->p_vaddr + load_addr + phdr->p_filesz), phdr->p_memsz - phdr->p_filesz);
  }
}

// ELFローダー
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
  EFI_PHYSICAL_ADDRESS kernel_start_addr;
  EFI_PHYSICAL_ADDRESS kernel_end_addr;

  // Is the kernel file is executable ?
  if (kernel_ehdr->e_ident[0] == 0x7f && kernel_ehdr->e_ident[1] == 'E' && kernel_ehdr->e_ident[2] == 'L' && kernel_ehdr->e_ident[3] == 'F' && kernel_ehdr->e_ident[4] == 2 && kernel_ehdr->e_ident[5] == 1 && kernel_ehdr->e_type == ET_EXEC) {
    PrintOK();
    Print(L"The kernel file is executable file \n");
  } else {
    PrintError();
    Print(L"The kernel file is not executable file\n");
  }

  // Calculate memory size for all PT_LOAD segments
  UINTN segment_size;
  EFI_PHYSICAL_ADDRESS kernel_file_addr = 0;
  EFI_PHYSICAL_ADDRESS load_addr = 0;
  calc_segment_start_size(kernel_ehdr, &kernel_start_addr, &segment_size);
  UINTN num_pages = (segment_size + 4095) / 4096;
  Print(L"[ INFO ] NUM_PAGES %lu, KERNEL_START_ADDR %lx\n", num_pages, &kernel_start_addr);

  // Allocate pages
  status = gBS->AllocatePages(AllocateAddress, EfiLoaderData, num_pages, &kernel_start_addr);
  if (EFI_ERROR(status)) {
    PrintError();
    Print(L"Allocate pages : %r \n", status);
  }

  // Copy segments
  elf64_phdr *phdr = ELF64_GET_PHDR(kernel_ehdr);
  for (UINTN i = 0; i < kernel_ehdr->e_phnum; ++i) {
    Print(L"[ INFO ] Processing a program header %lu, type = %lu", i, phdr[i].p_type);
    if (phdr[i].p_type == PT_LOAD) {
      Print(L"[ INFO ] Program Header %lu : vaddr %08x, offset %x, filesz %x, memsz %x", i, phdr[i].p_vaddr, phdr[i].p_offset, phdr[i].p_filesz, phdr[i].p_memsz);
      copy_a_segment(&phdr[i], kernel_file_addr, load_addr);
    } else if (phdr[i].p_type == PT_DYNAMIC) {
      PrintError();
      Print(L"Cullently neoboot is not supported dynamic executable file\n");
    }
  }

  // Locate entry point
  *entry_addr = kernel_ehdr->e_entry;
  return EFI_SUCCESS;
}
