#include "../include/efi.h"
#include "../include/proto.h"

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

EFI_SYSTEM_TABLE *ST;

void efi_init(EFI_SYSTEM_TABLE *SystemTable)
{
	EFI_GUID lip_guid = {0x5b1b31a1, 0x9562, 0x11d2, {0x8e, 0x3f, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
	EFI_GUID dpp_guid = {0x09576e91, 0x6d3f, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
	EFI_GUID fi_guid = {0x09576e92, 0x6d3f, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
	
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