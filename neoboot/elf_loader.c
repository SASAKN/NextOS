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
#include "elf.h"
#include "elf_loader.h"

EFI_STATUS load_kernel(EFI_FILE_PROTOCOL *root, EFI_FILE_PROTOCOL *k, UINTN kfile_size, EFI_PHYSICAL_ADDRESS *kbase_addr) {
    EFI_STATUS status;
    // Get info the kernel file
    kfile_size = open_file_read(root, L"\\kernel.elf", k);
    Print(L"\n");
    Print(L"[ INFO ] Kernel File Size = %lu bytes\n", kfile_size);

    // Allocate
    status = gBS->AllocatePages(AllocateAddress, EfiLoaderData, (kfile_size + 4095) / 4096, kbase_addr);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Allocate pages : %r\n", status);
    }
    PrintOK();
    Print(L"Allocate kernel\n");

    // Read
    status = k->Read(k, &kfile_size, (VOID *)kbase_addr);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Read kernel : %r\n", status);
    }
    PrintOK();
    Print(L"Read kernel\n");

    return EFI_SUCCESS;
}
