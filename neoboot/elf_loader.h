#ifndef _BOOT_ELF_LOADER_H
#define _BOOT_ELF_LOADER_H

// Prototype
EFI_STATUS read_file(UINTN *file_size, EFI_FILE_PROTOCOL *file, void *buffer);

#endif //_BOOT_ELF_LOADER_H