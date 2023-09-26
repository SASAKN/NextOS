/* Neos Boot Loader v0.1 */

#include "../include/efi.h"
#include "../include/proto.h"
#include "../include/config.h"
#include "../include/elf.h"
#include "../include/graphics.h"
#include "../include/mem.h"

/* Print Hello! */
EFI_STATUS EfiMain(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable)
{
    efi_init(SystemTable); /* UEFIの全てを初期化する関数 */
    puts(L"Hello !");
    while (1);
    return EFI_SUCCESS;
};