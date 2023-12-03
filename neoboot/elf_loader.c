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

EFI_STATUS read_file(UINTN *file_size, EFI_FILE_PROTOCOL *file, void *buffer) {
    EFI_STATUS status;
    // Allocate Pool
    status = gBS->AllocatePool(EfiLoaderData, *file_size, &buffer);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Allocate Pool\n");
    }
    PrintOK();
    Print(L"Allocate pool\n");
    // // Read File
    // status = file->Read(file, file_size, &buffer);
    // if (EFI_ERROR(status)) {
    //     PrintError();
    //     Print(L"Read Kernel \n");
    // }
    // PrintOK();
    // Print(L"Read kernel\n");
    return EFI_SUCCESS;
}