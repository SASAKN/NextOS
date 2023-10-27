#ifndef _EFI_LIP_H
#define _EFI_LIP_H

#include "efi.h"
#include "types.h"

// typedef
// EFI_STATUS
// (EFIAPI *EFI_IMAGE_UNLOAD) (
//   IN EFI_HANDLE               ImageHandle,
//   );

// typedef struct {
//    UINT32                        Revision;
//    EFI_HANDLE                    ParentHandle;
//    EFI_SYSTEM_TABLE              *SystemTable;

//    // Source location of the image
//    EFI_HANDLE                    DeviceHandle;
//    EFI_DEVICE_PATH_PROTOCOL      *FilePath;
//    VOID                          *Reserved;

//    // Image’s load options
//    UINT32                        LoadOptionsSize;
//    VOID                          *LoadOptions;

//    // Location where image was loaded
//    VOID                          *ImageBase;
//    UINT64                        ImageSize;
//    EFI_MEMORY_TYPE               ImageCodeType;
//    EFI_MEMORY_TYPE               ImageDataType;
//    EFI_IMAGE_UNLOAD              Unload;
// } EFI_LOADED_IMAGE_PROTOCOL;




#endif