/* EFI_INIT */
#include "../include/efi.h"

EFI_SYSTEM_TABLE *ST;

void efi_init(EFI_SYSTEM_TABLE *SystemTable) {
    SystemTable->ConOut->ClearScreen(SystemTable->ConOut); /* 何かが、画面に表示されてしまわないようにクリア。 */
    ST = SystemTable;
    SystemTable->BootServices->SetWatchdogTimer(0, 0, 0, NULL); /* 5分何もしないでいると、再起動してしまうバグを修正 */
    SystemTable->BootServices->LocateProtocol(&gop_guid, NULL, (void **)&GOP);
	SystemTable->BootServices->LocateProtocol(&spp_guid, NULL, (void **)&SPP);
	SystemTable->BootServices->LocateProtocol(&sfsp_guid, NULL, (void **)&SFSP);
	SystemTable->BootServices->LocateProtocol(&stiep_guid, NULL, (void **)&STIEP);
	SystemTable->BootServices->LocateProtocol(&dpttp_guid, NULL, (void **)&DPTTP);
	SystemTable->BootServices->LocateProtocol(&dpftp_guid, NULL, (void **)&DPFTP);
	SystemTable->BootServices->LocateProtocol(&dpup_guid, NULL, (void **)&DPUP);
};