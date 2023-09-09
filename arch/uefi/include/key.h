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

#endif