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

EFI_STATUS read_kernel(EFI_FILE_PROTOCOL *kernel_file, UINTN kernel_f_size, VOID *kernel_buffer) {
    EFI_STATUS status;
    status = gBS->AllocatePool(EfiLoaderData, kernel_f_size, &kernel_buffer);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Allocate Pool\n");
        return EFI_SUCCESS;
    }
    status = kernel_file->Read(kernel_file, &kernel_f_size, kernel_buffer);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Read kernel file\n");
        return EFI_SUCCESS;
    }
    return EFI_SUCCESS;
}