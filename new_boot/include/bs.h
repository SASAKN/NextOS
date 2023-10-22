#ifndef _EFI_BS_H
#define _EFI_BS_H

#include "types.h"

/* BootServices */
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




#endif