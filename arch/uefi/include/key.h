#ifndef _ARCH_UEFI_KEY_H
#define _ARCH_UEFI_KEY_H

/* EFI_INPUT_KEY */
typedef struct
{
    UINT16 ScanCode;
    UINT16 UnicodeChar;
} EFI_INPUT_KEY;

/* EFI_KEY_OPTION */
typedef struct
{
    EFI_BOOT_KEY_DATA KeyData;
    UINT32 BootOptionCrc;
    UINT16 BootOption;
} EFI_KEY_OPTION;

/* EFI_BOOT_KEY_DATA */
typedef union
{
    struct
    {
        UINT32 Revision : 8;
        UINT32 ShiftPressed : 1;
        UINT32 ControlPressed : 1;
        UINT32 AltPressed : 1;
        UINT32 LogoPressed : 1;
        UINT32 MenuPressed : 1;
        UINT32 SysReqPressed : 1;
        UINT32 Reserved : 16;
        UINT32 InputKeyCount : 2;
    } Options;
    UINT32 PackedValue;
} EFI_BOOT_KEY_DATA;

#endif