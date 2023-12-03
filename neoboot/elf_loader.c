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

#include "efiio.h"
#include "memory.h"
#include "elf.h"

// ELFファイルの読み取りなど

EFI_STATUS read_kernel(EFI_FILE_PROTOCOL *kernel_file, VOID **kernel_buffer) {
    EFI_STATUS status;
    UINTN file_info_size = sizeof(EFI_FILE_INFO) + sizeof(CHAR16) * 12;
    UINT8 file_info_buffer[file_info_size];
    kernel_file->GetInfo(kernel_file, &gEfiFileInfoGuid, &file_info_size, file_info_buffer);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"GetInfo Status : %r\n", status);
    }
    EFI_FILE_INFO *file_info = (EFI_FILE_INFO *)file_info_buffer;
    UINTN file_size = file_info->FileSize;
    status = gBS->AllocatePool(EfiLoaderData, file_size, kernel_buffer);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"AllocatePool Status : %r\n", status);
    }
    status = kernel_file->Read(kernel_file, &file_size, *kernel_buffer);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Read : %r \n", status);
    }
    return EFI_SUCCESS;
}