#include  <Uefi.h>
#include  <Library/UefiLib.h>
#include  <Library/UefiBootServicesTableLib.h>
#include  <Library/UefiRuntimeServicesTableLib.h>
#include  <Library/PrintLib.h>
#include <Protocol/GraphicsOutput.h>

#include "common.h"

// Open graphics output protocol
EFI_STATUS open_gop(void) {
    EFI_STATUS status;
    UINTN num_handles;
    num_handles = 0;
    EFI_HANDLE *gop_handles;
    gop_handles = NULL;

    // Locate Handle Buffer
    status = gBS->LocateHandleBuffer(ByProtocol, &gEfiGraphicsOutputProtocolGuid, NULL, &num_handles, &gop_handles);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Locate handle buffer\n");
    }

    // Open graphics output protocol

}