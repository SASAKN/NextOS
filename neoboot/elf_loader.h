#ifndef _BOOT_ELF_LOADER_H
#define _BOOT_ELF_LOADER_H

// Prototype
EFI_STATUS allocate_kernel(UINTN kernel_file_size, EFI_PHYSICAL_ADDRESS *kernel_base_addr);
EFI_STATUS read_kernel(EFI_FILE_PROTOCOL *f, UINTN *kernel_file_size, EFI_PHYSICAL_ADDRESS *kernel_base_addr);

#endif //_BOOT_ELF_LOADER_H