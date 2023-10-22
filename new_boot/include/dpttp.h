#ifndef _EFI_DPTTP_H
#define _EFI_DPTTP_H

#include "efi.h"

/* DPTTP */
#define EFI_DEVICE_PATH_TO_TEXT_PROTOCOL_GUID \
  {0x8b843e20,0x8132,0x4852,\
    {0x90,0xcc,0x55,0x1a,0x4e,0x4a,0x7f,0x1c}}

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