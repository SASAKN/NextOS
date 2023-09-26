#include "../include/efi.h"
#include "../include/proto.h" 
#include "../include/elf.h"
#include "../include/config.h"
#include "../include/graphics.h"

/* Print Hello! */
EFI_STATUS EFIAPI EfiMain(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable)
{
    puts(L"Hello from UEFI!");
    while (1);
    return EFI_SUCCESS;
};