// neoboot v.0.01
#include "include/efi.h"
#include "include/proto.h"
#include "include/config.h"
#include "include/elf.h"
#include "include/graphics.h"
#include "include/mem.h"
#include "include/macros.h"

EFI_STATUS EfiMain(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS status;
    // UEFIの初期化
    gST = SystemTable;
    gBS = gST->BootServices;
    gRT = gST->RuntimeServices;
    PrintOK(SystemTable);
}