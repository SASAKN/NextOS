#ifndef _BOOT_ELF_LOADER_H
#define _BOOT_ELF_LOADER_H

// Prototype
EFI_STATUS read_kernel(EFI_FILE_PROTOCOL *kernel_file, UINTN kernel_f_size, VOID *kernel_buffer);

#endif //_BOOT_ELF_LOADER_H