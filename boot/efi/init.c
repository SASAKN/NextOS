/* EFI_INIT */
#include "../include/efi.h"

EFI_SYSTEM_TABLE *ST;

void efi_init(EFI_SYSTEM_TABLE *SystemTable) {
    SystemTable->ConOut->ClearScreen(SystemTable->ConOut); /* 何かが、画面に表示されてしまわないようにクリア。 */
    ST = SystemTable;
    SystemTable->BootServices->SetWatchdogTimer(0, 0, 0, NULL); /* 5分何もしないでいると、再起動してしまうバグを修正 */
};