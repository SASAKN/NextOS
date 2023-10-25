#ifndef _EFI_SIMPLETEXT_H
#define _EFI_SIMPLETEXT_H

/* 新しいヘッダーに追加したものは、コメントアウト */

// /* SimpleTextInputExProtocol */
#include "efi.h"

/* Guid */
#define EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_GUID             \
    {                                                      \
        0xdd9e7534, 0x7762, 0x4698,                        \
        {                                                  \
            0x8c, 0x14, 0xf5, 0x85, 0x17, 0xa6, 0x25, 0xaa \
        }                                                  \
    }

// typedef struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL
// {
//     EFI_INPUT_RESET_EX Reset;
//     EFI_INPUT_READ_KEY_EX ReadKeyStrokeEx;
//     EFI_EVENT WaitForKeyEx;
//     EFI_SET_STATE SetState;
//     EFI_REGISTER_KEYSTROKE_NOTIFY RegisterKeyNotify;
//     EFI_UNREGISTER_KEYSTROKE_NOTIFY UnregisterKeyNotify;
// } EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL;

// typedef EFI_STATUS(*EFI_INPUT_READ_KEY_EX)(
//     IN struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
//     OUT EFI_KEY_DATA *KeyData);

// typedef EFI_STATUS(*EFI_SET_STATE)(
//     IN struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
//     IN EFI_KEY_TOGGLE_STATE *KeyToggleState);

// typedef EFI_STATUS(*EFI_KEY_NOTIFY_FUNCTION)(
//     IN EFI_KEY_DATA *KeyData);

// typedef EFI_STATUS(*EFI_REGISTER_KEYSTROKE_NOTIFY)(
//     IN struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
//     IN EFI_KEY_DATA *KeyData,
//     IN EFI_KEY_NOTIFY_FUNCTION KeyNotificationFunction,
//     OUT VOID **NotifyHandle);

// typedef EFI_STATUS(*EFI_UNREGISTER_KEYSTROKE_NOTIFY)(
//     IN struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
//     IN VOID *NotificationHandle);

// /* SimpleTextInputProtocol */

/* Guid */
#define EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID \
 {0x387477c1,0x69c7,0x11d2,\
  {0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

// typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
//  EFI_INPUT_RESET                       Reset;
//  EFI_INPUT_READ_KEY                    ReadKeyStroke;
//  EFI_EVENT                             WaitForKey;
// } EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

// typedef
// EFI_STATUS
// (*EFI_INPUT_RESET) (
//  IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL                 *This,
//  IN BOOLEAN                                        ExtendedVerification
//  );

//  typedef
// EFI_STATUS
// (*EFI_INPUT_READ_KEY) (
//  IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL              *This,
//  OUT EFI_INPUT_KEY                              *Key
//  );

/* SimpleTextOutputProtocol */
/* Guid */
#define EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID \
 {0x387477c2,0x69c7,0x11d2,\
  {0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}


//  typedef
// EFI_STATUS
// (*EFI_TEXT_SET_CURSOR_POSITION) (
//  IN struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
//  IN UINTN                                       Column,
//  IN UINTN                                       Row
//  );

// typedef
// EFI_STATUS
// (*EFI_TEXT_ENABLE_CURSOR) (
//  IN struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
//  IN BOOLEAN                                     Visible
//  );

// typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
//  EFI_TEXT_RESET                           Reset;
//  EFI_TEXT_STRING                          OutputString;
//  EFI_TEXT_TEST_STRING                     TestString;
//  EFI_TEXT_QUERY_MODE                      QueryMode;
//  EFI_TEXT_SET_MODE                        SetMode;
//  EFI_TEXT_SET_ATTRIBUTE                   SetAttribute;
//  EFI_TEXT_CLEAR_SCREEN                    ClearScreen;
//  EFI_TEXT_SET_CURSOR_POSITION             SetCursorPosition;
//  EFI_TEXT_ENABLE_CURSOR                   EnableCursor;
//  SIMPLE_TEXT_OUTPUT_MODE                  *Mode;
// } EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

// typedef
// EFI_STATUS
// (*EFI_TEXT_RESET) (
//  IN struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
//  IN BOOLEAN                               ExtendedVerification
//  );

//  typedef
// EFI_STATUS
// (*EFI_TEXT_STRING) (
//  IN struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
//  IN CHAR16                             *String
//  );

//  typedef
// EFI_STATUS
// (*EFI_TEXT_TEST_STRING) (
//  IN struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
//  IN CHAR16                                *String
//  );

// typedef
// EFI_STATUS
// (*EFI_TEXT_QUERY_MODE) (
//  IN struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL This,
//  IN UINTN                                    ModeNumber,
//  OUT UINTN                                   *Columns,
//  OUT UINTN                                   *Rows
//  );

//   typedef
// EFI_STATUS
// (*EFI_TEXT_SET_MODE) (
//  IN struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
//  IN UINTN                                    ModeNumber
//  );

// typedef
// EFI_STATUS
// (*EFI_TEXT_SET_ATTRIBUTE) (
//  IN struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
//  IN UINTN                                  Attribute
//  );

//  typedef
// EFI_STATUS
// (*EFI_TEXT_CLEAR_SCREEN) (
//  IN struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This
//  );



#endif