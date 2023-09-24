/* EFI_INIT */
#include "../include/efi.h"

EFI_SYSTEM_TABLE *ST;

void efi_init(EFI_SYSTEM_TABLE *SystemTable) {
    ST = SystemTable;
};