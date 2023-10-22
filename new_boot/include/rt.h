#ifndef _EFI_RT_H
#define _EFI_RT_H

#include "types.h"
#include "efi.h"

typedef
EFI_STATUS
GetVariable (
  IN CHAR16           *VariableName,
  IN EFI_GUID         *VendorGuid,
  OUT UINT32          *Attributes OPTIONAL,
  IN OUT UINTN        *DataSize,
  OUT VOID            *Data OPTIONAL
 );

typedef
EFI_STATUS
GetNextVariableName (
  IN OUT UINTN           *VariableNameSize,
  IN OUT CHAR16          *VariableName,
  IN OUT EFI_GUID        *VendorGuid
 );

 typedef
 EFI_STATUS
 SetVariable (
   IN CHAR16            *VariableName,
   IN EFI_GUID          *VendorGuid,
   IN UINT32            Attributes,
   IN UINTN             DataSize,
   IN VOID              *Data
);

typedef
EFI_STATUS
QueryVariableInfo (
   IN UINT32             Attributes,
   OUT UINT64            *MaximumVariableStorageSize,
   OUT UINT64            *RemainingVariableStorageSize,
   OUT UINT64            *MaximumVariableSize
  );

typedef
EFI_STATUS
GetTime (
   OUT EFI_TIME                  *Time,
   OUT EFI_TIME_CAPABILITIES     *Capabilities OPTIONAL
  );

typedef
EFI_STATUS
SetTime (
  IN EFI_TIME       *Time
 );

typedef
EFI_STATUS
GetWakeupTime (
   OUT BOOLEAN            *Enabled,
   OUT BOOLEAN            *Pending,
   OUT EFI_TIME           *Time
  );

typedef
EFI_STATUS
SetWakeupTime (
   IN BOOLEAN         Enable,
   IN EFI_TIME        *Time OPTIONAL
  );

typedef
EFI_STATUS
SetVirtualAddressMap (
   IN UINTN                 MemoryMapSize,
   IN UINTN                 DescriptorSize,
   IN UINT32                DescriptorVersion,
   IN EFI_MEMORY_DESCRIPTOR *VirtualMap
  );

typedef
EFI_STATUS
ConvertPointer (
   IN UINTN             DebugDisposition,
   IN VOID              **Address
  );

typedef
VOID
(EFIAPI *EFI_RESET_SYSTEM) (
   IN EFI_RESET_TYPE          ResetType,
   IN EFI_STATUS              ResetStatus,
   IN UINTN                   DataSize,
   IN VOID                    *ResetData OPTIONAL
 );

typedef
EFI_STATUS
GetNextHighMonotonicCount (
  OUT UINT32               *HighCount
 );

typedef
EFI_STATUS
UpdateCapsule (
   IN EFI_CAPSULE_HEADER      **CapsuleHeaderArray,
   IN UINTN                   CapsuleCount,
   IN EFI_PHYSICAL_ADDRESS    ScatterGatherList OPTIONAL
  );

typedef
EFI_STATUS
QueryCapsuleCapabilities (
   IN EFI_CAPSULE_HEADER         **CapsuleHeaderArray,
   IN UINTN                      CapsuleCount,
   OUT UINT64                    *MaximumCapsuleSize,
   OUT EFI_RESET_TYPE            *ResetType
  );









#endif