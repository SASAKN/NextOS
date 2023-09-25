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
	EFI_GUID gop_guid = {0x9042a9de, 0x23dc, 0x4a38, {0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a}};
	EFI_GUID spp_guid = {0x31878c87, 0xb75, 0x11d5, {0x9a, 0x4f, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
	EFI_GUID stiep_guid = {0xdd9e7534, 0x7762, 0x4698, {0x8c, 0x14, 0xf5, 0x85, 0x17, 0xa6, 0x25, 0xaa}};
	EFI_GUID dpttp_guid = {0x8b843e20, 0x8132, 0x4852, {0x90, 0xcc, 0x55, 0x1a, 0x4e, 0x4a, 0x7f, 0x1c}};
	EFI_GUID dpftp_guid = {0x5c99a21, 0xc70f, 0x4ad2, {0x8a, 0x5f, 0x35, 0xdf, 0x33, 0x43, 0xf5, 0x1e}};
	EFI_GUID dpup_guid = {0x379be4e, 0xd706, 0x437d, {0xb0, 0x37, 0xed, 0xb8, 0x2f, 0xb7, 0x72, 0xa4}};
	EFI_GUID msp_guid = {0x3fdda605, 0xa76e, 0x4f46, {0xad, 0x29, 0x12, 0xf4, 0x53, 0x1b, 0x3d, 0x08}};

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