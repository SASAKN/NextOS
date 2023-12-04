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
void calc_segment_start_size(elf64_ehdr *ehdr, EFI_PHYSICAL_ADDRESS *segment_start_addr, UINTN *segment_size) {
  UINTN i = 0;
  elf64_phdr *phdr = ELF64_GET_PHDR(ehdr);

  for (; i < ehdr->e_phnum && phdr[i].p_type != PT_LOAD; ++i);
  EFI_PHYSICAL_ADDRESS start = phdr[i].p_vaddr;
  EFI_PHYSICAL_ADDRESS end = get_segment_end_addr(&phdr[i]);
  ++i;

  for (; i < ehdr->e_phnum; ++i) {
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
  

}