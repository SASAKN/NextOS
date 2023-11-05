#include "include/efi.h"
#include "include/proto.h"


/* OKを緑で表示 */
void PrintOK(EFI_SYSTEM_TABLE *SystemTable)
{
    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, 0x02); /* 緑で、OKを表示 */
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"[ OK ]");
    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, 0x0F); /* 白に戻す */
};