#include <Uefi/UefiBaseType.h>
#include <Protocol/SimpleFileSystem.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/LoadedImage.h>
#include <Guid/FileInfo.h>
#include <Library/BaseLib.h>
#include <Library/UefiLib.h>

void PrintOK(void)
{
    gST->ConOut->SetAttribute(gST->ConOut, 0x02); /* 緑で、OKを表示 */
    gST->ConOut->OutputString(gST->ConOut, L"[ OK ]");
    gST->ConOut->SetAttribute(gST->ConOut, 0x0F); /* 白に戻す */
};

void PrintWarn(void)
{
    gST->ConOut->SetAttribute(gST->ConOut, 0x0E); /* 黄色で、Warnを表示 */
    gST->ConOut->OutputString(gST->ConOut, L"[ Warn ]");
    gST->ConOut->SetAttribute(gST->ConOut, 0x0F); /* 白に戻す */
};

void PrintError(void)
{
    gST->ConOut->SetAttribute(gST->ConOut, 0x04); /* あかで、Errorを表示 */
    gST->ConOut->OutputString(gST->ConOut, L"[ Error ! ]");
    gST->ConOut->SetAttribute(gST->ConOut, 0x0F); /* 白に戻す */
};

// Open root directory
EFI_STATUS open_root_dir(EFI_HANDLE IM, DIR **root) {
    EFI_STATUS status;
    EFI_LOADED_IMAGE_PROTOCOL *lip;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *fs;
    EFI_HANDLE fs_opener;
    // Loaded Image Protocol
    status = gBS->OpenProtocol(IM, &gEfiLoadedImageProtocolGuid, (VOID**)&lip, IM, NULL, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Open Protocol : %r\n", status);
    }
    // Simple File System Protocol
    status = gBS->OpenProtocol(lip->DeviceHandle, &gEfiSimpleFileSystemProtocolGuid, (VOID**)&fs, IM, NULL, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Open Protocol : %r\n", status);
    }
    // Open Volume
    status = fs->OpenVolume(fs, root);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Open Protocol : %r\n", status);
    }
    // Close Loaded Image Protocol
    status = gBS->CloseProtocol(IM, &gEfiLoadedImageProtocolGuid, IM, NULL);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Close Loaded Image Protocol : %r\n", status);
    }
    // Close Simple File System Protocol
    status = gBS->CloseProtocol(lip->DeviceHandle, &gEfiSimpleFileSystemProtocolGuid, IM, NULL);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Close Simple File System Protocol : %r\n", status);
    }
    PrintOK();
    Print(L"Open Volume\n");
    return EFI_SUCCESS;
}