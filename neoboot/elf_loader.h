#ifndef _BOOT_ELF_LOADER_H
#define _BOOT_ELF_LOADER_H

#define _NEOBOOT_ELF_LOADER 1

// Prototype
EFI_STATUS load_kernel(EFI_FILE_PROTOCOL *root, EFI_FILE_PROTOCOL *kernel_file, UINTN kernel_file_size, EFI_PHYSICAL_ADDRESS kernel_base_addr);

#ifdef _NEOBOOT_ELF_LOADER
EFI_STATUS load_kernel(EFI_FILE_PROTOCOL *root, EFI_FILE_PROTOCOL *kernel_file, UINTN kernel_file_size, EFI_PHYSICAL_ADDRESS kernel_base_addr, Elf64_Addr *entry_addr);
#endif

#endif //_BOOT_ELF_LOADER_H