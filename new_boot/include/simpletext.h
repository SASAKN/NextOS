#ifndef _EFI_SIMPLETEXT_H
#define _EFI_SIMPLETEXT_H

/* SimpleTextInputExProtocol */
#include "efi.h"

/* Guid */
#define EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_GUID             \
    {                                                      \
        0xdd9e7534, 0x7762, 0x4698,                        \
        {                                                  \
            0x8c, 0x14, 0xf5, 0x85, 0x17, 0xa6, 0x25, 0xaa \
        }                                                  \
    }

typedef EFI_STATUS(EFIAPI *EFI_INPUT_RESET_EX)(
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN BOOLEAN ExtendedVerification);

typedef EFI_STATUS(EFIAPI *EFI_INPUT_READ_KEY_EX)(
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    OUT EFI_KEY_DATA *KeyData);

typedef EFI_STATUS(EFIAPI *EFI_SET_STATE)(
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN EFI_KEY_TOGGLE_STATE *KeyToggleState);

typedef EFI_STATUS(EFIAPI *EFI_KEY_NOTIFY_FUNCTION)(
    IN EFI_KEY_DATA *KeyData);

typedef EFI_STATUS(EFIAPI *EFI_REGISTER_KEYSTROKE_NOTIFY)(
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN EFI_KEY_DATA *KeyData,
    IN EFI_KEY_NOTIFY_FUNCTION KeyNotificationFunction,
    OUT VOID **NotifyHandle);

typedef EFI_STATUS(EFIAPI *EFI_UNREGISTER_KEYSTROKE_NOTIFY)(
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN VOID *NotificationHandle);

typedef struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL
{
    EFI_INPUT_RESET_EX Reset;
    EFI_INPUT_READ_KEY_EX ReadKeyStrokeEx;
    EFI_EVENT WaitForKeyEx;
    EFI_SET_STATE SetState;
    EFI_REGISTER_KEYSTROKE_NOTIFY RegisterKeyNotify;
    EFI_UNREGISTER_KEYSTROKE_NOTIFY UnregisterKeyNotify;
} EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL;

/* SimpleTextInputProtocol */

typedef
EFI_STATUS
(EFIAPI *EFI_INPUT_RESET) (
 IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL                 *This,
 IN BOOLEAN                                        ExtendedVerification
 );

 typedef
EFI_STATUS
(EFIAPI *EFI_INPUT_READ_KEY) (
 IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL              *This,
 OUT EFI_INPUT_KEY                              *Key
 );

/* Guid */
#define EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID \
 {0x387477c1,0x69c7,0x11d2,\
  {0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
 EFI_INPUT_RESET                       Reset;
 EFI_INPUT_READ_KEY                    ReadKeyStroke;
 EFI_EVENT                             WaitForKey;
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;



#endif