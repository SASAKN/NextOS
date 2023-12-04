#ifndef _BOOT_ELF_LOADER_H
#define _BOOT_ELF_LOADER_H

// Prototype
EFI_STATUS load_kernel(EFI_FILE_PROTOCOL *root, EFI_FILE_PROTOCOL *kernel_file, UINTN kernel_file_size, EFI_PHYSICAL_ADDRESS kernel_base_addr, Elf64_Addr *entry_addr);
void CopyLoadSegments(elf64_ehdr* ehdr);
void CalcLoadAddressRange(elf64_ehdr* ehdr, UINT64* first, UINT64* last);

#endif //_BOOT_ELF_LOADER_H