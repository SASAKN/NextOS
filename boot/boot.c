/* Neos Boot Loader v0.1 */

#include "include/efi.h"
#include "include/config.h"
#include "include/elf.h"
#include "include/graphics.h"
#include "include/mem.h"

/* Print Hello! */
EFI_STATUS EFIAPI EfiMain(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable)
{
    puts(L"Hello !");
    while (1);
    return EFI_SUCCESS;
};