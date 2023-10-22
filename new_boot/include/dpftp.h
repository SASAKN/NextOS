#ifndef _EFI_DPFTP_H
#define _EFI_DPFTP_H

#include "efi.h"

typedef
EFI_DEVICE_PATH_PROTOCOL*
(EFIAPI *EFI_DEVICE_PATH_FROM_TEXT_NODE) (
  IN CONST CHAR16*          TextDeviceNode
  );

typedef
EFI_DEVICE_PATH_PROTOCOL*
(EFIAPI *EFI_DEVICE_PATH_FROM_TEXT_PATH) (
  IN CONST CHAR16*                     TextDevicePath
  );

/* DPFTP */
typedef struct _EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL {
EFI_DEVICE_PATH_FROM_TEXT_NODE           ConvertTextToDevicNode;
EFI_DEVICE_PATH_FROM_TEXT_PATH           ConvertTextToDevicPath;
} EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL;



#endif