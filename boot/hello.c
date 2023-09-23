#include "include/efi.h"
#include "include/elf.h"
#include "include/config.h"
#include "include/graphics.h"

struct EFI_SYSTEM_TABLE *ST;

/* Print Hello! */
EFI_STATUS EFIAPI EfiMain(
    IN EFI_HANDLE ImageHandle,
    IN *ST *SystemTable)
{
    ST->ConOut->OutputString(ST->ConOut, L"Hello Neos!\n");
    while (1);
    return EFI_SUCCESS;
};