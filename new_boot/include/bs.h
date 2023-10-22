#ifndef _EFI_BS_H
#define _EFI_BS_H

#include "types.h"

/* Event Services */
typedef
EFI_STATUS
(EFIAPI *EFI_CREATE_EVENT) (
   IN UINT32                   Type,
   IN EFI_TPL                  NotifyTpl,
   IN EFI_EVENT_NOTIFY         NotifyFunction, OPTIONAL
   IN VOID                     *NotifyContext, OPTIONAL
   OUT EFI_EVENT               *Event
   );

typedef
VOID
(EFIAPI *EFI_EVENT_NOTIFY) (
  IN EFI_EVENT          Event,
  IN VOID              *Context
   );

typedef
EFI_STATUS
(EFIAPI *EFI_CREATE_EVENT_EX) (
   IN UINT32                  Type,
   IN EFI_TPL                 NotifyTpl,
   IN EFI_EVENT_NOTIFY        NotifyFunction OPTIONAL,
   IN CONST VOID              *NotifyContext OPTIONAL,
   IN CONST EFI_GUID          *EventGroup OPTIONAL,
   OUT EFI_EVENT              *Event
   );

typedef
EFI_STATUS
(EFIAPI *EFI_CLOSE_EVENT) (
  IN EFI_EVENT      Event
);

typedef
EFI_STATUS
(EFIAPI *EFI_SIGNAL_EVENT) (
  IN EFI_EVENT Event
    );

typedef
EFI_STATUS
(EFIAPI *EFI_WAIT_FOR_EVENT) (
   IN UINTN             NumberOfEvents,
   IN EFI_EVENT         *Event,
   OUT UINTN            *Index
  );

typedef
EFI_STATUS
(EFIAPI *EFI_CHECK_EVENT) (
  IN EFI_EVENT                Event
);

typedef
EFI_STATUS
(EFIAPI *EFI_SET_TIMER) (
   IN EFI_EVENT               Event,
   IN EFI_TIMER_DELAY         Type,
   IN UINT64                  TriggerTime
   );

typedef
EFI_TPL
(EFIAPI   *EFI_RAISE_TPL) (
  IN EFI_TPL   NewTpl
  );

typedef
VOID
(EFIAPI *EFI_RESTORE_TPL) (
   IN EFI_TPL OldTpl
   );

/* Memory Allocation Services */
typedef
EFI_STATUS
(EFIAPI *EFI_ALLOCATE_PAGES) (
   IN EFI_ALLOCATE_TYPE                   Type,
   IN EFI_MEMORY_TYPE                     MemoryType,
   IN UINTN                               Pages,
   IN OUT EFI_PHYSICAL_ADDRESS            *Memory
   );

typedef
EFI_STATUS
(EFIAPI *EFI_FREE_PAGES) (
IN EFI_PHYSICAL_ADDRESS    Memory,
IN UINTN                   Pages
);

typedef
EFI_STATUS
(EFIAPI *EFI_GET_MEMORY_MAP) (
   IN OUT UINTN                  *MemoryMapSize,
   OUT EFI_MEMORY_DESCRIPTOR     *MemoryMap,
   OUT UINTN                     *MapKey,
   OUT UINTN                     *DescriptorSize,
   OUT UINT32                    *DescriptorVersion
  );

typedef
EFI_STATUS
(EFIAPI  *EFI_ALLOCATE_POOL) (
   IN EFI_MEMORY_TYPE            PoolType,
   IN UINTN                      Size,
   OUT VOID                      **Buffer
   );

typedef
EFI_STATUS
(EFIAPI *EFI_FREE_POOL) (
   IN VOID           *Buffer
   );

typedef
EFI_STATUS
(EFIAPI *EFI_INSTALL_PROTOCOL_INTERFACE) (
   IN OUT EFI_HANDLE             *Handle,
   IN EFI_GUID                   *Protocol,
   IN EFI_INTERFACE_TYPE         InterfaceType,
   IN VOID                       *Interface
   );

typedef
EFI_STATUS
(EFIAPI *EFI_UNINSTALL_PROTOCOL_INTERFACE) (
   IN EFI_HANDLE        Handle,
   IN EFI_GUID          *Protocol,
   IN VOID              *Interface
   );

typedef
EFI_STATUS
(EFIAPI *EFI_REINSTALL_PROTOCOL_INTERFACE) (
   IN EFI_HANDLE           Handle,
   IN EFI_GUID             *Protocol,
   IN VOID                 *OldInterface,
   IN VOID                 *NewInterface
   );

typedef
EFI_STATUS
(EFIAPI *EFI_REGISTER_PROTOCOL_NOTIFY) (
   IN EFI_GUID                         *Protocol,
   IN EFI_EVENT                        Event,
   OUT VOID                            **Registration
   );

typedef
EFI_STATUS
(EFIAPI *EFI_LOCATE_HANDLE) (
   IN EFI_LOCATE_SEARCH_TYPE                 SearchType,
   IN EFI_GUID                               *Protocol OPTIONAL,
   IN VOID                                   *SearchKey OPTIONAL,
   IN OUT UINTN                              *BufferSize,
   OUT EFI_HANDLE                            *Buffer
   );

typedef
EFI_STATUS
(EFIAPI *EFI_HANDLE_PROTOCOL) (
   IN EFI_HANDLE                    Handle,
   IN EFI_GUID                      *Protocol,
   OUT VOID                         **Interface
   );

typedef
EFI_STATUS
(EFIAPI *EFI_LOCATE_DEVICE_PATH) (
   IN EFI_GUID                         *Protocol,
   IN OUT EFI_DEVICE_PATH_PROTOCOL     **DevicePath,
   OUT EFI_HANDLE                      *Device
   );

typedef
EFI_STATUS
(EFIAPI *EFI_OPEN_PROTOCOL) (
   IN EFI_HANDLE                    Handle,
   IN EFI_GUID                      *Protocol,
   OUT VOID                         **Interface OPTIONAL,
   IN EFI_HANDLE                    AgentHandle,
   IN EFI_HANDLE                    ControllerHandle,
   IN UINT32                        Attributes
   );

typedef
EFI_STATUS
(EFIAPI *EFI_CLOSE_PROTOCOL) (
   IN EFI_HANDLE                 Handle,
   IN EFI_GUID                   *Protocol,
   IN EFI_HANDLE                 AgentHandle,
   IN EFI_HANDLE                 ControllerHandle
   );

typedef
EFI_STATUS
(EFIAPI *EFI_OPEN_PROTOCOL_INFORMATION) (
   IN EFI_HANDLE                             Handle,
   IN EFI_GUID                               *Protocol,
   OUT EFI_OPEN_PROTOCOL_INFORMATION_ENTRY   **EntryBuffer,
   OUT UINTN                                 *EntryCount
   );

typedef
EFI_STATUS
(EFIAPI *EFI_CONNECT_CONTROLLER) (
   IN EFI_HANDLE                       ControllerHandle,
   IN EFI_HANDLE                       *DriverImageHandle OPTIONAL,
   IN EFI_DEVICE_PATH_PROTOCOL         *RemainingDevicePath OPTIONAL,
   IN BOOLEAN Recursive
   );

typedef
EFI_STATUS
(EFIAPI *EFI_DISCONNECT_CONTROLLER) (
   IN EFI_HANDLE                       ControllerHandle,
   IN EFI_HANDLE                       DriverImageHandle OPTIONAL,
   IN EFI_HANDLE                       ChildHandle OPTIONAL
   );

typedef
EFI_STATUS
(EFIAPI *EFI_PROTOCOLS_PER_HANDLE) (
   IN EFI_HANDLE                             Handle,
   OUT EFI_GUID                              ***ProtocolBuffer,
   OUT UINTN                                 *ProtocolBufferCount
   );

typedef
EFI_STATUS
(EFIAPI *EFI_LOCATE_HANDLE_BUFFER) (
   IN EFI_LOCATE_SEARCH_TYPE                    SearchType,
   IN EFI_GUID                                  *Protocol OPTIONAL,
   IN VOID                                      *SearchKey OPTIONAL,
   OUT UINTN                                    *NoHandles,
   OUT EFI_HANDLE                               **Buffer
   );

typedef
EFI_STATUS
(EFIAPI *EFI_LOCATE_PROTOCOL) (
  IN EFI_GUID                            *Protocol,
  IN VOID                                *Registration OPTIONAL,
  OUT VOID                               **Interface
 );

typedef
EFI_STATUS
EFIAPI \*EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES) (
   IN OUT EFI_HANDLE                               *Handle,
   ...
   );

typedef
EFI_STATUS
EFIAPI *EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES) (
   IN EFI_HANDLE Handle,
   …
  );

typedef
EFI_STATUS
(EFIAPI *EFI_IMAGE_LOAD) (
   IN BOOLEAN                          BootPolicy,
   IN EFI_HANDLE                       ParentImageHandle,
   IN EFI_DEVICE_PATH_PROTOCOL         *DevicePath   OPTIONAL,
   IN VOID                             *SourceBuffer OPTIONAL
   IN UINTN                            SourceSize,
   OUT EFI_HANDLE                      *ImageHandle
   );











#endif