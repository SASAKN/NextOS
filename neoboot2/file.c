// For using UEFI Library
#include  <Uefi.h>
#include  <Library/UefiLib.h>
#include  <Library/UefiBootServicesTableLib.h>
#include  <Library/UefiRuntimeServicesTableLib.h>
#include  <Library/PrintLib.h>
#include  <Library/MemoryAllocationLib.h>
#include  <Library/BaseMemoryLib.h>
#include  <Protocol/LoadedImage.h>
#include  <Protocol/SimpleFileSystem.h>
#include  <Guid/FileInfo.h>

#include "include/memory_map.h"
#include "include/file.h"
#include "include/proto.h"
#include "include/elf.h"

// ルートディレクトリーを開く
EFI_STATUS open_root_dir(EFI_HANDLE IM, DIR **root) {
    EFI_LOADED_IMAGE_PROTOCOL *lip;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *fs;
    // Loaded Image Protocol
    gBS->OpenProtocol(IM, &gEfiLoadedImageProtocolGuid, (VOID**)&lip, IM, NULL, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
    // Simple File System Protocol
    gBS->OpenProtocol(lip->DeviceHandle, &gEfiSimpleFileSystemProtocolGuid, (VOID**)&fs, IM, NULL, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
    // Open Volume
    fs->OpenVolume(fs, root);
    PrintOK();
    Print(L"Open Volume\n");
    return EFI_SUCCESS;
}

//ファイルを作る
EFI_FILE_PROTOCOL *create_file(EFI_FILE_PROTOCOL *root, CHAR16 *file_path) {
    EFI_STATUS status;
    EFI_FILE_PROTOCOL *file;
    status = root->Open(root, &file, file_path, EFI_FILE_MODE_READ | EFI_FILE_MODE_CREATE | EFI_FILE_MODE_WRITE, 0);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Create File : %r\n", status);
    }
    return file;
}

//ファイルを読み込む
