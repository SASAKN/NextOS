#ifndef _BOOT_GUID_H
#define _BOOT_GUID_H

#include "efi.h"
#include "types.h"
#include "status.h"
#include "proto.h"
#include "elf.h"

EFI_GUID lip_guid = {0x5b1b31a1, 0x9562, 0x11d2, {0x8e, 0x3f, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};

EFI_GUID sfsp_guid = {0x0964e5b22, 0x6459, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};

extern EFI_GUID EfiLoadedImageProtocolGuid;
extern EFI_GUID lip_guid;
extern EFI_GUID dpp_guid;
extern EFI_GUID fi_guid;
extern EFI_GUID sfsp_guid;

#endif