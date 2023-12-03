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

EFI_STATUS allocate_kernel(UINTN kernel_file_size, EFI_PHYSICAL_ADDRESS *kernel_base_addr) {
    EFI_STATUS status;
    status = gBS->AllocatePages(AllocateAddress, EfiLoaderData, (kernel_file_size + 0xfff) / 0x1000, kernel_base_addr);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Allocate pages for the kernel file : %r\n", status);
    }
    return EFI_SUCCESS;
}

EFI_STATUS read_kernel(EFI_FILE_PROTOCOL *f, UINTN *kernel_file_size, EFI_PHYSICAL_ADDRESS *kernel_base_addr) {
    f->Read(f, kernel_file_size, (VOID *)kernel_base_addr);
    return EFI_SUCCESS;
}
