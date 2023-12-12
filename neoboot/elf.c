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

#include "elf.h"

// ELFを解析
void calc_load_addr_range(Elf64_Ehdr* ehdr, UINT64* first, UINT64* last) {
  Elf64_Phdr* phdr = (Elf64_Phdr*)((UINT64)ehdr + ehdr->e_phoff);
  *first = MAX_UINT64;
  *last = 0;
  for (Elf64_Half i = 0; i < ehdr->e_phnum; ++i) {
    if (phdr[i].p_type != PT_LOAD) continue;
    *first = MIN(*first, phdr[i].p_vaddr);
    *last = MAX(*last, phdr[i].p_vaddr + phdr[i].p_memsz);
    
  }
}

void copy_load_segments(Elf64_Ehdr* ehdr) {
  Elf64_Phdr* phdr = (Elf64_Phdr*)((UINT64)ehdr + ehdr->e_phoff);
  for (Elf64_Half i = 0; i < ehdr->e_phnum; ++i) {

    // Print the debug message
    Print(L"\n[ INFO ] Copy PT_LOAD Segments\n");
    // Processing
    gST->ConOut->SetAttribute(gST->ConOut, EFI_LIGHTBLUE);
    gST->ConOut->OutputString(gST->ConOut, L"[ PROCESSING ]");
    gST->ConOut->SetAttribute(gST->ConOut, EFI_WHITE);
    Print(L"Program header %lu(count) vaddr : %08x, paddr : %08x, offset %x, file_size : %x, memory_size : %x\n", i, phdr->p_vaddr, phdr->p_paddr, phdr->p_offset, phdr->p_filesz, phdr->p_memsz);

    if (phdr[i].p_type != PT_LOAD) continue;
    UINT64 segm_in_file = (UINT64)ehdr + phdr[i].p_offset;
    CopyMem((VOID*)phdr[i].p_vaddr, (VOID*)segm_in_file, phdr[i].p_filesz);
    UINTN remain_bytes = phdr[i].p_memsz - phdr[i].p_filesz;
    SetMem((VOID*)(phdr[i].p_vaddr + phdr[i].p_filesz), remain_bytes, 0);
  }
}