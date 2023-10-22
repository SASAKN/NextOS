#include "include/efi.h"
#include "include/proto.h"

/* Print Hello! */
EFI_STATUS EfiMain(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable)
{
    efi_init(SystemTable); /* EFIのプロトコルなどを読み込む関数 */
    puts(L"Hello !");
    while (1);
    return EFI_SUCCESS;
};