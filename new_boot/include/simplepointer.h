#ifndef _EFI_SIMPLE_POINTER_H
#define _EFI_SIMPLE_POINTER_H

/* SimplePointerProtocol */
/* Guid */
#define EFI_SIMPLE_POINTER_PROTOCOL_GUID \
 {0x31878c87,0xb75,0x11d5,\
  {0x9a,0x4f,0x00,0x90,0x27,0x3f,0xc1,0x4d}}

typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_POINTER_RESET) (
 IN EFI_SIMPLE_POINTER_PROTOCOL              *This,
 IN BOOLEAN                                  ExtendedVerification
 );

 typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_POINTER_GET_STATE)(
 IN EFI_SIMPLE_POINTER_PROTOCOL              *This,
 OUT EFI_SIMPLE_POINTER_STATE                *State
 );


typedef struct _EFI_SIMPLE_POINTER_PROTOCOL {
 EFI_SIMPLE_POINTER_RESET                    Reset;
 EFI_SIMPLE_POINTER_GET_STATE                GetState;
 EFI_EVENT                                   WaitForInput;
 EFI_SIMPLE_INPUT_MODE                       *Mode;
} EFI_SIMPLE_POINTER_PROTOCOL;

#endif