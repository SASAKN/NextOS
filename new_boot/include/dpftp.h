#ifndef _EFI_DPFTP_H
#define _EFI_DPFTP_H

#include "efi.h"

/* DPFTP */
#define EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL_GUID \
  {0x5c99a21,0xc70f,0x4ad2,\
    {0x8a,0x5f,0x35,0xdf,0x33,0x43,0xf5, 0x1e}}

// typedef
// EFI_DEVICE_PATH_PROTOCOL*
// (EFIAPI *EFI_DEVICE_PATH_FROM_TEXT_NODE) (
//   IN CONST CHAR16*          TextDeviceNode
//   );

// typedef
// EFI_DEVICE_PATH_PROTOCOL*
// (EFIAPI *EFI_DEVICE_PATH_FROM_TEXT_PATH) (
//   IN CONST CHAR16*                     TextDevicePath
//   );

// /* DPFTP */
// typedef struct _EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL {
// EFI_DEVICE_PATH_FROM_TEXT_NODE           ConvertTextToDevicNode;
// EFI_DEVICE_PATH_FROM_TEXT_PATH           ConvertTextToDevicPath;
// } EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL;



#endif