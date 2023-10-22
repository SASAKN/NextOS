#ifndef _EFI_DPUP_H
#define _EFI_DPUP_H

#include "efi.h"
#include "types.h"

typedef
UINTN
(EFIAPI *EFI_DEVICE_PATH_UTILS_GET_DEVICE_PATH_SIZE) (
  IN CONST EFI_DEVICE_PATH_PROTOCOL           *DevicePath
  );

typedef
EFI_DEVICE_PATH_PROTOCOL*
(EFIAPI *EFI_DEVICE_PATH_UTILS_DUP_DEVICE_PATH) (
  IN CONST EFI_DEVICE_PATH_PROTOCOL           *DevicePath
  );

typedef
EFI_DEVICE_PATH_PROTOCOL*
(EFIAPI *EFI_DEVICE_PATH_UTILS_APPEND_PATH) (
  IN CONST EFI_DEVICE_PATH_PROTOCOL      *Src1 ,
  IN CONST EFI_DEVICE_PATH_PROTOCOL      *Src2
  );

typedef
EFI_DEVICE_PATH_PROTOCOL*
(EFIAPI *EFI_DEVICE_PATH_UTILS_APPEND_NODE) (
IN CONST EFI_DEVICE_PATH_PROTOCOL         *DevicePath,
IN CONST EFI_DEVICE_PATH_PROTOCOL         *DeviceNode
);

typedef
EFI_DEVICE_PATH_PROTOCOL*
(EFIAPI *EFI_DEVICE_PATH_UTILS_APPEND_INSTANCE) (
  IN CONST EFI_DEVICE_PATH_PROTOCOL       *DevicePath,
  IN CONST EFI_DEVICE_PATH_PROTOCOL       *DevicePathInstance
  );

typedef
EFI_DEVICE_PATH_PROTOCOL*
(EFIAPI *EFI_DEVICE_PATH_UTILS_GET_NEXT_INSTANCE) (
  IN OUT EFI_DEVICE_PATH_PROTOCOL         **DevicePathInstance,
  OUT UINTN                               *DevicePathInstanceSize* OPTIONAL
  );

typedef
EFI_DEVICE_PATH_PROTOCOL*
(EFIAPI *EFI_DEVICE_PATH_UTILS_CREATE_NODE) (
 IN UINT8               NodeType,
 IN UINT8               NodeSubType,
 IN UINT16              NodeLength
 );

typedef
BOOLEAN
(EFIAPI *EFI_DEVICE_PATH_UTILS_IS_MULTI_INSTANCE) (
 IN CONST EFI_DEVICE_PATH_PROTOCOL      *DevicePath
 );




/* DPUP */
typedef struct _EFI_DEVICE_PATH_UTILITIES_PROTOCOL {
  EFI_DEVICE_PATH_UTILS_GET_DEVICE_PATH_SIZE    GetDevicePathSize;
  EFI_DEVICE_PATH_UTILS_DUP_DEVICE_PATH         DuplicateDevicePath;
  EFI_DEVICE_PATH_UTILS_APPEND_PATH             AppendDevicePath;
  EFI_DEVICE_PATH_UTILS_APPEND_NODE             AppendDeviceNode;
  EFI_DEVICE_PATH_UTILS_APPEND_INSTANCE         AppendDevicePathInstance;
  EFI_DEVICE_PATH_UTILS_GET_NEXT_INSTANCE       GetNextDevicePathInstance;
  EFI_DEVICE_PATH_UTILS_IS_MULTI_INSTANCE       IsDevicePathMultiInstance;
  EFI_DEVICE_PATH_UTILS_CREATE_NODE             CreateDeviceNode;
}   EFI_DEVICE_PATH_UTILITIES_PROTOCOL;


#endif