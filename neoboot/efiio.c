#include <Uefi/UefiBaseType.h>
#include <Protocol/SimpleFileSystem.h>
#include <Guid/FileInfo.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/SimpleTextOut.h>
#include <Protocol/LoadedImage.h>
#include <Guid/FileInfo.h>
#include <Library/BaseLib.h>
#include <Library/UefiLib.h>

void PrintOK(void)
{
    gST->ConOut->SetAttribute(gST->ConOut, EFI_GREEN); /* 緑で、OKを表示 */
    gST->ConOut->OutputString(gST->ConOut, L"[ OK ]");
    gST->ConOut->SetAttribute(gST->ConOut, EFI_WHITE); /* 白に戻す */
};

void PrintWarn(void)
{
    gST->ConOut->SetAttribute(gST->ConOut, EFI_YELLOW); /* 黄色で、Warnを表示 */
    gST->ConOut->OutputString(gST->ConOut, L"[ Warn ]");
    gST->ConOut->SetAttribute(gST->ConOut, EFI_WHITE); /* 白に戻す */
};

void PrintError(void)
{
    gST->ConOut->SetAttribute(gST->ConOut, EFI_RED); /* あかで、Errorを表示 */
    gST->ConOut->OutputString(gST->ConOut, L"[ Error ! ]");
    gST->ConOut->SetAttribute(gST->ConOut, EFI_WHITE); /* 白に戻す */
};

// Open root directory
EFI_STATUS open_root_dir(EFI_HANDLE IM, EFI_FILE_PROTOCOL **root) {
    EFI_STATUS status;
    EFI_LOADED_IMAGE_PROTOCOL *lip;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *fs;
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

EFI_STATUS open_file_read(UINTN file_size, EFI_FILE_PROTOCOL *root, EFI_FILE_PROTOCOL *file, CHAR16 *file_path) {
    EFI_STATUS status;
    status = root->Open(root, &file, file_path, EFI_FILE_MODE_READ, 0);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Open '%-ls' : %r\n", file_path, status);
        return status;
    }
    // FMAのところも計算
    UINTN file_info_buffer_size = sizeof(EFI_FILE_INFO) + sizeof(CHAR16) * StrLen(file_path) + 2;
    UINT8 file_info_buffer[file_info_buffer_size];
    status = file->GetInfo(file, &gEfiFileInfoGuid, &file_info_buffer_size, file_info_buffer);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Get Info : %r \n", status);
        return status;
    }
    PrintOK();
    Print(L"Get Info\n");
    EFI_FILE_INFO *file_info = (EFI_FILE_INFO *)file_info_buffer;
    file_size = file_info->FileSize;
    return EFI_SUCCESS;
}