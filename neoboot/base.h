/* UEFIの初期化などを設定するファイル */
#ifndef _BOOT_BASE_H
#define _BOOT_BASE_H

#include "include/efi.h"

/* Boot Base */
/* これは、NEOBOOTの初期化のためのものです。 */
extern EFI_SYSTEM_TABLE *gST;
extern EFI_BOOT_SERVICES *gBS;
extern EFI_RUNTIME_SERVICES *gRT;

#endif