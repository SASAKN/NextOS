#include "include/efi.h"
#include "include/proto.h"
#include "include/guid.h"

EFI_SYSTEM_TABLE *ST;
EFI_BOOT_SERVICES *BS;
EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP;
EFI_SIMPLE_POINTER_PROTOCOL *SPP;
EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *SFSP;
EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *STIEP;
EFI_DEVICE_PATH_TO_TEXT_PROTOCOL *DPTTP;
EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL *DPFTP;
EFI_DEVICE_PATH_UTILITIES_PROTOCOL *DPUP;
EFI_MP_SERVICES_PROTOCOL *MSP;
EFI_LOADED_IMAGE_PROTOCOL *ELIP;

EFI_SYSTEM_TABLE *ST;

void efi_init(EFI_SYSTEM_TABLE *SystemTable)
{
	/* GUID */

	SystemTable->ConOut->ClearScreen(SystemTable->ConOut); /* 画面クリア */
	ST = SystemTable;
	ST->BootServices->SetWatchdogTimer(0, 0, 0, NULL); /* 5分何もしないでいると、再起動してしまうバグを修正 */
	ST->BootServices->LocateProtocol(&gop_guid, NULL, (void **)&GOP);
	ST->BootServices->LocateProtocol(&spp_guid, NULL, (void **)&SPP);
	ST->BootServices->LocateProtocol(&sfsp_guid, NULL, (void **)&SFSP);
	ST->BootServices->LocateProtocol(&stiep_guid, NULL, (void **)&STIEP);
	ST->BootServices->LocateProtocol(&dpttp_guid, NULL, (void **)&DPTTP);
	ST->BootServices->LocateProtocol(&dpftp_guid, NULL, (void **)&DPFTP);
	ST->BootServices->LocateProtocol(&dpup_guid, NULL, (void **)&DPUP);
	ST->BootServices->LocateProtocol(&msp_guid, NULL, (void **)&MSP);
};