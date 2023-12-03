#ifndef _BOOT_ELF_LOADER_H
#define _BOOT_ELF_LOADER_H

// Prototype
EFI_PHYSICAL_ADDRESS align_addr(EFI_PHYSICAL_ADDRESS addr, UINTN align);
EFI_PHYSICAL_ADDRESS get_segment_end_addr(elf64_phdr *phdr);
void calc_segment_start_size(elf64_ehdr *ehdr, EFI_PHYSICAL_ADDRESS *segment_start_addr, UINTTN *segment_size);
EFI_STATUS load_kernel(EFI_FILE_PROTOCOL *root, EFI_FILE_PROTOCOL *kernel_file, UINTN kernel_file_size, EFI_PHYSICAL_ADDRESS kernel_base_addr, Elf64_Addr *entry_addr);

#endif //_BOOT_ELF_LOADER_H