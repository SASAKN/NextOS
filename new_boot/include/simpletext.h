#ifndef _EFI_SIMPLETEXT_H
#define _EFI_SIMPLETEXT_H

/* SimpleTextInputExProtocol */
/* Guid */
#define EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_GUID \
 {0xdd9e7534, 0x7762, 0x4698, \
  {0x8c, 0x14, 0xf5, 0x85, 0x17, 0xa6, 0x25, 0xaa}}

typedef
EFI_STATUS
(EFIAPI *EFI_INPUT_RESET_EX) (
 IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL        *This,
 IN BOOLEAN                                  ExtendedVerification
 );

typedef
EFI_STATUS
(EFIAPI *EFI_INPUT_READ_KEY_EX) (
 IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL     *This,
 OUT EFI_KEY_DATA                         *KeyData
 );

 

typedef struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL {
 EFI_INPUT_RESET_EX                          Reset;
 EFI_INPUT_READ_KEY_EX                       ReadKeyStrokeEx;
 EFI_EVENT                                   WaitForKeyEx;
 EFI_SET_STATE                               SetState;
 EFI_REGISTER_KEYSTROKE_NOTIFY               RegisterKeyNotify;
 EFI_UNREGISTER_KEYSTROKE_NOTIFY             UnregisterKeyNotify;
} EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL;


#endif