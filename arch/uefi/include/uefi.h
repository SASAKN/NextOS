#ifndef _UEFI_H
#define _UEFI_H

#include "types.h"
#include "protocol.h"



/* メモリー */

/* EFI_MEMORY_TYPE */
typedef enum
{
    EfiReservedMemoryType,
    EfiLoaderCode,
    EfiLoaderData,
    EfiBootServicesCode,
    EfiBootServicesData,
    EfiRuntimeServicesCode,
    EfiRuntimeServicesData,
    EfiConventionalMemory,
    EfiUnusableMemory,
    EfiACPIReclaimMemory,
    EfiACPIMemoryNVS,
    EfiMemoryMappedIO,
    EfiMemoryMappedIOPortSpace,
    EfiPalCode,
    EfiMaxMemoryType
} EFI_MEMORY_TYPE;

/* EFI_MEMORY_DESCRIPTOR */
typedef struct
{
    UINT32 Type;
    EFI_STATUS PhysicalStart;
    EFI_STATUS VirtualStart;
    EFI_STATUS NumberOfPages;
    EFI_STATUS Attribute;
} EFI_MEMORY_DESCRIPTOR;


#endif