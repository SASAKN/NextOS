#ifndef _ARCH_UEFI_GUID_H
#define _ARCH_UEFI_GUID_H

/* EFI_GUID */
typedef struct
{
    UINT32 Data1;
    UINT16 Data2;
    UINT16 Data3;
    UINT8 Data4[8];
} EFI_GUID;

/* GUID */
#define EFI_BOOT_MANAGER_POLICY_PROTOCOL_GUID              \
    {                                                      \
        0xFEDF8E0C, 0xE147, 0x11E3,                        \
        {                                                  \
            0x99, 0x03, 0xB8, 0xE8, 0x56, 0x2C, 0xBA, 0xFA \
        }                                                  \
    }
#define EFI_DEVICE_PATH_PROTOCOL_GUID \
  {0x09576e91,0x6d3f,0x11d2,\
    {0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

#endif