#ifndef _NEOBOOT_FILE_H
#define _NEOBOOT_FILE_H

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

// わかりやすいように使い分けするデータ型
typedef struct _EFI_FILE_PROTOCOL FILE;
typedef struct _EFI_FILE_PROTOCOL DIR;


#endif //_NEOBOOT_FILE_H