#ifndef _NEOBOOT_PROTO_H
#define _NEOBOOT_PROTO_H

// For using UEFI Library
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

#include "memory_map.h"
#include "file.h"
#include "proto.h"
#include "elf.h"

//Print
void PrintError(void); 
void PrintWarn(void); 
void PrintGoodBye(void);
void PrintOK(void);  

//MemoryMap
void *malloc(UINTN size);
void free(void* ptr);
const CHAR16 *get_memtype(EFI_MEMORY_TYPE type);
void init_memmap(struct MemoryMap *map, void* buffer);
EFI_STATUS get_memmap(struct MemoryMap *map);
EFI_STATUS print_memmap(struct MemoryMap *map);
EFI_STATUS save_memmap(struct MemoryMap *map, DIR *root);

// File
EFI_STATUS open_root_dir(EFI_HANDLE IM, DIR **root);
FILE *create_file(DIR *root, CHAR16 *file_path);

#endif