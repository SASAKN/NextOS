#include  <Uefi.h>
#include  <Library/UefiLib.h>
#include  <Library/UefiBootServicesTableLib.h>
#include  <Library/UefiRuntimeServicesTableLib.h>
#include  <Library/PrintLib.h>
#include <Protocol/GraphicsOutput.h>

#include "common.h"
#include "memory.h"
#include "elf.h"
#include "graphics.h"

// Open graphics output protocol
EFI_STATUS open_gop(EFI_HANDLE IM, EFI_GRAPHICS_OUTPUT_PROTOCOL **gop) {
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
    status = gBS->OpenProtocol(gop_handles[0], &gEfiGraphicsOutputProtocolGuid, (VOID **)gop, IM, NULL, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
    if (EFI_ERROR(status)) {
        PrintError();
        Print(L"Open Protocol : %r\n", status);
    }

    gBS->FreePool(gop_handles);

    return EFI_SUCCESS;
}

const CHAR16 *get_pf_unicode(EFI_GRAPHICS_OUTPUT_PROTOCOL fmt) {
    switch(fmt) {
        case PixelRedGreenBlueReserved8BitPerColor:
            return L"PixelRedGreenBlueReserved8BitPerColor";
        case PixelBlueGreenRedReserved8BitPerColor:
            return L"PixelBlueGreenRedReserved8BitPerColor";
        case PixelBitMask:
            return L"PixelBitMask";
        case PixelBltOnly:
            return L"PixelBltOnly";
        case PixelFormatMax:
            return L"PixelFormatMax";
        default:
            return L"UnknownPixelFormat";
    }
}