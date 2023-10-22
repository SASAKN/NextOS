#ifndef _EFI_DPTTP_H
#define _EFI_DPTTP_H

#include "efi.h"

/* DPTH_H */
typedef
CHAR16*
(EFIAPI *EFI_DEVICE_PATH_TO_TEXT_NODE) (
  IN CONST EFI_DEVICE_PATH_PROTOCOL*    DeviceNode,
  IN BOOLEAN                    DisplayOnly,
  IN BOOLEAN                    AllowShortcuts
  );

typedef
CHAR16*
(EFIAPI *EFI_DEVICE_PATH_TO_TEXT_PATH) (
  IN CONST EFI_DEVICE_PATH_PROTOCOL       *DevicePath,
  IN BOOLEAN                              DisplayOnly,
  IN BOOLEAN                              AllowShortcuts
  );

/* DevicePathToTextProtocol */
typedef struct _EFI_DEVICE_PATH_TO_TEXT_PROTOCOL {
  EFI_DEVICE_PATH_TO_TEXT_NODE        ConvertDeviceNodeToText;
  EFI_DEVICE_PATH_TO_TEXT_PATH        ConvertDevicePathToText;
}  EFI_DEVICE_PATH_TO_TEXT_PROTOCOL;


#endif